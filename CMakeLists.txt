cmake_minimum_required(VERSION 3.31)
project(progrmmingExam)

set(CMAKE_CXX_STANDARD 20)

add_executable(progrmmingExam main.cpp
        Task.cpp
        Task.h
        ToDoList.cpp
        ToDoList.h)

# Add unit tests
enable_testing()
add_subdirectory(unit_testing)
