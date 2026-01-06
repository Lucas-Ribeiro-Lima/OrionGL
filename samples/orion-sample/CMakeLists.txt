cmake_minimum_required(VERSION 4.0.2)

project(orion_sample VERSION 1.0)

add_executable(orion_sample_exec "${PROJECT_SOURCE_DIR}/main.cpp"
                                 "${PROJECT_SOURCE_DIR}/BoxesRenderer.cpp")

target_include_directories(orion_sample_exec
                           PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(orion_sample_exec PRIVATE ${PROJECT_CORE_LIB})

file(COPY "assets" DESTINATION "${PROJECT_BINARY_DIR}")
