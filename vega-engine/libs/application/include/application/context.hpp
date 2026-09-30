#pragma once

#include <SDL3/SDL.h>

#include "application/config.hpp"
#include "application/scene.hpp"

#include "player/camera.hpp"

#include "graphics/context.hpp"

namespace vega {

struct application_context {
  SDL_Window* window = nullptr;

  int width    = config::startup_width;
  int height   = config::startup_height;
  bool running = false;

  double time                   = 0.;
  double avg_dt                 = 0.;
  double last_fixed_update_time = 0.;
  double last_dt_window_time    = 0.;
  double fixed_time             = 0.;
  bool reset_dt_history         = false;

  uint64_t frame       = 0;
  uint64_t fixed_frame = 0;

  Camera* active_camera = nullptr;
  struct {
    bool visible;
    float x;
    float y;
    float dx;
    float dy;
    bool clicked_down;
    bool clicked_up;
    uint32_t hovered_entity_index;
  } mouse_data{};

  struct {
    bool is_selected;
    uint32_t index;
  } selected_entity_data{};

  vulkan_context vulkan;

  //   resources_data resources;
  scene active_scene;

  std::vector<std::vector<char>> shader_modules;
};

}  // namespace vega