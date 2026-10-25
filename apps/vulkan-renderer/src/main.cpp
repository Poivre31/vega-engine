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
          {.position = vec3d(2., 0., 1.), .scale = vec3d(0.15)},
          {.velocity = random::in_ball(0.5)},
          vega::components::physics(1.),
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

  void gui_update() noexcept final {
    ImGui::Begin("Object editor");
    ImGui::Text(
        "Number of objects: %zu",
        get_app_context()->active_scene.registry()->view<entt::entity>()->size()
    );
    ImGui::Separator();
    if (ImGui::Button("Create object")) {
      vega::components::transform _transform;
      if (_editing_transform) {
        _transform = *_editing_transform;
      }
      auto entity = vega::add_game_object_3d(
          get_app_context()->active_scene,
          _transform,
          {},
          vega::components::physics(1.),
          vega::meshes::primitives::cube,
          vega::textures::m57
      );
      get_app_context()->active_scene.update_texture_descriptor();
      get_app_context()->active_scene.upload_material_buffer();
      get_app_context()->selected_entity_index = static_cast<uint64_t>(entity);
      _editing_transform =
          &get_app_context()->active_scene.registry()->get<vega::components::transform>(entity);
    }
    static bool random_objects_popup = false;
    if (ImGui::Button("Create random objects")) {
      random_objects_popup = true;
    }
    if (random_objects_popup) {
      ImGui::OpenPopup("Random objects settings");
      if (ImGui::BeginPopupModal("Random objects settings")) {
        static int number_objects      = 1;
        static float objects_scale     = 1.F;
        static float objects_max_speed = 1.F;
        static std::array<float, 3> objects_origin{};
        ImGui::Text("Number of objects: ");
        ImGui::SliderInt(
            "##Number of objects", &number_objects, 1, 10000, nullptr, ImGuiSliderFlags_Logarithmic
        );
        ImGui::DragFloat3(
            "Position",
            objects_origin.data(),
            1.F,
            -10.F,
            10.F,
            nullptr,
            ImGuiSliderFlags_NoRoundToFormat
        );
        ImGui::SliderFloat(
            "Scale", &objects_scale, 0.01, 100., nullptr, ImGuiSliderFlags_Logarithmic
        );
        ImGui::SliderFloat("Max velocity", &objects_max_speed, 0.0, 10.);
        if (ImGui::Button("Create")) {
          for (size_t i = 0; i < number_objects; i++) {
            vega::add_game_object_3d(
                get_app_context()->active_scene,
                {.position = vec3d(objects_origin[0], objects_origin[1], objects_origin[2]),
                 .scale    = vec3d(objects_scale)},
                {.velocity = random::in_ball(double(objects_max_speed))},
                vega::components::physics(1.),
                vega::meshes::sponza
            );
          }
          get_app_context()->active_scene.update_texture_descriptor();
          get_app_context()->active_scene.upload_material_buffer();
          random_objects_popup = false;
        }
        ImGui::EndPopup();
      }
    }
    if (ImGui::Button("Destroy all objects")) {
      vega::destroy_all_objects(get_app_context());
    }
    if (_editing_transform) {
      if (ImGui::Button("Destroy object")) {
        vega::destroy_object(
            get_app_context(), entt::entity(get_app_context()->selected_entity_index)
        );
      }
      ImGui::Separator();
      ImGui::Text("Transform");
      std::array<float, 3> position{
          float(_editing_transform->position.x),
          float(_editing_transform->position.y),
          float(_editing_transform->position.z)
      };
      if (ImGui::DragFloat3(
              "Position",
              position.data(),
              1.F,
              -10.F,
              10.F,
              nullptr,
              ImGuiSliderFlags_NoRoundToFormat
          )) {
        _editing_transform->position = vec3d(position[0], position[1], position[2]);
      }

      std::array<float, 3> scale{
          float(_editing_transform->scale.x),
          float(_editing_transform->scale.y),
          float(_editing_transform->scale.z)
      };
      if (ImGui::DragFloat3(
              "Scale", scale.data(), 1.F, -10, 10, nullptr, ImGuiSliderFlags_NoRoundToFormat
          )) {
        _editing_transform->scale = vec3d(scale[0], scale[1], scale[2]);
      }

      std::array<float, 3> rotation{
          float(_editing_transform->rotation.x),
          float(_editing_transform->rotation.y),
          float(_editing_transform->rotation.z)
      };
      if (ImGui::DragFloat3(
              "Rotation",
              rotation.data(),
              0.2F,
              0,
              2 * vega::math::constants::pi,
              nullptr,
              ImGuiSliderFlags_NoRoundToFormat | ImGuiSliderFlags_WrapAround
          )) {
        _editing_transform->rotation = vec3d(rotation[0], rotation[1], rotation[2]);
      }
    }
    ImGui::End();
  }

  void fixed_update(double fixed_step) noexcept final {
    auto view = get_app_context()
                    ->active_scene.registry()
                    ->view<
                        vega::components::transform,
                        vega::components::velocity,
                        vega::components::physics>();

    for (auto [entity, transform, velocity, physics] : view.each()) {
      physics.add_force(-0.2 * velocity.velocity);
      physics.iterate_euler(fixed_step, transform, velocity);
    }

    uint32_t selected_entity = get_app_context()->selected_entity_index;
    if (selected_entity != -1U) {
      _editing_transform =
          &get_app_context()->active_scene.registry()->get<vega::components::transform>(
              entt::entity(selected_entity)
          );
    } else {
      _editing_transform = nullptr;
    }
  }

 private:
  size_t _count{};
  vega::components::transform* _editing_transform = nullptr;
  vega::vega_console _console                     = console::create("Entity");
};

int main() {
  vega::application<entity_layer> app("My vulkan app");
  app.run();
}