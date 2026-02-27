#include "Camera.h"
#include "core/Input.h"
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace VE {

    FlyCamera::FlyCamera(float fov, float aspectRatio, float nearClip, float farClip)
        : m_Fov(fov), m_NearClip(nearClip), m_FarClip(farClip) {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), aspectRatio, m_NearClip, m_FarClip);
        m_ProjectionMatrix[1][1] *= -1; // Vulkan Y correction
        UpdateViewMatrix();
    }

    void FlyCamera::OnUpdate(float dt) {
        // Don't update camera if UI is capturing input
        if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard) {
            m_FirstMouse = true; // Reset mouse state to avoid jumps
            return;
        }

        // Movement
        float velocity = m_MoveSpeed * dt;
        if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) velocity *= m_SprintMultiplier;

        if (Input::IsKeyPressed(GLFW_KEY_W)) m_Position += m_Front * velocity;
        if (Input::IsKeyPressed(GLFW_KEY_S)) m_Position -= m_Front * velocity;
        if (Input::IsKeyPressed(GLFW_KEY_A)) m_Position -= m_Right * velocity;
        if (Input::IsKeyPressed(GLFW_KEY_D)) m_Position += m_Right * velocity;
        if (Input::IsKeyPressed(GLFW_KEY_Q)) m_Position += m_WorldUp * velocity;
        if (Input::IsKeyPressed(GLFW_KEY_E)) m_Position -= m_WorldUp * velocity;

        // Rotation (Mouse Look) - Only if Right Mouse Button is pressed
        if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
            float xpos = Input::GetMouseX();
            float ypos = Input::GetMouseY();

            if (m_FirstMouse) {
                m_LastX = xpos;
                m_LastY = ypos;
                m_FirstMouse = false;
            }

            float xoffset = xpos - m_LastX;
            float yoffset = m_LastY - ypos; // reversed since y-coordinates go from bottom to top
            m_LastX = xpos;
            m_LastY = ypos;

            xoffset *= m_MouseSensitivity;
            yoffset *= m_MouseSensitivity;

            m_Yaw += xoffset;
            m_Pitch += yoffset;

            if (m_Pitch > 89.0f) m_Pitch = 89.0f;
            if (m_Pitch < -89.0f) m_Pitch = -89.0f;
        } else {
            m_FirstMouse = true;
        }

        UpdateViewMatrix();
    }

    void FlyCamera::SetAspectRatio(float aspect) {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), aspect, m_NearClip, m_FarClip);
        m_ProjectionMatrix[1][1] *= -1;
    }

    void FlyCamera::UpdateViewMatrix() {
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));

        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

}
