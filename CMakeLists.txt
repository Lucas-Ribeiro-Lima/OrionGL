 cmake_minimum_required(VERSION 4.0.2)

 project(oriongl VERSION 1.0)
 list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

 include(policies)
 include(add_dependencies)

 ## Configure the core library
 include(add_project_core)

 ## Configure the main sample
 include(add_project_sample)

 ## Configure the test executable
 include(add_project_tests)

 ## Configure the engine installer
 include(install_engine)

 ## Configure the installation of the project
 include(install_sample_configuration)

 ## Configure the package
 include(package_configuration)