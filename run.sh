#!/usr/bin/bash

! command -v premake5 &> /dev/null && { \
    echo "Premake is not installed"; \
    echo "Hello";
    exit; \
}

premake5 gmake2 && make && ./bin/Debug-linux-x86_64/Sandbox/Sandbox