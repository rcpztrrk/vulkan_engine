#pragma once

#include <glm/glm.hpp>
#include <variant>

namespace VE {

    enum class ColliderType {
        None,
        Sphere,
        AABB
    };

    struct SphereCollider {
        float Radius = 1.0f;
        glm::vec3 Offset{ 0.0f };
    };

    struct AABBCollider {
        glm::vec3 HalfExtents{ 0.5f };
        glm::vec3 Offset{ 0.0f };
    };

    struct ColliderComponent {
        ColliderType Type = ColliderType::None;

        // Since components should be easily copyable and standard, we can use std::variant or store multiple
        std::variant<SphereCollider, AABBCollider> Shape;

        ColliderComponent() = default;
        ColliderComponent(const SphereCollider& sphere) : Type(ColliderType::Sphere), Shape(sphere) {}
        ColliderComponent(const AABBCollider& aabb) : Type(ColliderType::AABB), Shape(aabb) {}
    };

}
