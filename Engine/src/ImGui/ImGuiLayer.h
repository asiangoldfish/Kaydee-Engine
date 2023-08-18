#ifndef __IMGUI_LAYER_H__
#define __IMGUI_LAYER_H__

#include "Core/Layer.h"

namespace Kaydee {
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate() override;
        virtual void onEvent(Event& e) override;

        void begin();
        void end();
    };
}

#endif