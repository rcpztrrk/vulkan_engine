#pragma once

#include "RigidBody.h"
#include <vector>
#include <memory>
#include <entt/entt.hpp>

namespace VE {

    class PhysicsEngine {
    public:
        PhysicsEngine();
        ~PhysicsEngine() = default;

        void Update(float dt, entt::registry& registry);

        void SetGravity(const glm::vec3& gravity) { m_Gravity = gravity; }

    private:
        void ResolveCollisions(entt::registry& registry);

        glm::vec3 m_Gravity{ 0.0f, -9.81f, 0.0f };
    };

}
