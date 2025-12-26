
set(INSTALL_NAME "sample-solar-system")
set(INSTALL_DIR "sample-solar-system")

##Installation
install(TARGETS ${PROJECT_SAMPLE_EXEC}
        EXPORT "${INSTALL_NAME}_targets"
        RUNTIME DESTINATION "bin"
        COMPONENT sample
)

install(DIRECTORY "assets"
        DESTINATION "share/${INSTALL_DIR}"
        COMPONENT sample
)

install(DIRECTORY "shaders"
        DESTINATION "share/${INSTALL_DIR}"
        COMPONENT sample
)


set(BUILD_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install-root")
add_custom_target(oriongl-build-sample
        COMMAND "${CMAKE_COMMAND}" --install "${CMAKE_BINARY_DIR}" --prefix "${BUILD_INSTALL_PREFIX}" --component sample
        DEPENDS ${PROJECT_TESTS_EXEC} ${PROJECT_SAMPLE_EXEC}
        COMMENT "Installing development layout to ${BUILD_INSTALL_PREFIX}"
)

if (WIN32)
    set(INSTALL_EXECUTABLE "${BUILD_INSTALL_PREFIX}/bin/${INSTALL_NAME}.exe")
else ()
    set(INSTALL_EXECUTABLE "${BUILD_INSTALL_PREFIX}/bin/${INSTALL_NAME}")
endif ()

add_custom_target(oriongl-run-sample
        COMMAND "${INSTALL_EXECUTABLE}"
        DEPENDS oriongl-build-sample
)
