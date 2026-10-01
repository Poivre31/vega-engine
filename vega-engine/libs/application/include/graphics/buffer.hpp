#pragma once

#include <console/console.hpp>

#include "graphics.hpp"
#include "context.hpp"

namespace vega {

template <class T>
class host_buffer {
 public:
  host_buffer(std::nullptr_t) {};
  host_buffer(
      vk::raii::Device& device,
      vma::raii::Allocator& allocator,
      size_t number_of_elements,
      bool gpu_to_cpu_transfer  = false,
      bool buffer_device_adress = true,
      bool permanent            = true
  )
      : _size(number_of_elements * sizeof(T)),
        _number(number_of_elements),
        _permanent(permanent),
        _gpu_to_cpu_transfer(gpu_to_cpu_transfer),
        _bda(buffer_device_adress) {
    _create_staging_buffer(allocator);
    if (_staging_buffer.getAllocation().getMemoryProperties()
        & vk::MemoryPropertyFlagBits::eDeviceLocal) {
      console::get(consoles::graphics)
          ->trace("Allocated {}B on device without staging buffer", _size);
      _buffer         = std::move(_staging_buffer);
      _staging_buffer = nullptr;

      _staged = false;
    } else {
      auto usage = vk::BufferUsageFlagBits::eStorageBuffer | vk::BufferUsageFlagBits::eTransferDst;
      if (_bda) {
        usage |= vk::BufferUsageFlagBits::eShaderDeviceAddress;
      }
      if (_gpu_to_cpu_transfer) {
        usage |= vk::BufferUsageFlagBits::eTransferSrc;
      }

      vk::BufferCreateInfo buffer_info{.size = _size, .usage = usage};
      vma::AllocationCreateFlags allocation_flags;
      if (_permanent) {
        allocation_flags |= vma::AllocationCreateFlagBits::eMapped
                            | vma::AllocationCreateFlagBits::eHostAccessSequentialWrite;
      }

      vma::AllocationCreateInfo allocation_info{
          .flags = allocation_flags,
          .usage = vma::MemoryUsage::eAutoPreferDevice,
      };
      _buffer = allocator.createBuffer(buffer_info, allocation_info);
      if (_buffer.getAllocation().getMemoryProperties()
          & vk::MemoryPropertyFlagBits::eDeviceLocal) {
        console::get(consoles::graphics)
            ->trace("Allocated {}B on device and created associated host staging buffer", _size);
      } else {
        console::get(consoles::graphics)
            ->warn(
                "Tried to allocate {}B on device but vma allocated it on host memory. A staging "
                "buffer has also been allocated on host memory",
                _size
            );
      }
      _staged = true;
    }
  }

  void upload_data(
      vma::raii::Allocator& allocator,
      vk::raii::CommandBuffer& cmd,
      const std::vector<T>& data
  ) {
    if (!data.data()) {
      throw std::runtime_error("Uploading invalid data (nullptr) to buffer");
    }
    if (data.size() > _number) {
      throw std::runtime_error("Uploading more data than the buffer was created for");
    }
    if (!*_buffer) {
      throw std::runtime_error("Uploading data before buffer creation");
    }

    uint64_t copy_size = data.size() * sizeof(T);
    if (_staged) {
      if (!*_staging_buffer) {
        _create_staging_buffer(allocator);
        console::get(consoles::graphics)
            ->warn(
                "Recreating a staging buffer after host_buffer creation, this is valid but it's "
                "best to set 'permanent=true' at creation if you intend to upload several times to "
                "the buffer"
            );
      }
      _staging_buffer.getAllocation().copyFromMemory(data.data(), 0, copy_size);
      vk::BufferCopy2 region{.srcOffset = 0, .dstOffset = 0, .size = copy_size};
      vk::CopyBufferInfo2 copy_info{
          .srcBuffer = _staging_buffer, .dstBuffer = _buffer, .regionCount = 1, .pRegions = &region
      };
      cmd.copyBuffer2(copy_info);
      if (!_permanent) {
        _staging_buffer = nullptr;
      }
    } else {
      _buffer.getAllocation().copyFromMemory(data.data(), 0, copy_size);
    }
  }

  [[nodiscard]] vma::raii::Buffer& get() { return _buffer; }
  [[nodiscard]] vk::DescriptorBufferInfo get_descriptor_info() {
    return {.buffer = _buffer, .offset = 0, .range = vk::WholeSize};
  }

  [[nodiscard]] vk::DeviceAddress get_adress(const vulkan_context& vk_context) {
    if (!_bda) {
      throw std::runtime_error(
          "Trying to get the adress of a buffer that doesn't use buffer device adress"
      );
    }
    if (!*_buffer) {
      throw std::runtime_error(
          "Trying to get the buffer adress of a buffer that hasn't been created"
      );
    }
    vk::BufferDeviceAddressInfo address_info{.buffer = _buffer};
    vk::DeviceAddress adress = vk_context.device->getBufferAddress(address_info);
    if (!adress) {
      throw std::runtime_error("Material buffer adresss is invalid");
    }
    return adress;
  }

  void wait_storage_write_for_cpu_read(vk::raii::CommandBuffer& cmd) {
    vk::PipelineStageFlags2 dst_stage_mask = _staged ? vk::PipelineStageFlagBits2::eTransfer
                                                     : vk::PipelineStageFlagBits2::eHost;
    vk::AccessFlagBits2 dst_access_mask    = _staged ? vk::AccessFlagBits2::eTransferRead
                                                     : vk::AccessFlagBits2::eHostRead;
    vk::BufferMemoryBarrier2 barrier{
        .srcStageMask        = vk::PipelineStageFlagBits2::eComputeShader,
        .srcAccessMask       = vk::AccessFlagBits2::eShaderStorageWrite,
        .dstStageMask        = dst_stage_mask,
        .dstAccessMask       = dst_access_mask,
        .srcQueueFamilyIndex = vk::QueueFamilyIgnored,
        .dstQueueFamilyIndex = vk::QueueFamilyIgnored,
        .buffer              = _buffer,
        .offset              = 0,
        .size                = _size,
    };
    vk::DependencyInfo dependency{.bufferMemoryBarrierCount = 1, .pBufferMemoryBarriers = &barrier};
    cmd.pipelineBarrier2(dependency);
  }

  void wait_cpu_write_for_storage_read(vk::raii::CommandBuffer& cmd) {
    vk::PipelineStageFlags2 src_stage_mask = _staged ? vk::PipelineStageFlagBits2::eTransfer
                                                     : vk::PipelineStageFlagBits2::eHost;
    vk::AccessFlagBits2 src_access_mask    = _staged ? vk::AccessFlagBits2::eTransferWrite
                                                     : vk::AccessFlagBits2::eHostWrite;
    vk::BufferMemoryBarrier2 barrier{
        .srcStageMask        = src_stage_mask,
        .srcAccessMask       = src_access_mask,
        .dstStageMask        = vk::PipelineStageFlagBits2::eComputeShader,
        .dstAccessMask       = vk::AccessFlagBits2::eShaderStorageRead,
        .srcQueueFamilyIndex = vk::QueueFamilyIgnored,
        .dstQueueFamilyIndex = vk::QueueFamilyIgnored,
        .buffer              = _buffer,
        .offset              = 0,
        .size                = _size,
    };
    vk::DependencyInfo dependency{.bufferMemoryBarrierCount = 1, .pBufferMemoryBarriers = &barrier};
    cmd.pipelineBarrier2(dependency);
  }

  void transfer_data_gpu_to_cpu(const vulkan_context& vk_context, vk::raii::CommandBuffer& cmd) {
    if (!_gpu_to_cpu_transfer) {
      throw std::runtime_error("Buffer was not created with the capability to read from cpu");
    }
    if (_permanent) {
      if (_staged) {
        vk::BufferCopy2 region{.srcOffset = 0, .dstOffset = 0, .size = _size};
        vk::CopyBufferInfo2 copy_info{
            .srcBuffer   = _buffer,
            .dstBuffer   = _staging_buffer,
            .regionCount = 1,
            .pRegions    = &region
        };
        cmd.copyBuffer2(copy_info);
        vk::BufferMemoryBarrier2 barrier{
            .srcStageMask        = vk::PipelineStageFlagBits2::eTransfer,
            .srcAccessMask       = vk::AccessFlagBits2::eTransferWrite,
            .dstStageMask        = vk::PipelineStageFlagBits2::eHost,
            .dstAccessMask       = vk::AccessFlagBits2::eHostRead,
            .srcQueueFamilyIndex = vk::QueueFamilyIgnored,
            .dstQueueFamilyIndex = vk::QueueFamilyIgnored,
            .buffer              = _staging_buffer,
            .offset              = 0,
            .size                = _size,
        };
        vk::DependencyInfo dependency{
            .bufferMemoryBarrierCount = 1, .pBufferMemoryBarriers = &barrier
        };
        cmd.pipelineBarrier2(dependency);
      }
      if (!_mapped_data) {
        throw std::runtime_error(
            "The mapped data to a permanenty mapped buffer is null, this shouldn't happend, buffer "
            "creation has probably failed."
        );
      }
    } else {
      throw std::runtime_error("Don't read data from gpu with a non persistent buffer");
    }
  }

  std::vector<T> get_transfered_data() {
    if (!_gpu_to_cpu_transfer) {
      throw std::runtime_error("Buffer was not created with the capability to read from cpu");
    }
    if (_permanent) {
      if (!_mapped_data) {
        throw std::runtime_error(
            "The mapped data to a permanenty mapped buffer is null, this shouldn't happend, buffer "
            "creation has probably failed."
        );
      }
      return std::vector<T>(_mapped_data, _mapped_data + _number);
    } else {
      throw std::runtime_error("Don't read data from gpu with a non persistent buffer");
    }
  }

 private:
  void _create_staging_buffer(vma::raii::Allocator& allocator) {
    if (*_staging_buffer) {
      return;
    }
    auto usage = vk::BufferUsageFlagBits::eStorageBuffer | vk::BufferUsageFlagBits::eTransferSrc;
    if (_bda) {
      usage |= vk::BufferUsageFlagBits::eShaderDeviceAddress;
    }
    if (_gpu_to_cpu_transfer) {
      usage |= vk::BufferUsageFlagBits::eTransferDst;
    }

    vk::BufferCreateInfo staging_buffer_info{
        .size        = _size,
        .usage       = usage,
        .sharingMode = vk::SharingMode::eExclusive,
    };
    vma::AllocationCreateFlags allocation_flags =
        vma::AllocationCreateFlagBits::eHostAccessAllowTransferInstead;
    vma::MemoryUsage memory_usage = vma::MemoryUsage::eAutoPreferDevice;
    if (_permanent) {
      allocation_flags |= vma::AllocationCreateFlagBits::eMapped;
    }
    if (_gpu_to_cpu_transfer) {
      allocation_flags |= vma::AllocationCreateFlagBits::eHostAccessRandom;
      memory_usage      = vma::MemoryUsage::eGpuToCpu;
    } else {
      allocation_flags |= vma::AllocationCreateFlagBits::eHostAccessSequentialWrite;
      memory_usage      = vma::MemoryUsage::eCpuToGpu;
    }
    vma::AllocationCreateInfo allocation_info{
        .flags         = allocation_flags,
        .usage         = memory_usage,
        .requiredFlags = vk::MemoryPropertyFlagBits::eHostCoherent,
    };
    _staging_buffer = allocator.createBuffer(staging_buffer_info, allocation_info);
    if (_permanent && _gpu_to_cpu_transfer) {
      _mapped_data = static_cast<T*>(_staging_buffer.getAllocation().getInfo().pMappedData);
    }
  }

  vma::raii::Buffer _buffer         = nullptr;
  vma::raii::Buffer _staging_buffer = nullptr;
  bool _staged{};
  bool _permanent{};
  bool _bda{};
  bool _gpu_to_cpu_transfer{};
  size_t _size{};
  size_t _number{};
  T* _mapped_data = nullptr;
};

}  // namespace vega