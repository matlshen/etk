cmake_minimum_required(VERSION 3.5.0)

project(etk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_ETK_TESTS "Build unit tests" ON)
option(BUILD_ETK_EXAMPLES "Build examples" OFF)
option(INTERNAL_ASSERTIONS "Enable internal assertions" ON)

Include(FetchContent)
FetchContent_Declare(
    etl
    GIT_REPOSITORY https://github.com/ETLCPP/etl
    GIT_TAG        20.39.4
)
FetchContent_MakeAvailable(etl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic -Werror")

# Create a library target with the collected source files
add_library(${PROJECT_NAME} INTERFACE)
add_library(etk::etk ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} 
    INTERFACE
    include
    ${etl_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} INTERFACE etl::etl)

if (BUILD_ETK_TESTS)
    add_subdirectory(test)
endif()

if (BUILD_ETK_EXAMPLES)
    add_subdirectory(examples)
endif()

if (INTERNAL_ASSERTIONS)
    target_compile_definitions(${PROJECT_NAME} INTERFACE INTERNAL_ASSERTIONS)
endif()