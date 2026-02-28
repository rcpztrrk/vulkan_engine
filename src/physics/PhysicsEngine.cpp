#include "PhysicsEngine.h"
#include "core/Components.h"
#include <entt/entt.hpp>
#include <iostream>
#include <algorithm>
#include "physics/Collision.h"
#include "physics/Colliders.h"

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

        // 2. Collision Resolution
        ResolveCollisions(registry);
    }

    void PhysicsEngine::ResolveCollisions(entt::registry& registry) {
        auto view = registry.view<RigidBodyComponent, TransformComponent, ColliderComponent>();
        
        // O(N^2) broadphase for simplicity
        for (auto itA = view.begin(); itA != view.end(); ++itA) {
            auto entityA = *itA;
            auto& rbA = view.get<RigidBodyComponent>(entityA);
            auto& tcA = view.get<TransformComponent>(entityA);
            auto& colA = view.get<ColliderComponent>(entityA);
            
            auto itB = itA;
            ++itB;
            for (; itB != view.end(); ++itB) {
                auto entityB = *itB;
                auto& rbB = view.get<RigidBodyComponent>(entityB);
                auto& tcB = view.get<TransformComponent>(entityB);
                auto& colB = view.get<ColliderComponent>(entityB);
                
                // Skip if both are static
                if (rbA.Body->GetInverseMass() == 0.0f && rbB.Body->GetInverseMass() == 0.0f) {
                    continue;
                }
                
                CollisionManifold manifold;
                bool swapped = false;
                
                // Determine types and call appropriate collision function
                if (colA.Type == ColliderType::Sphere && colB.Type == ColliderType::Sphere) {
                    manifold = Collision::CheckSphereSphere(
                        std::get<SphereCollider>(colA.Shape), tcA.Translation,
                        std::get<SphereCollider>(colB.Shape), tcB.Translation);
                } else if (colA.Type == ColliderType::AABB && colB.Type == ColliderType::AABB) {
                    manifold = Collision::CheckAABBAABB(
                        std::get<AABBCollider>(colA.Shape), tcA.Translation,
                        std::get<AABBCollider>(colB.Shape), tcB.Translation);
                } else if (colA.Type == ColliderType::Sphere && colB.Type == ColliderType::AABB) {
                    manifold = Collision::CheckSphereAABB(
                        std::get<SphereCollider>(colA.Shape), tcA.Translation,
                        std::get<AABBCollider>(colB.Shape), tcB.Translation);
                } else if (colA.Type == ColliderType::AABB && colB.Type == ColliderType::Sphere) {
                    manifold = Collision::CheckSphereAABB(
                        std::get<SphereCollider>(colB.Shape), tcB.Translation,
                        std::get<AABBCollider>(colA.Shape), tcA.Translation);
                    swapped = true;
                }
                
                if (manifold.IsColliding) {
                    // Normal points from B to A
                    glm::vec3 normal = swapped ? -manifold.Normal : manifold.Normal;
                    
                    // --- Resolve Penetration (Positional Correction) ---
                    const float percent = 0.2f; // mostly 0.2 to 0.8
                    const float slop = 0.01f; // mostly 0.01 to 0.1
                    float invMassA = rbA.Body->GetInverseMass();
                    float invMassB = rbB.Body->GetInverseMass();
                    float totalInvMass = invMassA + invMassB;
                    
                    if (totalInvMass == 0.0f) continue;
                    
                    glm::vec3 correction = (std::max(manifold.PenetrationDepth - slop, 0.0f) / totalInvMass) * percent * normal;
                    
                    if (invMassA > 0.0f) {
                        tcA.Translation += invMassA * correction;
                        rbA.Body->SetPosition(tcA.Translation);
                    }
                    if (invMassB > 0.0f) {
                        tcB.Translation -= invMassB * correction;
                        rbB.Body->SetPosition(tcB.Translation);
                    }
                    
                    // --- Resolve Velocity (Impulse) ---
                    glm::vec3 rv = rbB.Body->GetVelocity() - rbA.Body->GetVelocity();
                    float velAlongNormal = glm::dot(rv, normal);
                    
                    if (velAlongNormal < 0) continue; // Moving apart
                    
                    float e = 0.5f; // Restitution (bounciness)
                    float j = -(1.0f + e) * velAlongNormal;
                    j /= totalInvMass;
                    
                    glm::vec3 impulse = j * normal;
                    
                    if (invMassA > 0.0f) {
                        rbA.Body->AddImpulse(-impulse);
                    }
                    if (invMassB > 0.0f) {
                        rbB.Body->AddImpulse(impulse);
                    }
                }
            }
        }
    }

}
