cmake_minimum_required(VERSION 3.5.0)
project(etk_unit_tests LANGUAGES CXX)

# Download Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_compile_options(${PROJECT_NAME} 
    PRIVATE 
    -Wall 
    -Wextra
    -Werror
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/../include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    etk::etk
    GTest::gtest_main
)