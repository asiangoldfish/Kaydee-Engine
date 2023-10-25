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
        virtual ~ImGuiLayer();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onEvent(Event& event) override;

        void begin();
        void end();

        void setBlockEvents(bool block) { blockEvents = block; }

    private:
        bool blockEvents = true;
        float time;
    };
}
