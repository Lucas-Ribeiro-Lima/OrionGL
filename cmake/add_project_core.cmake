# Search for the source code
file(GLOB_RECURSE CPP_SOURCES_CORE "${PROJECT_SOURCE_DIR}/src/core/*.cpp")
file(GLOB_RECURSE CPP_SOURCES_GRAPHICS "${PROJECT_SOURCE_DIR}/src/graphics/*.cpp")
file(GLOB_RECURSE CPP_SOURCES_UTILS "${PROJECT_SOURCE_DIR}/src/utils/*.cpp")

set(PROJECT_CORE_LIB "${PROJECT_NAME}-core")
add_library(${PROJECT_CORE_LIB} STATIC
        ${CPP_SOURCES_CORE}
        ${CPP_SOURCES_GRAPHICS}
        ${CPP_SOURCES_UTILS}
        "src/graphics/glad.c")

target_include_directories(${PROJECT_CORE_LIB} PUBLIC "${PROJECT_SOURCE_DIR}/include")

#Third parties
target_link_libraries(${PROJECT_CORE_LIB} PUBLIC glm)
target_link_libraries(${PROJECT_CORE_LIB} PUBLIC glfw)
