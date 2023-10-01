#ifndef __ENTRY_POINT_H__
#define __ENTRY_POINT_H__

#include "Core/Application.h"
#include "Core/Log.h"

extern Kaydee::Application*
Kaydee::createApplication();

void
usage();
void
version();

int
main(int argc, char** argv)
{
    if (argc == 2) {
        std::string option(argv[1]);
        if (option == "--help" || option == "-h") {
            usage();
            return 0;
        } else if (option == "--version" || option == "-v") {
            version();
            return 0;
        } else {
            std::cout << "Argument \'" << argv[1] << "\' is not recognized.\n";
            usage();
            return 1;
        }
    }

    Kaydee::Log::init();
    KD_CORE_WARN("Initialized log");

    auto app = Kaydee::createApplication();
    app->run();
    delete app;
}

void
usage()
{
    std::cout << R"(Usage: Sandbox [OPTION]
Game engine.

To start the game engine, launch the application with no arguments.

OPTIONS:
    -h, --help              this page
    -v, --version           version number
)";
}

void
version()
{
    // std::cout << "1.0.0\n";

    if (__cplusplus == 202101L)
        std::cout << "C++23";
    else if (__cplusplus == 202002L)
        std::cout << "C++20";
    else if (__cplusplus == 201703L)
        std::cout << "C++17";
    else if (__cplusplus == 201402L)
        std::cout << "C++14";
    else if (__cplusplus == 201103L)
        std::cout << "C++11";
    else if (__cplusplus == 199711L)
        std::cout << "C++98";
    else
        std::cout << "pre-standard C++." << __cplusplus;
    std::cout << "\n";
}

#endif
