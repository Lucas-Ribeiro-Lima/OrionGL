option(ORIONGL_DEV_MODE "Use development asset paths" OFF)

if (ORIONGL_DEV_MODE)
    add_compile_definitions(ORIONGL_DEV_MODE=1)
else()
    add_compile_definitions(ORIONGL_DEV_MODE=0)
endif()


# Forward the configuration file
configure_file(
        "${PROJECT_SOURCE_DIR}/config.h.in"
        "${PROJECT_SOURCE_DIR}/include/Config.h"
)
