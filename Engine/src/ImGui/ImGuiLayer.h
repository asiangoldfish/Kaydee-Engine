#pragma once

#include "Core/Layer.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Kaydee {
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onEvent(Event& event) override;

        void begin();
        void end();

    private:
        //inline bool onKeyPressedEvent(Kaydee::MouseButtonPressedEvent& event)
        //{
        //    return true;
        //}

    private:
        float time;
    };
}
