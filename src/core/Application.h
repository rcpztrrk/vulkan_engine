#pragma once

#include "Window.h"
#include <memory>

namespace VE {
    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();
        
        static Application& Get() { return *s_Instance; }
        Window& GetWindow() { return *m_Window; }

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        
        static Application* s_Instance;
    };
}
