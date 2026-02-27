#include "Window.h"
#include "Logger.h"
#include "Input.h"

namespace VE {
    Window::Window(const WindowProps& props) : m_Data(props) {
        VE_CORE_INFO("Pencere oluşturuluyor: {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!glfwInit()) {
            VE_CORE_CRITICAL("GLFW başlatılamadı!");
            return;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
        
        if (!m_Window) {
            VE_CORE_CRITICAL("GLFW Penceresi oluşturulamadı!");
            return;
        }

        glfwSetWindowUserPointer(m_Window, this);

        // Key callbacks
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (action == GLFW_PRESS) Input::UpdateKey(key, true);
            else if (action == GLFW_RELEASE) Input::UpdateKey(key, false);
        });

        // Mouse button callbacks
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            if (action == GLFW_PRESS) Input::UpdateMouseButton(button, true);
            else if (action == GLFW_RELEASE) Input::UpdateMouseButton(button, false);
        });

        // Mouse position callbacks
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
            Input::UpdateMousePosition(xpos, ypos);
        });
    }

    Window::~Window() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        VE_CORE_INFO("Pencere kapatıldı.");
    }
}
