#pragma once

#include "graphics/context.hpp"

#include "application/scene.hpp"
#include "application/layer.hpp"

#include "mesh_imports.hpp"
#include "primitive_meshes.hpp"  // IWYU pragma: keep
#include "texture_imports.hpp"

namespace vega {

class assets_layer final : public ilayer {
 public:
  using ilayer::ilayer;
  bool init() noexcept final {
    try {
      const vulkan_context& vk_context = get_app_context()->vulkan;
      auto& scene                      = get_app_context()->active_scene;
      auto& resources                  = *scene.resources();

      scene.init(vk_context);

      // TEXTURES
      auto m57_tex = scene.load_texture(vk_context, textures::m57);
      auto m57_mat = resources.materials.push(m57_tex);

      // MODELS
      scene.load_mesh_from_obj_mtl(vk_context, meshes::sponza);
      scene.load_vertex_array(create_cube({1.F, 0.F, 0.F}, 0.5F), m57_mat);

      for (auto& mesh : resources.meshes) {
        mesh.create_vertex_buffer(vk_context);
      }

      scene.update_texture_descriptor(vk_context);
      scene.upload_material_buffer(vk_context);

    } catch (const std::exception& e) {
      console::get(consoles::assets)->error("Exception during assets initialisation: {}", e.what());
      return false;
    } catch (...) {
      console::get(consoles::assets)->error("Unknown error during assets initialisation");
      return false;
    }

    return true;
  }

 private:
};

}  // namespace vega