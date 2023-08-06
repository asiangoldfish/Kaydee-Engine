#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#define KAYDEE_API

#include "Core.h"

namespace Kaydee
{
    class KAYDEE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
        static void print();
    };

    // To be defined in the client
    Application* createApplication();
}

#endif