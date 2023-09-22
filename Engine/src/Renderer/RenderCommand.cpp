#include "kdpch.h"
#include "Renderer/RenderCommand.h"

#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Kaydee {
    RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
}