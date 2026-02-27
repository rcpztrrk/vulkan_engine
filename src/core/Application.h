#pragma once

#include "Window.h"
#include "renderer/VulkanRenderer.h"
#include "physics/PhysicsEngine.h"
#include "renderer/Camera.h"
#include "Scene.h"
#include <memory>
#include <chrono>

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
        std::unique_ptr<PhysicsEngine> m_PhysicsEngine; 
        std::unique_ptr<Scene> m_Scene;
        std::unique_ptr<FlyCamera> m_Camera;
        
        bool m_Running = true;
        float m_DeltaTime = 0.0f;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_LastFrameTime;
        
        static Application* s_Instance;
    };
}
