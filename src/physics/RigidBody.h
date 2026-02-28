#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace VE {

    class RigidBody {
    public:
        RigidBody();
        ~RigidBody() = default;

        void Update(float dt);

        // Force & Torque
        void AddForce(const glm::vec3& force) { m_ForceAccumulator += force; }
        void AddTorque(const glm::vec3& torque) { m_TorqueAccumulator += torque; }
        void AddImpulse(const glm::vec3& impulse) { m_Velocity += impulse * m_InverseMass; }
        void AddAngularImpulse(const glm::vec3& impulse); // To be implemented

        // Getters
        const glm::vec3& GetPosition() const { return m_Position; }
        const glm::quat& GetOrientation() const { return m_Orientation; }
        const glm::vec3& GetVelocity() const { return m_Velocity; }
        const glm::vec3& GetAngularVelocity() const { return m_AngularVelocity; }
        float GetMass() const { return m_Mass; }
        float GetInverseMass() const { return m_InverseMass; }

        // Setters
        void SetPosition(const glm::vec3& position) { m_Position = position; }
        void SetOrientation(const glm::quat& orientation) { m_Orientation = orientation; }
        void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; }
        void SetAngularVelocity(const glm::vec3& angularVelocity) { m_AngularVelocity = angularVelocity; }
        void SetMass(float mass);
        void SetGravityScale(float scale) { m_GravityScale = scale; }

    private:
        // Linear
        glm::vec3 m_Position{ 0.0f };
        glm::vec3 m_Velocity{ 0.0f };
        glm::vec3 m_Acceleration{ 0.0f };
        glm::vec3 m_ForceAccumulator{ 0.0f };

        // Angular
        glm::quat m_Orientation{ 1.0f, 0.0f, 0.0f, 0.0f }; // Identity quaternion
        glm::vec3 m_AngularVelocity{ 0.0f };
        glm::vec3 m_AngularAcceleration{ 0.0f };
        glm::vec3 m_TorqueAccumulator{ 0.0f };
        glm::mat3 m_InertiaTensor{ 1.0f };
        glm::mat3 m_InverseInertiaTensor{ 1.0f };

        float m_Mass = 1.0f;
        float m_InverseMass = 1.0f;
        float m_GravityScale = 1.0f;

        float m_LinearDamping = 0.01f;
        float m_AngularDamping = 0.01f;
    };

}
