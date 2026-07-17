cmake_minimum_required(VERSION 4.3)
project(chip8TE)


add_executable(${PROJECT_NAME} 
  src/main.cpp
  src/rendering_engine/tEngine.cpp
  src/chip8/program_loader/program_loader.cpp
)
