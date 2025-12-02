cmake_minimum_required(VERSION 4.0.2)

project(OpenGl-Learning VERSION 1.0)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(policies)
include(add_dependencies)

include(environment_configuration)

## Configure the core library
include(add_project_core)

## Configure the main executable
include(add_project_main)

## Configure the test executable
include(add_project_tests)