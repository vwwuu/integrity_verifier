cmake_minimum_required(VERSION 3.23)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "Rusty")
set(HEADER_DIRECTORY "include/")

# GoogleTest inclusion
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME})

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else ()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

target_sources(${PROJECT_NAME} PRIVATE src/main.cc)
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIRECTORY})
