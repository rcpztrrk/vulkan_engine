#include "Input.h"

namespace VE {

    std::unordered_map<int, bool> Input::s_Keys;
    std::unordered_map<int, bool> Input::s_LastKeys;
    std::unordered_map<int, bool> Input::s_MouseButtons;
    glm::vec2 Input::s_MousePosition = { 0.0f, 0.0f };

    bool Input::IsKeyPressed(int keycode) {
        return s_Keys[keycode];
    }

    bool Input::IsKeyJustPressed(int keycode) {
        return s_Keys[keycode] && !s_LastKeys[keycode];
    }

    bool Input::IsMouseButtonPressed(int button) {
        return s_MouseButtons[button];
    }

    glm::vec2 Input::GetMousePosition() {
        return s_MousePosition;
    }

    float Input::GetMouseX() {
        return s_MousePosition.x;
    }

    float Input::GetMouseY() {
        return s_MousePosition.y;
    }

    void Input::UpdateKey(int keycode, bool pressed) {
        s_Keys[keycode] = pressed;
    }

    void Input::UpdateMouseButton(int button, bool pressed) {
        s_MouseButtons[button] = pressed;
    }

    void Input::UpdateMousePosition(double x, double y) {
        s_MousePosition = { (float)x, (float)y };
    }

    void Input::TransitionStates() {
        s_LastKeys = s_Keys;
    }

}
