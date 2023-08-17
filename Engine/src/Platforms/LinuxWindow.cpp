#include "Platforms/LinuxWindow.h"
#include "Core/Core.h"
#include "Core/Log.h"
#include "kdpch.h"

namespace Kaydee {
    static bool glfwInitialized = false;

    Window* Window::create(const WindowProps& props)
    {
        return new LinuxWindow(props);
    }

    LinuxWindow::LinuxWindow(const WindowProps& props)
    {
        init(props);
    }

    LinuxWindow::~LinuxWindow()
    {
        shutdown();
    }

    void LinuxWindow::init(const WindowProps& props)
    {
        windowData.Title = props.title;
        windowData.Width = props.width;
        windowData.Height = props.height;

        KD_CORE_INFO("Creating window {0} ({1}, {2})",
                     props.title,
                     props.width,
                     props.height);

        if (!glfwInitialized) {
            // TODO - glfwTerminate on system shutdown
            int success = glfwInit();
            KD_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwInitialized = true;
        }

        window = glfwCreateWindow((int)props.width,
                                  (int)props.height,
                                  windowData.Title.c_str(),
                                  nullptr,
                                  nullptr);
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, &windowData);
        setVSync(true);
    }

    void LinuxWindow::shutdown()
    {
        glfwDestroyWindow(window);
    }

    void LinuxWindow::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    void LinuxWindow::setVSync(bool enabled)
    {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }

        windowData.VSync = enabled;
    }

    bool LinuxWindow::isVSync() const
    {
        return windowData.VSync;
    }
}