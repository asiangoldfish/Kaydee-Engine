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

constexpr uint32_t
hash(const char* data, size_t const size) noexcept
{
    uint32_t hash = 5381;

    for (const char* c = data; c < data + size; ++c)
        hash = ((hash << 5) + hash) + (unsigned char)*c;

    return hash;
}

int
main(int argc, char** argv)
{
    if (argc == 2) {
        std::string option(argv[1]);
        switch (hash(option.c_str(), sizeof(option))) {
            case hash("--help", 7):
            case hash("-h", 3):
                usage();
                break;

            case hash("--version", 10):
            case hash("-v", 3):
                version();
                break;

            default:
                std::cout << "Argument \'" << argv[1] << "\' not recognized.\n";
                usage();
        }
        return 0;
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
    std::cout << "1.0.0\n";
}

#endif
