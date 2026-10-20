#pragma once

#include <application/scene.hpp>
#include <resources/mesh_imports.hpp>

#include "components.hpp"

namespace vega {

/** Creates an entity with rigid body component and a renderer 3d component constructed from
 * primitive type @param primitive and texture @param texture */
entt::entity add_game_object_3d(
    scene& scene,
    const components::transform& transform,
    const components::velocity& velocity,
    const components::physics& physics,
    meshes::primitives primitive,
    const texture_info& texture
) {
  entt::registry* registry = scene.registry();

  auto tex  = scene.load_texture(texture);
  auto mat  = scene.resources()->materials.push(tex);
  auto prim = scene.load_vertex_array(meshes::create_primitive(primitive), mat);

  const auto entity = registry->create();
  registry->emplace<components::renderer_3d>(entity, prim);
  registry->emplace<components::transform>(entity, transform);
  registry->emplace<components::velocity>(entity, velocity);
  registry->emplace<components::physics>(entity, physics);
  return entity;
}

entt::entity add_game_object_3d(
    scene& scene,
    const components::transform& transform,
    const components::velocity& velocity,
    const components::physics& physics,
    const model_info& info
) {
  entt::registry* registry = scene.registry();

  auto mesh = scene.load_mesh_from_obj_mtl(info);

  const auto entity = registry->create();
  registry->emplace<components::renderer_3d>(entity, mesh);
  registry->emplace<components::transform>(entity, transform);
  registry->emplace<components::velocity>(entity, velocity);
  registry->emplace<components::physics>(entity, physics);
  return entity;
}

entt::entity add_static_object_3d(
    scene& scene,
    const components::transform& transform,
    meshes::primitives primitive,
    texture_info texture
) {
  entt::registry* registry = scene.registry();

  auto tex  = scene.load_texture(texture);
  auto mat  = scene.resources()->materials.push(tex);
  auto prim = scene.load_vertex_array(meshes::create_primitive(primitive), mat);

  const auto entity = registry->create();
  registry->emplace<components::transform>(entity, transform);
  registry->emplace<components::renderer_3d>(entity, prim);
  return entity;
}

entt::entity
add_static_object_3d(scene& scene, const components::transform& transform, const model_info& info) {
  entt::registry* registry = scene.registry();

  auto mesh = scene.load_mesh_from_obj_mtl(info);

  const auto entity = registry->create();
  registry->emplace<components::transform>(entity, transform);
  registry->emplace<components::renderer_3d>(entity, mesh);
  return entity;
}

void destroy_object(application_context* context, entt::entity entity) {
  context->active_scene.registry()->destroy(entity);
  if (context->selected_entity_index == static_cast<uint64_t>(entity)) {
    context->selected_entity_index = -1U;
  }
  if (context->mouse_data.hovered_entity_index == static_cast<uint64_t>(entity)) {
    context->mouse_data.hovered_entity_index = -1U;
  }
}

void destroy_all_objects(application_context* context) {
  *context->active_scene.registry()        = entt::registry();
  context->selected_entity_index           = -1U;
  context->mouse_data.hovered_entity_index = -1U;
}

}  // namespace vega
