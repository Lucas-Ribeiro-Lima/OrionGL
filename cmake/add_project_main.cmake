set(PROJECT_MAIN_EXEC ${PROJECT_NAME}_main)
add_executable(${PROJECT_MAIN_EXEC} "src/Main.cpp")
target_link_libraries(${PROJECT_MAIN_EXEC} PRIVATE ${PROJECT_CORE_LIB})
