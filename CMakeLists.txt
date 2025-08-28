cmake_minimum_required(VERSION 3.31)
project(TicketManagementSystem)

set(CMAKE_CXX_STANDARD 23)

add_executable(TicketManagementSystem main.cpp
        time_table.cpp
        time_table.h
        menu.cpp
        menu.h)
