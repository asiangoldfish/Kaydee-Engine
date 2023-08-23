#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace Kaydee {
    enum class RendererAPI
    {
        NONE = 0,
        OPENGL = 1
    };

    class Renderer
    {
    public:
        static inline RendererAPI getAPI() { return rendererAPI; }

    private:
        static RendererAPI rendererAPI;
    };
}

#endif // __RENDERER_H__