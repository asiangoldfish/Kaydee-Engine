#ifndef __IMGUI_LAYER_H__
#define __IMGUI_LAYER_H__

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

        void begin();
        void end();

    private:
        float time;
    };
}

#endif