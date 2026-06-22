#investigado para incluir Qt en proyecto
cmake_minimum_required(VERSION 3.16)
project(ChatMode)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(MPI REQUIRED)
find_program(MPIEXEC_EXECUTABLE mpiexec mpirun)           

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
    mainwindow.cpp  
    mainwindow.h   
    receptor_mpi.h                
)

target_include_directories(ChatMode PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ChatMode PRIVATE core
    Qt6::Widgets                      # MPI para C
    MPI::MPI_CXX                     # MPI para C++
)

qt_add_resources(ChatMode "assets"
    PREFIX "/"
    FILES
        utils/user.png
        utils/background.png
        utils/contacts.png
        utils/difusion.png
        utils/send.png
        utils/back.png
        utils/minis/mini_back.png
        utils/minis/mini_contacts.png
        utils/minis/mini_difusion.png
        utils/minis/mini_send.png
        utils/bubble_send.png
        utils/bubble_send2.png
        utils/bubble_recv.png
        utils/bubble_recv2.png
)

add_custom_target(run
    COMMAND ${MPIEXEC_EXECUTABLE} --oversubscribe -n 5 ./ChatMode
    DEPENDS ChatMode
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
