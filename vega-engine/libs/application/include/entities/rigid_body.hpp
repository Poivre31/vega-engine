#pragma once
#include <math/vec.hpp>
#include "glm.hpp"

using namespace vega::math;

namespace vega {

class rigid_body {
 public:
  rigid_body(double mass) : _mass(mass) { check_mass(); }
  rigid_body(double mass, vec3d position) : _mass(mass), _position(std::move(position)) {
    check_mass();
  }
  rigid_body(double mass, vec3d position, vec3d velocity)
      : _mass(mass), _position(std::move(position)), _velocity(std::move(velocity)) {
    check_mass();
  }

  void add_force(const vec3d& force) { _acceleration += force / _mass; }

  void iterate_euler(double dt) {
    _position     += dt * _velocity;
    _velocity     += dt * _acceleration;
    _acceleration  = vec3d(0.);
  }

  [[nodiscard]] vec3d& position() noexcept { return _position; }
  [[nodiscard]] vec3d& velocity() noexcept { return _velocity; }
  [[nodiscard]] glm::mat4x4 local_transform() const {
    auto mat = glm::mat4x4(1.F);
    mat      = glm::translate(mat, vec3d_to_glm_f(_position));

    return mat;
  }

 private:
  void check_mass() const {
    if (_mass == 0.F) {
      throw std::runtime_error("A rigid cannot have a mass of 0");
    }
  }

  double _mass{};
  vec3d _acceleration;
  vec3d _position;
  vec3d _velocity;
};

}  // namespace vega