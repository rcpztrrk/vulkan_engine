#include "Application.h"
#include "Logger.h"
#include "Components.h"
#include "tools/Profiler.h"
#include "core/Input.h"
#include "physics/Colliders.h"

namespace VE {
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        Logger::Init();
        m_Window = std::make_unique<Window>(WindowProps("Vulkan Engine - Phase 5"));
        m_Renderer = std::make_unique<VulkanRenderer>(m_Window->GetNativeWindow());
        m_Renderer->Init();

        m_PhysicsEngine = std::make_unique<PhysicsEngine>();
        m_Scene = std::make_unique<Scene>();
        m_Camera = std::make_unique<FlyCamera>(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
        m_LastFrameTime = std::chrono::high_resolution_clock::now();

        // Create floor
        auto floor = m_Scene->CreateEntity("Floor");
        auto& floorTc = m_Scene->GetRegistry().get<TransformComponent>(floor);
        floorTc.Translation = glm::vec3(0.0f, -5.0f, 0.0f);
        floorTc.Scale = glm::vec3(20.0f, 0.1f, 20.0f);
        m_Scene->GetRegistry().emplace<MeshComponent>(floor, "assets/models/cube.obj"); 
        
        auto& floorRb = m_Scene->GetRegistry().emplace<RigidBodyComponent>(floor);
        floorRb.Body->SetMass(0.0f); // Static
        m_Scene->GetRegistry().emplace<ColliderComponent>(floor, AABBCollider{ floorTc.Scale });

        // Create multiple test entities
        for (int i = 0; i < 3; i++) {
            auto entity = m_Scene->CreateEntity("Cube " + std::to_string(i));
            
            auto& tc = m_Scene->GetRegistry().get<TransformComponent>(entity);
            tc.Translation = glm::vec3(i * 5.0f - 5.0f, i * 4.0f + 5.0f, 0.0f);
            tc.Rotation = glm::vec3(0.0f); // Keep rotation 0 for AABB
            
            m_Scene->GetRegistry().emplace<MeshComponent>(entity, "assets/models/cube.obj");
            auto& rb = m_Scene->GetRegistry().emplace<RigidBodyComponent>(entity);
            rb.Body->SetMass(1.0f);
            m_Scene->GetRegistry().emplace<ColliderComponent>(entity, AABBCollider{ tc.Scale });
        }
    }

    Application::~Application() {
    }

    void Application::Run() {
        VE_CORE_TRACE("Application loop started.");
        
        while (!m_Window->ShouldClose()) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            m_DeltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - m_LastFrameTime).count();
            m_LastFrameTime = currentTime;

            m_Window->PollEvents();
            m_Camera->OnUpdate(m_DeltaTime);
            Profiler::Update(m_DeltaTime);

            const float fixedDt = 1.0f / 60.0f;
            static float accumulator = 0.0f;
            accumulator += m_DeltaTime;

            while (accumulator >= fixedDt) {
                m_PhysicsEngine->Update(fixedDt, m_Scene->GetRegistry());
                accumulator -= fixedDt;
            }

            m_Renderer->DrawFrame(m_Scene->GetRegistry(), *m_Camera);
            Input::TransitionStates();
        }
    }
}
