#include "Window.h"
#include "Logger.h"

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
        }
    }

    Window::~Window() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        VE_CORE_INFO("Pencere kapatıldı.");
    }
}
