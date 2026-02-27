#pragma once

#include <entt/entt.hpp>
#include <string>

namespace VE {

    class Scene {
    public:
        Scene();
        ~Scene();

        entt::entity CreateEntity(const std::string& name = "Empty Entity");
        void DestroyEntity(entt::entity entity);

        void OnUpdate(float dt);
        void OnRender();

        entt::registry& GetRegistry() { return m_Registry; }

    private:
        entt::registry m_Registry;
    };

}
