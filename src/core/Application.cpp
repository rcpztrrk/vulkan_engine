#include "Application.h"
#include "Logger.h"

namespace VE {
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        Logger::Init();
        m_Window = std::make_unique<Window>(WindowProps("Vulkan Engine Faz 0"));
    }

    Application::~Application() {
    }

    void Application::Run() {
        VE_CORE_TRACE("Uygulama döngüsü başlatıldı.");
        
        while (!m_Window->ShouldClose()) {
            m_Window->PollEvents();
        }
    }
}
