#Common variables
set(CPACK_PACKAGE_NAME "OrionGL")
set(CPACK_PACKAGE_VENDOR "lucaslive974")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Studies and application of C++/OpenGL/Cmake")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/assets/packaging/package-icon.svg")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_GENERATOR "DEB")

#Debian variables
set(CPACK_PACKAGE_CONTACT "lucasribeirolima974@gmail.com")
set(CPACK_DEBIAN_PACKAGE_RELEASE "1.0")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "")

include(CPack)

