#include "Application.h"
#include "Logger.h"
#include "Components.h"

namespace VE {
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        Logger::Init();
        m_Window = std::make_unique<Window>(WindowProps("Vulkan Engine Faz 4 - ECS"));
        m_Renderer = std::make_unique<VulkanRenderer>(m_Window->GetNativeWindow());
        m_Renderer->Init();

        m_PhysicsEngine = std::make_unique<PhysicsEngine>();
        m_Scene = std::make_unique<Scene>();

        // Create floor
        auto floor = m_Scene->CreateEntity("Floor");
        auto& floorTc = m_Scene->GetRegistry().get<TransformComponent>(floor);
        floorTc.Translation = glm::vec3(0.0f, -5.0f, 0.0f);
        floorTc.Scale = glm::vec3(20.0f, 0.1f, 20.0f);
        m_Scene->GetRegistry().emplace<MeshComponent>(floor, "assets/models/cube.obj"); 

        // Create multiple test entities
        for (int i = 0; i < 3; i++) {
            auto entity = m_Scene->CreateEntity("Cube " + std::to_string(i));
            
            auto& tc = m_Scene->GetRegistry().get<TransformComponent>(entity);
            tc.Translation = glm::vec3(i * 5.0f - 5.0f, i * 2.0f, 0.0f);
            tc.Rotation = glm::vec3(0.0f, glm::radians(i * 45.0f), 0.0f);
            
            m_Scene->GetRegistry().emplace<MeshComponent>(entity, "assets/models/cube.obj");
            m_Scene->GetRegistry().emplace<RigidBodyComponent>(entity);
        }
    }

    Application::~Application() {
    }

    void Application::Run() {
        VE_CORE_TRACE("Uygulama döngüsü başlatıldı.");
        
        float lastFrameTime = 0.0f;
        
        while (!m_Window->ShouldClose()) {
            float time = (float)glfwGetTime();
            float dt = time - lastFrameTime;
            lastFrameTime = time;

            m_Window->PollEvents();

            const float fixedDt = 1.0f / 60.0f;
            static float accumulator = 0.0f;
            accumulator += dt;

            while (accumulator >= fixedDt) {
                m_PhysicsEngine->Update(fixedDt, m_Scene->GetRegistry());
                accumulator -= fixedDt;
            }

            m_Renderer->DrawFrame(m_Scene->GetRegistry());
        }
    }
}
