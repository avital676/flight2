cmake_minimum_required(VERSION 3.15)
project(flight2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(flight2 main.cpp parser.cpp lexer.cpp command.cpp command.h variables.cpp variables.h parser.h server.cpp server.h client.cpp client.h manager.cpp manager.h Interpreter.h Interpreter.cpp ex1.h ex1.cpp)