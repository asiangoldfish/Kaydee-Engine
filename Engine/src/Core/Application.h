#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Core/Window.h"

namespace Kaydee {
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();

    private:
        std::unique_ptr<Window> window;
        bool running = true;
    };

    // To be defined in the client
    Application* createApplication();
}

#endif
