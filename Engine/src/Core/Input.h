#pragma once

/**
 * Input poll. Lets any class poll for input.
 */

namespace Kaydee {

    // This class is a singleton so it can be used anywhere
    class Input
    {
    public:
        inline static bool isKeyPressed(int keycode)
        {
            return instance->isKeyPressedImpl(keycode);
        }

        inline static bool isMouseButtonPressed(int button)
        {
            return instance->isMouseButtonPressedImpl(button);
        }

        // Get mouse position in screen space
        inline static std::pair<float, float> getMousePosition()
        {
            return { instance->getMouseXImpl(), instance->getMouseYImpl() };
        }

        inline static bool getMouseX() { return instance->getMouseXImpl(); }
        inline static bool getMouseY() { return instance->getMouseYImpl(); }

    protected:
        // Each platform will implement this
        virtual bool isKeyPressedImpl(int keycode) = 0;
        virtual bool isMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> getMousePositionImpl() = 0;
        virtual float getMouseXImpl() = 0;
        virtual float getMouseYImpl() = 0;

    private:
        static Input* instance;
    };
}
