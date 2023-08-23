#!/usr/bin/bash

# Exit if this script is run standalone
if [  "$( basename "$0" )" == "help.sh" ]; then
    echo "ERROR: You cannot run this script standalone"
    exit -1
fi

display_help() {
    echo -n "Usage: ./create_module.sh [options]
Options:
  -b, --build                   Build the project
  -c, --clean                   Clean the build directory
  -cb, --clean-build            Clean and build the project
  --continuous-build            Automatically builds on change
  -d, --doxygen                 Generate or update Doxygen documentation
  -do,--doxygen-open            Open Doxygen documentation in default browser
  --docs-local-server           Run local server developing the documentation website
  -h, --help                    Display this help page
  -n, --new-module              Create a new module
  -r, --run                     Compile and run the program
        --gl-override-version   Override OpenGL version to 4.5

Examples:
  ./util.sh -n
  ./util.sh -d
  ./util.sh --help -n
"
}

display_new_module_help() {
    echo "Usage: ./create_module.sh --new-module"
    echo "Options:"
    echo "  -h, --help          Display help for the new-module command"
    echo ""
    echo "Examples:"
    echo "  ./util.sh --new-module     # Create a new module"
}

display_doxygen_help() {
    echo "Usage: ./create_module.sh --doxygen"
    echo "Options:"
    echo "  -h, --help          Display help for the doxygen command"
    echo ""
    echo "Examples:"
    echo "  ./util.sh --doxygen        # Generate or update Doxygen documentation"
}
