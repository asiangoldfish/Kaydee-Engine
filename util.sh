#!/bin/bash

DIRPATH="$( echo "$PWD" )"
SCRIPTS="$DIRPATH/tools/development_scripts"

# Imports
source "$SCRIPTS/help.sh"
source "$SCRIPTS/doxygen.sh"
source "$SCRIPTS/module.sh"
source "$SCRIPTS/cmake.sh"

#####################################
### The script's main entry point ###
#####################################

# Help page on no arguments
if [ "$#" -eq 0 ]; then
    display_help
    exit 0
fi

# Parse arguments
while [ "$1" != "" ]; do
    case $1 in
    
        # Help pages. The user may also get help page for sub commands by saying ex. --help --new-module
        -h | --help )
            case "$2" in
                --new-module | -n )
                    display_new_module_help
                    ;;
                --doxygen | -d )
                    display_doxygen_help
                    ;;
                * )
                    display_help
            esac
            exit 0
            ;;
        -n | --new-module )
            create_module       # scripts/module.sh
            exit 0
            ;;
        -d | --doxygen )
            generate_doxygen_docs   # scripts/doxygen.sh
            exit 0
            ;;
        -do | --doxygen-open )
            open_docs
            exit 0
            ;;
        --docs-local-server )
            cd "$DIRPATH/docs"
            bash devserver.sh
            exit 0
            ;;
        -c | --clean )
            cmake_clean
            exit 0
            ;;
        -cb | --clean-build )
            cmake_clean &&
            cmake_build
            exit 0
            ;;
        -cbr | --clean-build-run )
            cmake_clean &&
            cmake_build &&
            cmake_run
            exit 0
            ;;
        -b | --build )
            cmake_build &&
            exit 0
            ;;
        -r | --run )
            cmake_build &&
            cmake_run &&
            exit 0
            ;;
        --continuous-build )
            cmake_continous_build
            exit 0
            ;;
        * )
            echo "Error: Invalid option: $1"
            display_help
            exit -1
            ;;
    esac
    shift
done

