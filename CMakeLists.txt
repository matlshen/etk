cmake_minimum_required(VERSION 3.5.0)

project(etk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_ETK_TESTS "Build unit tests" ON)
option(INTERNAL_ASSERTIONS "Enable internal assertions" ON)

Include(FetchContent)
FetchContent_Declare(
    etl
    GIT_REPOSITORY https://github.com/ETLCPP/etl
    GIT_TAG        20.39.4
)
FetchContent_MakeAvailable(etl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic -Werror")

# Collect all .cpp files in the ./src directory
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Create a library target with the collected source files
add_library(${PROJECT_NAME} ${SRC_FILES})
add_library(etk::etk ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include ../etl/include)

target_link_libraries(${PROJECT_NAME} PRIVATE etl::etl)

if (BUILD_ETK_TESTS)
    add_subdirectory(test)
endif()

if (INTERNAL_ASSERTIONS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC INTERNAL_ASSERTIONS)
endif()