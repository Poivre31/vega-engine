#pragma once

#include "handle.hpp"
#include <string>

namespace vega {

class mesh_3D;
struct model_info {
  std::string name;
  std::string object_folder;
  std::string file_name;
  float scale             = 1.F;
  bool z_is_up            = true;
  bool reverse_front_face = false;
  mutable handle<mesh_3D> handle{};
};

namespace meshes {

enum class primitives : uint8_t { cube };

model_info sponza{
    .name          = "Sponza",
    .object_folder = "resources/models/sponza/",
    .file_name     = "sponza.obj",
    .scale         = 1.F / 200,
    .z_is_up       = false,
};

const std::unordered_map<std::string, model_info*> imports{{sponza.name, &sponza}};

}  // namespace meshes
}  // namespace vega