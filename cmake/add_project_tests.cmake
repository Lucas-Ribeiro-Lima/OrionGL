enable_testing()

## Search for the tests source code
file(GLOB_RECURSE TESTS_SOURCES "${PROJECT_SOURCE_DIR}/tests/test_*.cpp")

## Configure the test executable
set(PROJECT_TESTS_EXEC "${PROJECT_NAME}-tests")
add_executable(${PROJECT_TESTS_EXEC} ${TESTS_SOURCES})
target_link_libraries(${PROJECT_TESTS_EXEC} PRIVATE ${PROJECT_CORE_LIB} gtest_main)

add_test(NAME gtest COMMAND ${PROJECT_TESTS_EXEC})