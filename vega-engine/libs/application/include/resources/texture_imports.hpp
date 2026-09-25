#pragma once

#include <cstdint>

namespace vega {

enum class channels : uint8_t { RGB = 3, RGBA = 4 };

struct texture_info {
  const char* texture_path{};
  bool enable_mipmaps      = true;
  bool is_srgb             = true;
  channels target_channels = channels::RGBA;
};

namespace textures {

const texture_info m57{
    .texture_path   = "resources/textures/m57.jpg",
    .enable_mipmaps = true,
};

}  // namespace textures
}  // namespace vega