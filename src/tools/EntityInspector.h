#pragma once

#include <entt/entt.hpp>
#include <string>

namespace VE {

    class EntityInspector {
    public:
        static void OnUIRender(entt::registry& registry);

    private:
        static void DrawEntityNode(entt::registry& registry, entt::entity entity);
        static void DrawComponents(entt::registry& registry, entt::entity entity);

        static entt::entity s_SelectedEntity;
    };

}
