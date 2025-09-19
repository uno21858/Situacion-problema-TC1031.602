cmake_minimum_required(VERSION 4.0)
project(Situacion_problema_TC1031_602)

set(CMAKE_CXX_STANDARD 14)

add_executable(Situacion_problema_TC1031_602
        src/main.cpp
        src/MenuInterface.h
        src/MenuInterface.cpp
        src/LogsManager.h
        src/LogsManager.cpp)


# el cmkae list hace que puedas ejecutar el codigo con el boton de play
# no es necesario usar g++ nombre de todso los archivos. pues asi es mas facil