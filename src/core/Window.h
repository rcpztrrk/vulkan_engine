#pragma once

#include <string>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace VE {
    struct WindowProps {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title = "Vulkan Engine",
                    uint32_t width = 1280,
                    uint32_t height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    class Window {
    public:
        Window(const WindowProps& props);
        ~Window();

        bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }
        void PollEvents() { glfwPollEvents(); }
        
        GLFWwindow* GetNativeWindow() const { return m_Window; }

    private:
        GLFWwindow* m_Window;
        WindowProps m_Data;
    };
}
