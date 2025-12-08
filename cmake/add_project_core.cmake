# Search for the source code
file(GLOB_RECURSE CPP_SOURCES_CORE "${PROJECT_SOURCE_DIR}/src/core/*.cpp")
file(GLOB_RECURSE CPP_SOURCES_GRAPHICS "${PROJECT_SOURCE_DIR}/src/graphics/*.cpp")

if(APPLE)
    file(GLOB_RECURSE CPP_SOURCES_PLATFORM "${PROJECT_SOURCE_DIR}/src/platform/mac/*.cpp")
elseif (WIN32)
    file(GLOB_RECURSE CPP_SOURCES_PLATFORM "${PROJECT_SOURCE_DIR}/src/platform/windows/*.cpp")
elseif (LINUX)
    file(GLOB_RECURSE CPP_SOURCES_PLATFORM "${PROJECT_SOURCE_DIR}/src/platform/linux/*.cpp")
endif ()

file(GLOB_RECURSE CPP_SOURCES_UTILS "${PROJECT_SOURCE_DIR}/src/utils/*.cpp")

file(GLOB_RECURSE CPP_SOURCES_BOUNDARY "${PROJECT_SOURCE_DIR}/src/thirdparty/json/*.cpp")

set(PROJECT_CORE_LIB "${PROJECT_NAME}_core")
add_library(${PROJECT_CORE_LIB} STATIC
        ${CPP_SOURCES_CORE}
        ${CPP_SOURCES_GRAPHICS}
        ${CPP_SOURCES_PLATFORM}
        ${CPP_SOURCES_BOUNDARY}
        ${CPP_SOURCES_UTILS}
        "src/graphics/glad.c")

target_include_directories(${PROJECT_CORE_LIB} PUBLIC "${PROJECT_SOURCE_DIR}/include")

#Third parties
target_link_libraries(${PROJECT_CORE_LIB} PUBLIC glm)
target_link_libraries(${PROJECT_CORE_LIB} PUBLIC glfw)
target_link_libraries(${PROJECT_CORE_LIB} PUBLIC nlohmann_json::nlohmann_json)
