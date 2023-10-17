#pragma once

#include "Core/Input.h"

namespace Kaydee {

    class LinuxInput : public Input
    {
    protected:
        virtual bool isKeyPressedImpl(int keycode) override;
        virtual bool isMouseButtonPressedImpl(int button) override;
        virtual float getMouseXImpl() override;
        virtual float getMouseYImpl() override;
        virtual std::pair<float, float> getMousePositionImpl() override;
    };

}
