#include "Collision.h"
#include <algorithm>
#include <cmath>

namespace VE {

    CollisionManifold Collision::CheckSphereSphere(
        const SphereCollider& sphereA, const glm::vec3& posA,
        const SphereCollider& sphereB, const glm::vec3& posB) {
        
        CollisionManifold manifold;
        glm::vec3 centerA = posA + sphereA.Offset;
        glm::vec3 centerB = posB + sphereB.Offset;
        
        glm::vec3 diff = centerA - centerB;
        float distSq = glm::dot(diff, diff);
        float radiusSum = sphereA.Radius + sphereB.Radius;
        
        if (distSq < radiusSum * radiusSum) {
            manifold.IsColliding = true;
            float dist = std::sqrt(distSq);
            
            if (dist == 0.0f) {
                manifold.PenetrationDepth = sphereA.Radius;
                manifold.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
            } else {
                manifold.PenetrationDepth = radiusSum - dist;
                manifold.Normal = diff / dist; // pointing from B to A
            }
        }
        
        return manifold;
    }

    CollisionManifold Collision::CheckAABBAABB(
        const AABBCollider& aabbA, const glm::vec3& posA,
        const AABBCollider& aabbB, const glm::vec3& posB) {
        
        CollisionManifold manifold;
        
        glm::vec3 centerA = posA + aabbA.Offset;
        glm::vec3 centerB = posB + aabbB.Offset;
        
        glm::vec3 minA = centerA - aabbA.HalfExtents;
        glm::vec3 maxA = centerA + aabbA.HalfExtents;
        
        glm::vec3 minB = centerB - aabbB.HalfExtents;
        glm::vec3 maxB = centerB + aabbB.HalfExtents;
        
        if (maxA.x < minB.x || minA.x > maxB.x) return manifold;
        if (maxA.y < minB.y || minA.y > maxB.y) return manifold;
        if (maxA.z < minB.z || minA.z > maxB.z) return manifold;
        
        manifold.IsColliding = true;
        
        // Find penetration depth on each axis
        float overlapXLeft = maxA.x - minB.x;
        float overlapXRight = maxB.x - minA.x;
        float overlapX = std::min(overlapXLeft, overlapXRight);
        
        float overlapYBottom = maxA.y - minB.y;
        float overlapYTop = maxB.y - minA.y;
        float overlapY = std::min(overlapYBottom, overlapYTop);
        
        float overlapZNear = maxA.z - minB.z;
        float overlapZFar = maxB.z - minA.z;
        float overlapZ = std::min(overlapZNear, overlapZFar);
        
        // Find axis of least penetration
        if (overlapX < overlapY && overlapX < overlapZ) {
            manifold.PenetrationDepth = overlapX;
            manifold.Normal = (overlapXLeft < overlapXRight) ? glm::vec3(-1.0f, 0.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
        } else if (overlapY < overlapX && overlapY < overlapZ) {
            manifold.PenetrationDepth = overlapY;
            manifold.Normal = (overlapYBottom < overlapYTop) ? glm::vec3(0.0f, -1.0f, 0.0f) : glm::vec3(0.0f, 1.0f, 0.0f);
        } else {
            manifold.PenetrationDepth = overlapZ;
            manifold.Normal = (overlapZNear < overlapZFar) ? glm::vec3(0.0f, 0.0f, -1.0f) : glm::vec3(0.0f, 0.0f, 1.0f);
        }
        
        return manifold;
    }

    CollisionManifold Collision::CheckSphereAABB(
        const SphereCollider& sphere, const glm::vec3& spherePos,
        const AABBCollider& aabb, const glm::vec3& aabbPos) {
        
        CollisionManifold manifold;
        
        glm::vec3 centerSphere = spherePos + sphere.Offset;
        glm::vec3 centerAABB = aabbPos + aabb.Offset;
        
        glm::vec3 minAABB = centerAABB - aabb.HalfExtents;
        glm::vec3 maxAABB = centerAABB + aabb.HalfExtents;
        
        // Find closest point on AABB to sphere center
        glm::vec3 closestPoint;
        closestPoint.x = std::max(minAABB.x, std::min(centerSphere.x, maxAABB.x));
        closestPoint.y = std::max(minAABB.y, std::min(centerSphere.y, maxAABB.y));
        closestPoint.z = std::max(minAABB.z, std::min(centerSphere.z, maxAABB.z));
        
        glm::vec3 diff = centerSphere - closestPoint;
        float distSq = glm::dot(diff, diff);
        
        if (distSq < sphere.Radius * sphere.Radius) {
            manifold.IsColliding = true;
            
            float dist = std::sqrt(distSq);
            if (dist == 0.0f) {
                // Sphere center is inside AABB. This is a bit tricky, simple resolution:
                manifold.PenetrationDepth = sphere.Radius;
                manifold.Normal = glm::vec3(0.0f, 1.0f, 0.0f); // Default push up
            } else {
                manifold.PenetrationDepth = sphere.Radius - dist;
                manifold.Normal = diff / dist; // Pointing from AABB to Sphere
            }
        }
        
        return manifold;
    }

}
