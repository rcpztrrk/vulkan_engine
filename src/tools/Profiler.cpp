#include "Profiler.h"
#include <imgui.h>
#include <numeric>

namespace VE {

    float Profiler::s_FrameTime = 0.0f;
    float Profiler::s_FPS = 0.0f;
    std::vector<float> Profiler::s_FrameTimeHistory;

    void Profiler::Update(float deltaTime) {
        s_FrameTime = deltaTime * 1000.0f; // ms
        s_FPS = 1.0f / deltaTime;

        s_FrameTimeHistory.push_back(s_FrameTime);
        if (s_FrameTimeHistory.size() > HISTORY_SIZE) {
            s_FrameTimeHistory.erase(s_FrameTimeHistory.begin());
        }
    }

    void Profiler::OnUIRender() {
        ImGui::Begin("Performance Profiler");

        ImGui::Text("Frame Time: %.3f ms", s_FrameTime);
        ImGui::Text("FPS: %.1f", s_FPS);

        if (!s_FrameTimeHistory.empty()) {
            float maxFrameTime = *std::max_element(s_FrameTimeHistory.begin(), s_FrameTimeHistory.end());
            ImGui::PlotLines("GPU Frame Time", s_FrameTimeHistory.data(), (int)s_FrameTimeHistory.size(), 0, nullptr, 0.0f, maxFrameTime * 1.2f, ImVec2(0, 80));
        }

        ImGui::End();
    }

}
