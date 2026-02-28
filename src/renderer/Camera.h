#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace VE {

    class FlyCamera {
    public:
        FlyCamera(float fov, float aspectRatio, float nearClip, float farClip);

        void OnUpdate(float dt);
        
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::vec3& GetPosition() const { return m_Position; }
        
        void SetAspectRatio(float aspect);

        float m_MoveSpeed = 10.0f;
        float m_SprintMultiplier = 2.5f;
        float m_MouseSensitivity = 0.1f;

    private:
        void UpdateViewMatrix();

        glm::vec3 m_Position = { 15.0f, 15.0f, 15.0f };
        glm::vec3 m_Front = { -1.0f, -1.0f, -1.0f };
        glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };

        float m_Yaw = -135.0f;
        float m_Pitch = -35.0f;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;

        float m_Fov;
        float m_NearClip;
        float m_FarClip;

        bool m_FirstMouse = true;
        float m_LastX = 640.0f;
        float m_LastY = 360.0f;
    };

}
