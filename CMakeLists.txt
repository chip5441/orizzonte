# Copyright (c) 2017 Vittorio Romeo
# MIT License |  https://opensource.org/licenses/MIT
# http://vittorioromeo.info | vittorio.romeo@outlook.com

cmake_minimum_required(VERSION 3.6)

# Include `vrm_cmake`.
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake/"
    "${CMAKE_SOURCE_DIR}/../vrm_cmake/cmake/"
    "${CMAKE_SOURCE_DIR}/extlibs/vrm_cmake/cmake/")

# Basic project setup.
project(orizzonte CXX)
enable_testing()

include(vrm_cmake)
vrm_cmake_init_project_name_upper()
vrm_cmake_init_project_source_dir()
vrm_cmake_init_project_common_module_paths()

# vrm_cmake_find_extlib(vrm_pp)
# vrm_cmake_find_extlib(vrm_core)

# Alias the include directory.
set(ORIZZONTE_INC_DIR "${ORIZZONTE_SOURCE_DIR}/include/")
include_directories("${ORIZZONTE_INC_DIR}")

# Other compiler flags.
vrm_cmake_add_common_compiler_flags()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
vrm_cmake_add_common_compiler_flags_suggest_attribute()

# The `check` target runs all tests.
vrm_check_target()

# Setup subdirectories.
add_subdirectory(test)
# add_subdirectory(example)

# Create header-only install target (automatically glob)
vrm_cmake_header_only_install_glob("${ORIZZONTE_INC_DIR}" "include")
