#pragma once
#include <SDL3/SDL.h>

#include "application/context.hpp"

namespace vega {

bool is_context_valid(application_context& context) {
  return context.window && context.active_camera && context.vulkan.allocator
         && context.vulkan.command_pool && context.vulkan.device && context.vulkan.physical_device
         && context.vulkan.graphics_queue;
}

/**
 * @brief An abstraction for the different steps at which code is executed during application
 * execution. Create a class marked as final that publically inherits from ilayer and uses its
 * default constructors, then overload the steps you want:
 *
 * class your_layer final : public ilayer {
 *  public:
 *    using ilayer::ilayer; // TODO : CHANGE THIS TO CLEANER SOLUTION
 *
 *    // AT CONSTRUCTION: return false if error makes it impossible to continue execution
 *    bool init() noexpect final {return true;}
 *
 *    // AT DESTRUCTION: only function called in reverse order (layer2 then layer1...)
 *    void cleanup() noexpect final {}
 *
 *    // BEFORE RENDERING: within an ImGui DrawFrame block, to handle UI logic
 *    void gui_update() noexpect final {}
 *
 *    // AT RENDERING: right before vulkan pipeline execution, for per frame logic
 *    void update(double delta_time) noexpect final {}
 *
 *    // AT FIXED INTERVAL: for logic that requires stability/lower fps (physics, gpu transfers...)
 *    void fixed_update(double fixed_step) noexpect final {}
 * };
 *
 */
class ilayer {
 public:
  ilayer(application_context* context) : _context(context) {
    assert(context != nullptr && "A valid application context should always be passed");
  }
  virtual ~ilayer()                = default;
  ilayer(const ilayer&)            = default;
  ilayer(ilayer&&)                 = default;
  ilayer& operator=(const ilayer&) = default;
  ilayer& operator=(ilayer&&)      = default;

  virtual bool init() noexcept { return true; };
  virtual void gui_update() noexcept {};
  virtual void update(double dt) noexcept {};
  virtual void fixed_update(double time_step) noexcept {};
  virtual void frame_render() noexcept {};
  virtual void cleanup() noexcept {};

  [[nodiscard]] application_context* get_app_context() const noexcept { return _context; }

 private:
  application_context* _context;
};

}  // namespace vega