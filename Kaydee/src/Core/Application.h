#ifndef __APPLICATION_H__
#define __APPLICATION_H__

namespace Kaydee
{
    class Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;

        void run();
    };

    // To be defined in the client
    Application* createApplication();
}

#endif
