#pragma once
#include <SDL3/SDL.h>

#include "application/context.hpp"

namespace vega {

bool is_context_valid(application_context& context) {
  return context.window && context.active_camera && context.vulkan.allocator
         && context.vulkan.command_pool && context.vulkan.device && context.vulkan.physical_device
         && context.vulkan.graphics_queue;
}

class ilayer {
 public:
  ilayer(application_context* context) : _context(context) {
    assert(context != nullptr && "A valid application context should always be passed");
  }
  virtual ~ilayer()                = default;
  ilayer(const ilayer&)            = default;
  ilayer(ilayer&&)                 = default;
  ilayer& operator=(const ilayer&) = default;
  ilayer& operator=(ilayer&&)      = default;

  virtual bool init() noexcept { return true; };
  virtual void gui_update() noexcept {};
  virtual void update(double dt) noexcept {};
  virtual void fixed_update(double time_step) noexcept {};
  virtual void frame_render() noexcept {};
  virtual void cleanup() noexcept {};

  [[nodiscard]] application_context* get_app_context() const noexcept { return _context; }

 private:
  application_context* _context;
};

}  // namespace vega