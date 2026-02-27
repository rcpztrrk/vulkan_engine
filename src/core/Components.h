#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "physics/RigidBody.h"
#include <memory>

namespace VE {

    struct TagComponent {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag) : Tag(tag) {}
    };

    struct TransformComponent {
        glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f }; // Euler angles
        glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& translation) : Translation(translation) {}

        glm::mat4 GetTransform() const {
            return glm::translate(glm::mat4(1.0f), Translation)
                * glm::toMat4(glm::quat(Rotation))
                * glm::scale(glm::mat4(1.0f), Scale);
        }
    };

    struct MeshComponent {
        std::string FilePath;
        // This will eventually hold a reference to a Mesh object/asset
        
        MeshComponent() = default;
        MeshComponent(const MeshComponent&) = default;
        MeshComponent(const std::string& filePath) : FilePath(filePath) {}
    };

    struct RigidBodyComponent {
        std::shared_ptr<RigidBody> Body;
        
        RigidBodyComponent() { Body = std::make_shared<RigidBody>(); }
        RigidBodyComponent(const RigidBodyComponent&) = default;
    };

}
