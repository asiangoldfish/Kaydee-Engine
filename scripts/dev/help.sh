#!/usr/bin/bash

# Exit if this script is run standalone
if [  "$( basename "$0" )" == "help.sh" ]; then
    echo "ERROR: You cannot run this script standalone"
    exit -1
fi

display_help() {
    echo "Usage: ./create_module.sh [options]"
    echo "Options:"
    echo "  -b, --build                  Build the project"
    echo "  -c, --clean                  Clean the build directory"
    echo "  -cb, --clean-build           Clean and build the project"
    echo "  --continuous-build           Automatically builds on change"
    echo "  -d, --doxygen                Generate or update Doxygen documentation"
    echo "  -do,--doxygen-open           Open Doxygen documentation in default browser"
    echo "  --docs-local-server          Run local server developing the documentation website"
    echo "  -h, --help                   Display this help page"
    echo "  -n, --new-module             Create a new module"
    echo "  -r, --run                    Compile and run the program"
    echo ""
    echo "Examples:"
    echo "  ./create_module.sh -n             # Create a new module"
    echo "  ./create_module.sh -d             # Generate or update Doxygen documentation"
    echo "  ./create_module.sh --help -n      # Get help for the new-module command"
}

display_new_module_help() {
    echo "Usage: ./create_module.sh --new-module"
    echo "Options:"
    echo "  -h, --help          Display help for the new-module command"
    echo ""
    echo "Examples:"
    echo "  ./create_module.sh --new-module     # Create a new module"
}

display_doxygen_help() {
    echo "Usage: ./create_module.sh --doxygen"
    echo "Options:"
    echo "  -h, --help          Display help for the doxygen command"
    echo ""
    echo "Examples:"
    echo "  ./create_module.sh --doxygen        # Generate or update Doxygen documentation"
}
