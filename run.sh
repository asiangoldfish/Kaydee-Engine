#!/usr/bin/bash

! command -v premake5 &> /dev/null && { \
    echo "Premake is not installed"; \
    echo "Hello";
    exit; \
}

clear

premake5 gmake2 && premake5 export-compile-commands # && make && ./bin/Debug-linux-x86_64/Sandbox/Sandbox
