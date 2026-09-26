#include <console/console.hpp>
#include <application/application.hpp>
#include <math/types.hpp>
#include <math/random.hpp>

#include <entt/entt.hpp>

using namespace vega::math;
using vega::console;

struct position {
  union {
    vec3d v{};
    struct {
      double x;
      double y;
      double z;
    };
  };
};

union velocity {
  vec3d v{};
  struct {
    double vx;
    double vy;
    double vz;
  };
};

class entity_layer final : public vega::ilayer {
 public:
  using vega::ilayer::ilayer;

  bool init() noexcept final {
    _count = 10;
    for (size_t i = 0; i < _count; i++) {
      const auto entity = _registry.create();
      _registry.emplace<position>(entity);
      _registry.emplace<velocity>(entity, random::uniform_vec3(-1., 1.));
    }
    return true;
  }

  void fixed_update(double fixed_step) noexcept final {
    auto view = _registry.view<position, velocity>();

    vec3d avg_velocity;
    vec3d avg_position;
    for (auto [entity, position, velocity] : view.each()) {
      position.v   += fixed_step * velocity.v;
      avg_position += position.v;
      avg_velocity += velocity.v;
    }

    _console->info(
        "COM = {:.3f}, computed COM = {:.3f}",
        avg_position / double(_count),
        (get_app_context()->fixed_time + fixed_step) * avg_velocity / double(_count)
    );
  }

 private:
  entt::registry _registry;
  size_t _count{};
  vega::vega_console _console = console::create("Entity");
};

int main() {
  vega::application<entity_layer> app("My vulkan app");
  app.run();
}