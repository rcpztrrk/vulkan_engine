#pragma once

#include "Colliders.h"
#include <glm/glm.hpp>

namespace VE {

    struct CollisionManifold {
        bool IsColliding = false;
        glm::vec3 Normal{ 0.0f };      // the direction to move object A to resolve the collision
        float PenetrationDepth = 0.0f; // how far A is inside B
        glm::vec3 ContactPoint{ 0.0f }; // point of contact (optional, useful for advanced resolution)
    };

    class Collision {
    public:
        // Returns true if intersecting, populates manifold with resolution data.
        static CollisionManifold CheckSphereSphere(
            const SphereCollider& sphereA, const glm::vec3& posA,
            const SphereCollider& sphereB, const glm::vec3& posB);

        static CollisionManifold CheckAABBAABB(
            const AABBCollider& aabbA, const glm::vec3& posA,
            const AABBCollider& aabbB, const glm::vec3& posB);

        static CollisionManifold CheckSphereAABB(
            const SphereCollider& sphere, const glm::vec3& spherePos,
            const AABBCollider& aabb, const glm::vec3& aabbPos);
    };

}
