#ifndef __OPENGL_CONTEXT_H__
#define __OPENGL_CONTEXT_H__

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Kaydee {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void init() override;
        virtual void swapBuffers() override;

    private:
        GLFWwindow* windowHandle;
    };

}

#endif