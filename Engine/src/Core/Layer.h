#pragma once

#include "Events/Event.h"
#include "kdpch.h"
#include "Core/Timestep.h"

namespace Kaydee {
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(Timestep ts) {}
        virtual void onEvent(Event& event) {}
        virtual void onImGuiRender() {}

        // Only for debugging
        inline const std::string& getName() const { return debugName; }

    protected:
        std::string debugName;
    };
}
