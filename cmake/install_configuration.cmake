
set(INSTALL_NAME "oriongl")
set(INSTALL_DIR "oriongl")

##Installation
install(TARGETS ${PROJECT_MAIN_EXEC}
        EXPORT "${INSTALL_NAME}_targets"
        RUNTIME DESTINATION "${INSTALL_NAME}"
)

install(DIRECTORY "assets"
        DESTINATION "share/${INSTALL_DIR}"
)

install(DIRECTORY "shaders"
        DESTINATION "share/${INSTALL_DIR}"
)