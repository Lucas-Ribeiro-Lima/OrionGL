set(SAMPLE_DIR "${PROJECT_SOURCE_DIR}/samples/solar-system")

if(APPLE)
    file(GLOB_RECURSE CPP_SOURCES_PLATFORM "${SAMPLE_DIR}/platform/mac/*.cpp")
elseif (WIN32)
    file(GLOB_RECURSE CPP_SOURCES_PLATFORM "${SAMPLE_DIR}/platform/windows/*.cpp")
elseif (LINUX)
    file(GLOB_RECURSE CPP_SOURCES_PLATFORM "${SAMPLE_DIR}/platform/linux/*.cpp")
endif ()

file(GLOB_RECURSE CPP_SOURCES_BOUNDARY "${SAMPLE_DIR}/thirdparty/json/*.cpp")

set(PROJECT_SAMPLE_EXEC "sample-solar-system")
add_executable(${PROJECT_SAMPLE_EXEC}
        ${CPP_SOURCES_PLATFORM}
        ${CPP_SOURCES_BOUNDARY}
        "${SAMPLE_DIR}/main.cpp"
        "${SAMPLE_DIR}/Corp.cpp"
        "${SAMPLE_DIR}/PlanetRenderer.cpp")

target_include_directories(${PROJECT_SAMPLE_EXEC}
        PRIVATE "${SAMPLE_DIR}/include"
)

target_link_libraries(${PROJECT_SAMPLE_EXEC} PRIVATE ${PROJECT_CORE_LIB})
target_link_libraries(${PROJECT_SAMPLE_EXEC} PUBLIC nlohmann_json::nlohmann_json)
