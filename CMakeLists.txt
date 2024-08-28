cmake_minimum_required(VERSION 3.28)
project(Radcraft)

add_subdirectory(vendor/Framer)

set(CMAKE_CXX_STANDARD 23)

add_executable("${CMAKE_PROJECT_NAME}")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC vendor/Framer/include)

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE Framer)