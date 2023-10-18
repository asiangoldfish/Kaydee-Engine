#pragma once

#include "Core.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"

/**
 * Input poll. Lets any class poll for input.
 */

namespace Kaydee {

    // This class is a singleton so it can be used anywhere
    class Input
    {
    public:
        // -----
        // Keyboard
        // -----
        static bool isKeyPressed(int keycode);

        // -----
        // Mouse
        // -----
        static bool isMouseButtonPressed(int button);
        // Get mouse position in screen space
        static std::pair<float, float> getMousePosition();
        static float getMouseX();
        static float getMouseY();
    };
}
