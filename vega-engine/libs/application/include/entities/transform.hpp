#pragma once
#include <math/vec.hpp>

namespace vega::components {

struct transform {
  math::vec3d position;
  math::vec3d scale = math::vec3d(1.F);

  [[nodiscard]] glm::mat4x4 world_transform() const {
    auto mat = glm::mat4x4(1.F);
    mat      = glm::translate(mat, math::vec3d_to_glm_f(position));
    mat      = glm::scale(mat, math::vec3d_to_glm_f(scale));

    return mat;
  }
};

struct velocity {
  math::vec3d velocity;
};

class physics {
 public:
  physics(double mass) : _mass(mass) {
    check_mass();
    _inv_mass = 1. / mass;  // NOLINT
  }

  void add_force(const math::vec3d& force) { _acceleration += force * _inv_mass; }

  void iterate_euler(double dt, transform& p, velocity& v) {
    p.position    += dt * v.velocity;
    v.velocity    += dt * _acceleration;
    _acceleration  = math::vec3d(0.);
  }

  [[nodiscard]] double mass() const { return _mass; }
  [[nodiscard]] double inverse_mass() const { return _inv_mass; }

 private:
  void check_mass() const {
    if (_mass == 0.F) {
      throw std::runtime_error("A rigid cannot have a mass of 0");
    }
  }

  double _mass     = 1.F;
  double _inv_mass = 1.F;
  math::vec3d _acceleration;
};

}  // namespace vega::components