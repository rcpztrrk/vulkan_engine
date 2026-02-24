#pragma once

#include "Window.h"
#include <memory>

namespace VE {
    class VulkanRenderer;

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();
        
        static Application& Get() { return *s_Instance; }
        Window& GetWindow() { return *m_Window; }

    private:
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<VulkanRenderer> m_Renderer;
        bool m_Running = true;
        
        static Application* s_Instance;
    };
}
