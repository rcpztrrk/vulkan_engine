#include "Scene.h"
#include "Components.h"

namespace VE {

    Scene::Scene() {
    }

    Scene::~Scene() {
    }

    entt::entity Scene::CreateEntity(const std::string& name) {
        entt::entity entity = m_Registry.create();
        m_Registry.emplace<TagComponent>(entity, name);
        m_Registry.emplace<TransformComponent>(entity);
        return entity;
    }

    void Scene::DestroyEntity(entt::entity entity) {
        m_Registry.destroy(entity);
    }

    void Scene::OnUpdate(float dt) {
        // This is where systems would be updated if they were part of the Scene
    }

    void Scene::OnRender() {
        // This is where rendering would be triggered
    }

}
