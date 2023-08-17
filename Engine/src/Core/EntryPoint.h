#ifndef __ENTRY_POINT_H__
#define __ENTRY_POINT_H__

#include "Core/Application.h"
#include "Core/Log.h"

extern Kaydee::Application* Kaydee::createApplication(); 

int main(int arcg, char **argv)
{
    Kaydee::Log::init();
    KD_CORE_WARN("Initialized log");

    auto app = Kaydee::createApplication();
    app->run();
    delete app;
}

#endif
