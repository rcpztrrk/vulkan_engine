#include "RigidBody.h"

namespace VE {

    RigidBody::RigidBody() {
        SetMass(1.0f);
    }

    void RigidBody::SetMass(float mass) {
        m_Mass = mass;
        if (m_Mass > 0.0f) {
            m_InverseMass = 1.0f / m_Mass;
        } else {
            m_InverseMass = 0.0f; // Static object
        }
    }

    void RigidBody::Update(float dt) {
        if (m_InverseMass <= 0.0f) return;

        // Semi-implicit Euler integration
        m_Acceleration = m_ForceAccumulator * m_InverseMass;
        m_Velocity += m_Acceleration * dt;
        
        // Apply damping
        m_Velocity *= (1.0f - m_LinearDamping);

        m_Position += m_Velocity * dt;

        // Clear forces for next frame
        m_ForceAccumulator = glm::vec3(0.0f);
    }

}
