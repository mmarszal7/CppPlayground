cmake_minimum_required(VERSION 3.0)
project(test)

find_package(OpenCV REQUIRED)

add_executable(main main.cpp externalFunction/circle.cpp)
target_link_libraries(main ${OpenCV_LIBS})