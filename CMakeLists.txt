cmake_minimum_required(VERSION 4.1.2)
project(Ajedrez)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ajedrez
        main.cpp
        constantes.h
        utilidades.h
        utilidades.cpp
        Pieza.h
        Pieza.cpp
        Tablero.cpp
        Tablero.h
        Torre.cpp
        Torre.h
        Alfil.cpp
        Alfil.h
        Dama.cpp
        Dama.h
        Caballo.cpp
        Caballo.h
        Rey.cpp
        Rey.h
        Peon.cpp
        Peon.h
        Partida.cpp
        Partida.h
)
