#pragma once

#include <glm/glm.hpp>

namespace VE {

    class RigidBody {
    public:
        RigidBody();
        ~RigidBody() = default;

        void Update(float dt);

        void AddForce(const glm::vec3& force) { m_ForceAccumulator += force; }
        void AddImpulse(const glm::vec3& impulse) { m_Velocity += impulse * m_InverseMass; }

        // Getters
        const glm::vec3& GetPosition() const { return m_Position; }
        const glm::vec3& GetVelocity() const { return m_Velocity; }
        float GetMass() const { return m_Mass; }
        float GetInverseMass() const { return m_InverseMass; }

        // Setters
        void SetPosition(const glm::vec3& position) { m_Position = position; }
        void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; }
        void SetMass(float mass);
        void SetGravityScale(float scale) { m_GravityScale = scale; }

    private:
        glm::vec3 m_Position{ 0.0f };
        glm::vec3 m_Velocity{ 0.0f };
        glm::vec3 m_Acceleration{ 0.0f };
        glm::vec3 m_ForceAccumulator{ 0.0f };

        float m_Mass = 1.0f;
        float m_InverseMass = 1.0f;
        float m_GravityScale = 1.0f;

        float m_LinearDamping = 0.01f;
    };

}
