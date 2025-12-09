 cmake_minimum_required(VERSION 4.0.2)

 project(oriongl VERSION 1.0)
 list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

 option(COMPILE_SAMPLES "Compile the samples projects" OFF)
 option(USE_TESTS "Compile the tests" ON)
 option(INSTALL_ORIONGL "Install the engine core" OFF)

 include(policies)
 include(add_dependencies)

 ## Configure the core library
 include(add_project_core)

 if (USE_TESTS)
     ## Configure the test executable
     include(add_project_tests)
 endif ()

 if (INSTALL_ORIONGL)
     ## Configure the engine installer
     include(install_engine)
 endif ()

 if (COMPILE_SAMPLES)
     include(add_project_sample)
     include(install_sample_configuration)
     include(package_configuration)
 endif ()
