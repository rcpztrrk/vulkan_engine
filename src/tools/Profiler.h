#pragma once

#include <vector>
#include <string>

namespace VE {

    class Profiler {
    public:
        static void OnUIRender();
        
        // Call this once per frame
        static void Update(float deltaTime);

    private:
        static float s_FrameTime;
        static float s_FPS;
        static std::vector<float> s_FrameTimeHistory;
        static const int HISTORY_SIZE = 100;
    };

}
