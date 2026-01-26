cmake_minimum_required(VERSION 3.23)

project(${PROJECT_NAME} LANGUAGES CXX)

set(PROJECT_NAME "Rusty")
set(HEADER_DIRECTORY "include/")

add_executable(${PROJECT_NAME})

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else ()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIRECTORY})
