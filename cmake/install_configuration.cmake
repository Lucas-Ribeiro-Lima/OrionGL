
set(INSTALL_NAME "oriongl")
set(INSTALL_DIR "oriongl")


##Installation
install(TARGETS ${PROJECT_MAIN_EXEC}
        EXPORT "${INSTALL_NAME}_targets"
        RUNTIME DESTINATION "bin"
)

install(DIRECTORY "assets"
        DESTINATION "share/${INSTALL_DIR}"
)

install(DIRECTORY "shaders"
        DESTINATION "share/${INSTALL_DIR}"
)


set(BUILD_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install-root")
add_custom_target(build-install
        COMMAND "${CMAKE_COMMAND}" --install "${CMAKE_BINARY_DIR}" --prefix "${BUILD_INSTALL_PREFIX}"
        DEPENDS ${PROJECT_TESTS_EXEC} ${PROJECT_MAIN_EXEC}
        COMMENT "Installing development layout to ${BUILD_INSTALL_PREFIX}"
)

if (WIN32)
    set(INSTALL_EXECUTABLE "${BUILD_INSTALL_PREFIX}/bin/${INSTALL_NAME}.exe")
else ()
    set(INSTALL_EXECUTABLE "${BUILD_INSTALL_PREFIX}/bin/${INSTALL_NAME}")
endif ()

add_custom_target(run-installed
        COMMAND "${INSTALL_EXECUTABLE}"
        DEPENDS build-install
)