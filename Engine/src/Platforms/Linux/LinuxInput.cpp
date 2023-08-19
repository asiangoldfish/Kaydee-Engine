#include "Platforms/Linux/LinuxInput.h"
#include "Core/Application.h"
#include <GLFW/glfw3.h>

namespace Kaydee {
    Input* Input::instance = new LinuxInput();

    bool LinuxInput::isKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(
          Application::get().getWindow().getNativeWindow());

        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::isMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(
          Application::get().getWindow().getNativeWindow());

        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    float LinuxInput::getMouseXImpl()
    {
        auto [x, y] = getMousePositionImpl();
        return x;
    }

    float LinuxInput::getMouseYImpl()
    {
        auto [x, y] = getMousePositionImpl();
        return y;
    }

    std::pair<float, float> LinuxInput::getMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(
          Application::get().getWindow().getNativeWindow());

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }
}