cmake_minimum_required(VERSION 4.0.2)

project(sample-solar-system VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(add_project_sample)
include(install_sample_configuration)
include(package_configuration)
