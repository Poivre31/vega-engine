#pragma once

#include <application/context.hpp>
#include <resources/mesh_imports.hpp>
#include <resources/handle.hpp>

namespace vega {

class renderer_3d {
 public:
  renderer_3d(model_info& info) {
    if (!info.handle.valid) {
    }
    _mesh = info.handle;
  }
  renderer_3d(handle<mesh_3D> mesh) : _mesh(mesh) {}

  mesh_3D* get_mesh(application_context& context) {
    return context.active_scene.meshes()->get(_mesh);
  }

 private:
  handle<mesh_3D> _mesh;
};

}  // namespace vega