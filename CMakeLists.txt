cmake_minimum_required(VERSION 4.0.2)
project(Ajedrez)

set(CMAKE_CXX_STANDARD 20)

add_executable(AjedresNuevo
        main.cpp
        tablero.cpp
        piezas_basicas.cpp
        piezas_avanzadas.cpp
        utilidades.cpp
)