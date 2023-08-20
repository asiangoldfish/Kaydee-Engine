#include "Platforms/OpenGL/OpenGLContext.h"

#include "kdpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Kaydee {
    OpenGLContext::OpenGLContext(GLFWwindow* _windowHandle)
      : windowHandle(_windowHandle)
    {
        KD_CORE_ASSERT(windowHandle, "WindowHandle is null");
    }

    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        KD_CORE_ASSERT(status, "Failed to initialize Glad!");

        std::cout << "OpenGL Info: " << std::endl;

        std::cout << std::left << std::setw(15)
                  << "Vendor: " << glGetString(GL_VENDOR) << std::endl;

        std::cout << std::left << std::setw(15)
                  << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

        std::cout << std::left << std::setw(15)
                  << "Version: " << glGetString(GL_VERSION) << std::endl;
    }

    void OpenGLContext::swapBuffers()
    {
        glfwSwapBuffers(windowHandle);
    }
}
