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
            return windowData.Width;
        }
        inline unsigned int getHeight() const override
        {
            return windowData.Height;
        }

        // Window attributes
        inline void setEventCallback(const EventCallbackFn& callback) override
        {
            windowData.EventCallback = callback;
        }
        void setVSync(bool enabled) override;
        bool isVSync() const override;

    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();

    private:
        GLFWwindow* window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData windowData;
    };
}

#endif