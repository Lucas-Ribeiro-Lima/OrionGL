# Search for the source code
file(GLOB_RECURSE CPP_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
list(FILTER CPP_SOURCES EXCLUDE REGEX ".*/Main\.cpp")

set(PROJECT_CORE_LIB ${PROJECT_NAME}_core)
add_library(${PROJECT_CORE_LIB} STATIC ${CPP_SOURCES} "src/glad.c")
target_include_directories(${PROJECT_CORE_LIB} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_CORE_LIB} PUBLIC glm)
target_link_libraries(${PROJECT_CORE_LIB} PUBLIC glfw)
target_link_libraries(${PROJECT_CORE_LIB} PUBLIC nlohmann_json::nlohmann_json)
