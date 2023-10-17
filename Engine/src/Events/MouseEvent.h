#pragma once

#include "Event.h"

#include "kdpch.h"

namespace Kaydee {
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
          : mouseX(x)
          , mouseY(y)
        {
        }
        inline float getX() const { return mouseX; }
        inline float getY() const { return mouseY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float mouseX, mouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float offsetX, float offsetY)
          : offsetX(offsetX)
          , offsetY(offsetY)
        {
        }

        inline float getOffsetX() const { return offsetX; }
        inline float getOffsetY() const { return offsetY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << getOffsetX() << ", "
               << getOffsetY();
            return ss.str();
        }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        EVENT_CLASS_TYPE(MouseScrolled);

    private:
        float offsetX, offsetY;
    };

    class MouseButtonEvent : public Event
    {
    public:
        inline int getMouseButton() const { return button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        EVENT_CLASS_TYPE(MouseButtonPressed);

    protected:
        MouseButtonEvent(int button)
          : button(button)
        {
        }

        int button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
          : MouseButtonEvent(button)
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
          : MouseButtonEvent(button)
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}
