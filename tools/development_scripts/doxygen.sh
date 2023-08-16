#!/usr/bin/bash

# Exit if this script is run standalone
if [  "$( basename "$0" )" == "doxygen.sh" ]; then
    echo "ERROR: You cannot run this script standalone"
    exit -1
fi

generate_doxygen_docs() {
    # Check that doxygen is installed
    command -v doxygen &> /dev/null || { echo "Doxygen is not installed. Also install Graphviz" && exit -1; }

    if [ ! -d "doxygen-docs" ]; then mkdir "doxygen-docs"; fi
    doxygen Doxyfile

    echo "Doxygen documentation has been generated/updated."
}

open_docs() {
    if [ -z "$BROWSER" ]; then
        echo "Default browser was not found. Set environment variable BROWSER to browser's binary path"
        exit -1
    elif [ ! -f "doxygen-docs/html/index.html" ]; then
        echo "Unable to find Doxygen documentation. Generate it with the following command:"
        echo "./util.sh --doxygen"

        exit -1
    else
        "$BROWSER" "doxygen-docs/html/index.html"
    fi
}
