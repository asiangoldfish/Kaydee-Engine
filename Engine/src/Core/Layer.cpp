#include "Core/Layer.h"
#include "kdpch.h"

namespace Kaydee {
    Layer::Layer(const std::string& name)
      : debugName(name)
    {
    }

    Layer::~Layer() {}
}