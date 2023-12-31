# Command arguments with CMake

# Exit if this script is run standalone
if [  "$( basename "$0" )" == "cmake.sh" ]; then
    echo "ERROR: You cannot run this script standalone"
    exit -1
fi

# Delete the build directory
function cmake_clean() {
    local BUILDDIR
    BUILDDIR="$DIRPATH/build"

    if [ -d "$BUILDDIR" ]; then
        rm -r "$BUILDDIR"
        echo "Removed build directory"
    else
        echo "No build directory to remove"
    fi

}

function cmake_build() {
    local BUILDDIR
    BUILDDIR="$DIRPATH/build"

    if [ ! -d "$BUILDDIR" ]; then
        mkdir -p "$BUILDDIR"
        echo "Created build directory at $BUILDDIR"
    fi

    cd "$BUILDDIR"
    # Change CMAKE_BUILD_TYPE to Release or Debug
    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G "Unix Makefiles" ..
    cmake --build . && echo "Successfully built the project"
}


function cmake_run() {
    local BUILDDIR
    BUILDDIR="$DIRPATH/build"

    local override
    override="$1"

    if [ "$override" == "--gl-version-override" ]; then
        export MESA_GL_VERSION_OVERRIDE=4.5
    fi

    cd "$BUILDDIR"
    make && { cd ..; "$OUT"; }
}

####
# Continously build the project
#
# While the project is under project, this program runs in the background and
# builds the project upon change
function cmake_continous_build() {
    # Ensure entr is installed
    command -v "entr" > /dev/null || { echo "Command 'entr' is required, but not installed"; return -1; }

    # List all file patterns to match against
    local patterns
    patterns=(      # List them here
        "*.cpp"
        "*.h"
        "CMakeLists.txt"
    )

    local query
    query=""
    for p in "${patterns[@]}"; do
        query="$query -iname $p"

        # Check if last element in array
        if [ "$p" != ${patterns[${#patterns[@]} - 1]} ]; then
            query="$query -o"
        fi
    done

    find ./src -type f -iname *.cpp -o -iname *.h -o -iname CMakeLists.txt | entr -p ./util.sh -b
}
