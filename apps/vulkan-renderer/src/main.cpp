#include <console/console.hpp>
#include <application/application.hpp>
#include <math/types.hpp>
#include <math/random.hpp>
#include <entities/renderer_3d.hpp>
#include <entities/rigid_body.hpp>
#include <entt/entt.hpp>

using namespace vega::math;
using vega::console;

class entity_layer final : public vega::ilayer {
 public:
  using vega::ilayer::ilayer;

  void assets_init() noexcept final {
    _count                   = 1000;
    auto& scene              = get_app_context()->active_scene;
    entt::registry* registry = scene.registry();
    auto m57_tex             = scene.load_texture(get_app_context()->vulkan, vega::textures::m57);
    auto m57_mat             = scene.resources()->materials.push(m57_tex);
    auto cube = scene.load_vertex_array(vega::create_cube({2.F, 0.F, 0.F}, 0.2F), m57_mat);

    for (size_t i = 0; i < _count; i++) {
      const auto entity = registry->create();
      registry->emplace<vega::renderer_3d>(entity, cube);
      registry->emplace<vega::rigid_body>(
          entity, vega::rigid_body(1.F, {0., 0., 0.}, random::uniform_vec3(-.3, .3))
      );
    }
    scene.resources()->meshes.get(cube)->create_vertex_buffer(get_app_context()->vulkan);

    const auto entity = registry->create();
    registry->emplace<vega::renderer_3d>(entity, vega::meshes::sponza);
    registry->emplace<vega::rigid_body>(entity, vega::rigid_body(1.F));

    scene.update_texture_descriptor(get_app_context()->vulkan);
    scene.upload_material_buffer(get_app_context()->vulkan);
  }

  void fixed_update(double fixed_step) noexcept final {
    entt::registry* registry = get_app_context()->active_scene.registry();

    auto view = registry->view<vega::rigid_body>();

    for (auto [entity, rigid_body] : view.each()) {
      rigid_body.add_force(-0.3 * rigid_body.velocity());
      rigid_body.iterate_euler(fixed_step);
    }
  }

 private:
  size_t _count{};
  vega::vega_console _console = console::create("Entity");
};

int main() {
  vega::application<entity_layer> app("My vulkan app");
  app.run();
}