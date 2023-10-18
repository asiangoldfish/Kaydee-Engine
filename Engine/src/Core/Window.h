#pragma once

#include "kdpch.h"

#include "Core/Core.h"
#include "Events/Event.h"

namespace Kaydee {
    struct WindowProps
    {
        std::string title;
        uint32_t width;
        uint32_t height;

        WindowProps(const std::string& title = "Game",
                    uint32_t width = 1280,
                    uint32_t height = 720)
          : title(title)
          , width(width)
          , height(height)
        {
        }
    };

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void onUpdate() = 0;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        // Window attributes
        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual void setVSync(bool enabled) = 0;
        virtual bool isVSync() const = 0;

        // Return GLFW window pointer (can be any other API)
        virtual void* getNativeWindow() const = 0;

        static Window* create(const WindowProps& props = WindowProps());
    };
}
