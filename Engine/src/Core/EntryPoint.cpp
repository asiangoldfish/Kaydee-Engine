#include <iostream>

#include "EntryPoint.h"

void
usage()
{
    std::cout << "Usage: myapp [OPTIONS]\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help     Display this help message\n";
    std::cout << "  -v, --version  Display version information\n";
}

void
version()
{
    std::cout << "MyApp version 1.0.0\n";
}

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

    return 0;
}