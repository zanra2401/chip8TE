cmake_minimum_required(VERSION 3.10)
project(chip8TE)

# Kumpulkan semua file C++
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
