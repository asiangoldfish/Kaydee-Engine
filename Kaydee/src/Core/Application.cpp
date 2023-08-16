#include "Core/Application.h"

#include "Core/Log.h"
#include "Events/ApplicationEvent.h"

void
Kaydee::Application::run()
{
    WindowResizeEvent e(1280, 720);

    // if (e.isInCategory(EventCategoryApplication))
    // {
    //     KD_TRACE(e);
    // }
    // if (e.isInCategory(EventCategoryInput))
    // {
    //     KD_TRACE(e);
    // }

    while (true)
        ;
}
