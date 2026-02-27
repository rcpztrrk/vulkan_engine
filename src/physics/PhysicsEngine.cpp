#include "PhysicsEngine.h"
#include "core/Components.h"
#include <entt/entt.hpp>
#include <iostream>
#include <algorithm>

namespace VE {

    PhysicsEngine::PhysicsEngine() {
    }

    void PhysicsEngine::Update(float dt, entt::registry& registry) {
        auto view = registry.view<RigidBodyComponent, TransformComponent>();
        
        for (auto entity : view) {
            auto& rb = view.get<RigidBodyComponent>(entity);
            auto& tc = view.get<TransformComponent>(entity);

            if (rb.Body->GetInverseMass() > 0.0f) {
                // Synchronize Transform -> RigidBody (optional, for external teleports)
                rb.Body->SetPosition(tc.Translation);

                // Apply gravity
                rb.Body->AddForce(m_Gravity * rb.Body->GetMass());
                
                // Update body
                rb.Body->Update(dt);

                // Synchronize RigidBody -> Transform
                tc.Translation = rb.Body->GetPosition();
            }
        }
    }

}
