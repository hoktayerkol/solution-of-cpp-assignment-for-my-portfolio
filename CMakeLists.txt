cmake_minimum_required(VERSION 2.8)
project(policy-assignment)

configure_file("show.py" "show.py" COPYONLY)
configure_file("grid_world.py" "grid_world.py" COPYONLY)

add_executable(${PROJECT_NAME} "main.cpp")
