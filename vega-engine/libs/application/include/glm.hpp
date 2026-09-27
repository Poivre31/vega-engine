#pragma once

#include <glm/glm.hpp>                    // IWYU pragma: export
#include <glm/vec3.hpp>                   // IWYU pragma: export
#include <glm/vec4.hpp>                   // IWYU pragma: export
#include <glm/mat4x4.hpp>                 // IWYU pragma: export
#include <glm/ext/matrix_transform.hpp>   // IWYU pragma: export
#include <glm/ext/matrix_clip_space.hpp>  // IWYU pragma: export
#include <glm/gtc/random.hpp>             // IWYU pragma: export
#include <glm/gtx/string_cast.hpp>        // IWYU pragma: export

#include <math/vec.hpp>

namespace vega::math {

inline glm::vec3 vec3d_to_glm_f(const vec3d& v) {
  return {float(v.x), float(v.y), float(v.z)};
}

inline glm::vec3 vec3f_to_glm_f(const vec3f& v) {
  return {v.x, v.y, v.z};
}

}  // namespace vega::math