#ifndef __LINUX__INPUT_H__
#define __LINUX__INPUT_H__

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

#endif // __LINUX__INPUT_H__