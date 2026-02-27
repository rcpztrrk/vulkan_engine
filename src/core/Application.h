#pragma once

#include "Window.h"
#include "renderer/VulkanRenderer.h"
#include "physics/PhysicsEngine.h"
#include "Scene.h"
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
        std::unique_ptr<VulkanRenderer> m_Renderer;
        std::unique_ptr<PhysicsEngine> m_PhysicsEngine; // Added PhysicsEngine member
        std::unique_ptr<Scene> m_Scene; // Replaced m_TestBody with m_Scene
        bool m_Running = true;
        
        static Application* s_Instance;
    };
}
