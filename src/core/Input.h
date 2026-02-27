#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

namespace VE {

    class Input {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();

        // Internal use by Window class
        static void UpdateKey(int keycode, bool pressed);
        static void UpdateMouseButton(int button, bool pressed);
        static void UpdateMousePosition(double x, double y);

        static void TransitionStates();

        static bool IsKeyJustPressed(int keycode);

    private:
        static std::unordered_map<int, bool> s_Keys;
        static std::unordered_map<int, bool> s_LastKeys;
        static std::unordered_map<int, bool> s_MouseButtons;
        static glm::vec2 s_MousePosition;
    };
}
