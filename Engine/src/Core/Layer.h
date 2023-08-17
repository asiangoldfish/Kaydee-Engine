#ifndef __LAYER_H__
#define __LAYER_H__

#include "Events/Event.h"
#include "kdpch.h"

namespace Kaydee {
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onEvent(Event& event) {}

        // Only for debugging
        inline const std::string& getName() const { return debugName; }

    protected:
        std::string debugName;
    };
}

#endif