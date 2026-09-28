#include <console/console.hpp>
#include <application/application.hpp>
#include <math/types.hpp>
#include <math/random.hpp>
#include <entities/components.hpp>
#include <entt/entt.hpp>
#include <entities/scene_manager.hpp>

using namespace vega::math;
using vega::console;

class entity_layer final : public vega::ilayer {
 public:
  using vega::ilayer::ilayer;

  void assets_init() noexcept final {
    _count      = 1000;
    auto& scene = get_app_context()->active_scene;

    for (size_t i = 0; i < _count; i++) {
      vega::add_game_object_3d(
          scene,
          {.position = vec3d(2., 0., 0.), .scale = vec3d(0.15)},
          {.velocity = random::in_ball(0.5)},
          vega::components::physics(10.),
          vega::meshes::primitives::cube,
          vega::textures::m57
      );
    }

    vega::add_static_object_3d(
        scene, {.position = vec3d(0.F), .scale = vec3d(1.F)}, vega::meshes::sponza
    );

    scene.update_texture_descriptor();
    scene.upload_material_buffer();
  }

  void fixed_update(double fixed_step) noexcept final {
    entt::registry* registry = get_app_context()->active_scene.registry();

    auto view = registry->view<
        vega::components::transform,
        vega::components::velocity,
        vega::components::physics>();

    for (auto [entity, transform, velocity, physics] : view.each()) {
      physics.add_force(-0.2 * velocity.velocity);
      physics.iterate_euler(fixed_step, transform, velocity);
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