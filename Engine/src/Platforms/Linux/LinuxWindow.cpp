#include "Platforms/Linux/LinuxWindow.h"

#include "Core/Core.h"
#include "Core/Log.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Platforms/OpenGL/OpenGLContext.h"

#include "kdpch.h"

namespace Kaydee {
    static bool glfwInitialized = false;

    static void GLFWErrorCallback(int error, const char* description)
    {
        KD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

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
        if (context) {
            delete context;
            context = nullptr;
        }

        shutdown();
    }

    void LinuxWindow::init(const WindowProps& props)
    {
        windowData.title = props.title;
        windowData.width = props.width;
        windowData.height = props.height;

        KD_CORE_INFO("Creating window {0} ({1}, {2})",
                     props.title,
                     props.width,
                     props.height);

        if (!glfwInitialized) {
            // TODO - glfwTerminate on system shutdown
            int success = glfwInit();
            KD_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            glfwInitialized = true;
        }

        window = glfwCreateWindow((int)props.width,
                                  (int)props.height,
                                  windowData.title.c_str(),
                                  nullptr,
                                  nullptr);

        context = new OpenGLContext(window);
        context->init();

        glfwSetWindowUserPointer(window, &windowData);
        setVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(
          window, [](GLFWwindow* window, int width, int height) {
              WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
              data.width = width;
              data.height = height;

              WindowResizeEvent event(width, height);
              KD_CORE_WARN("{0} {1}", width, height);
              data.eventCallback(event);
          });

        glfwSetWindowIconifyCallback(
          window, [](GLFWwindow* window, int minimized) {
              WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
              data.minimized = minimized;
              WindowIconifyEvent event(minimized);
              data.eventCallback(event);
          });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetCharCallback(
          window, [](GLFWwindow* window, unsigned int keycode) {
              WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
              KeyTypedEvent event(keycode);
              data.eventCallback(event);
          });

        glfwSetKeyCallback(
          window,
          [](GLFWwindow* window, int key, int scancode, int action, int mods) {
              WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

              switch (action) {
                  case GLFW_PRESS: {
                      KeyPressedEvent event(key, 0);
                      data.eventCallback(event);
                      break;
                  }
                  case GLFW_RELEASE: {
                      KeyReleasedEvent event(key, 0);
                      data.eventCallback(event);
                      break;
                  }
                  case GLFW_REPEAT: {
                      KeyPressedEvent event(key, 1);
                      data.eventCallback(event);
                      break;
                  }
              }
          });

        glfwSetMouseButtonCallback(
          window, [](GLFWwindow* window, int button, int action, int mods) {
              WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

              switch (action) {
                  case GLFW_PRESS: {
                      MouseButtonPressedEvent event(button);
                      data.eventCallback(event);
                      break;
                  }
                  case GLFW_RELEASE: {
                      MouseButtonReleasedEvent event(button);
                      data.eventCallback(event);
                      break;
                  }
              }
          });

        glfwSetScrollCallback(
          window, [](GLFWwindow* window, double xOffset, double yOffset) {
              WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

              MouseScrolledEvent event((float)xOffset, (float)yOffset);
              data.eventCallback(event);
          });

        glfwSetCursorPosCallback(
          window, [](GLFWwindow* window, double xPos, double yPos) {
              WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

              MouseMovedEvent event((float)xPos, (float)yPos);
              data.eventCallback(event);
          });
    }

    void LinuxWindow::shutdown()
    {
        glfwDestroyWindow(window);
    }

    void LinuxWindow::onUpdate()
    {
        glfwPollEvents();
        context->swapBuffers();
    }

    void LinuxWindow::setVSync(bool enabled)
    {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }

        windowData.vSync = enabled;
    }

    bool LinuxWindow::isVSync() const
    {
        return windowData.vSync;
    }
}