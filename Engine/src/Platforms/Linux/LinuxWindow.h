#ifndef __LINUX__WINDOW_H__
#define __LINUX__WINDOW_H__

#include "Core/Window.h"
#include <GLFW/glfw3.h>

namespace Kaydee {
    class LinuxWindow : public Window
    {
    public:
        LinuxWindow(const WindowProps& props);
        virtual ~LinuxWindow();

        void onUpdate() override;
        inline unsigned int getWidth() const override
        {
            return windowData.width;
        }
        inline unsigned int getHeight() const override
        {
            return windowData.height;
        }

        // Window attributes
        inline void setEventCallback(const EventCallbackFn& callback) override
        {
            windowData.eventCallback = callback;
        }
        void setVSync(bool enabled) override;
        bool isVSync() const override;

        inline virtual void* getNativeWindow() const override { return window; }

    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();

    private:
        GLFWwindow* window;

        struct WindowData
        {
            std::string title;
            unsigned int width, height;
            bool vSync;

            EventCallbackFn eventCallback;
        };

        WindowData windowData;
    };
}

#endif