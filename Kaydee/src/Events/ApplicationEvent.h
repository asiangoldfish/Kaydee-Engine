#ifndef __KAYDEE_APPLICATION_EVENT_H__
#define __KAYDEE_APPLICATION_EVENT_H__

#include "Event.h"

#include <sstream>

namespace Kaydee
{
    class WindowResizeEvent : public Kaydee::Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : width(width), height(height) {}

        inline unsigned int getWidth() const { return width; }
        inline unsigned int getHeight() const { return height; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << width << ", " << height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize);
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    
    private:
        int width, height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}

#endif
