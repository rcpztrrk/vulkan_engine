#include "Application.h"
#include "Logger.h"
#include "renderer/VulkanRenderer.h"

namespace VE {
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        Logger::Init();
        m_Window = std::make_unique<Window>(WindowProps("Vulkan Engine Faz 1"));
        m_Renderer = std::make_unique<VulkanRenderer>(m_Window->GetNativeWindow());
        m_Renderer->Init();
    }

    Application::~Application() {
    }

    void Application::Run() {
        VE_CORE_TRACE("Uygulama döngüsü başlatıldı.");
        
        while (!m_Window->ShouldClose()) {
            m_Window->PollEvents();
            m_Renderer->DrawFrame();
        }
    }
}
