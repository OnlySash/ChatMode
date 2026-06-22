#investigado para incluir Qt en proyecto
cmake_minimum_required(VERSION 3.16)
project(ChatMode)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(MPI REQUIRED)           

add_library(core STATIC
    ../src/wrapped_mpi.c
    ../src/coordinator.c
    ../src/protocol.c
    ../src/message.c
)

target_include_directories(core PUBLIC ../include)
target_compile_options(core PRIVATE -std=c2x -Wall -Wextra -g -O2)

target_link_libraries(core PUBLIC MPI::MPI_C)

#parte del makefile
add_executable(cli ../cli/main.c)
target_link_libraries(cli PRIVATE core )

#Usados en UI
qt_add_executable(ChatMode
    main_ui.cpp
    mainwindow.cpp                      # tu código C aquí
)

target_link_libraries(ChatMode PRIVATE core
    Qt6::Widgets                      # MPI para C
    MPI::MPI_CXX                     # MPI para C++
)
