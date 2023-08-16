#!/usr/bin/bash

# Exit if this script is run standalone
if [  "$( basename "$0" )" == "module.sh" ]; then
    echo "ERROR: You cannot run this script standalone"
    exit -1
fi


create_module() {
    printf "Enter the name of the new module: "
    read module_name

    # Trim leading and trailing whitespaces from the module name
    module_name=$(echo "$module_name" | xargs)

    if [ -z "$module_name" ]; then
        echo "Error: Module name cannot be blank."
        exit 1
    fi

    # Create the module directory
    module_dir="src/${module_name}"
    mkdir -p "$module_dir"

    # Generate the CMakeLists.txt file
    cat "scripts/CMakeLists.module" > "${module_dir}/CMakeLists.txt"

    # Add the new module to the root CMakeLists.txt
    echo "add_subdirectory(${module_name})" >> CMakeLists.txt

    echo "Module '${module_name}' has been created in '${module_dir}' and added to the root CMakeLists.txt."
    echo "Edit the CMakeLists.txt to ensure that it's correctly configured"
}
