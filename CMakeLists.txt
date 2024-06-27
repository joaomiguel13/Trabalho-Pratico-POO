cmake_minimum_required(VERSION 3.21)
project(TPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TPP main.cpp
        Aparelhos.cpp
        Processador.cpp
        PropriedadesAmbiente.cpp
        Regra.cpp
        Sensores.cpp
        Zona.cpp
        Comandos.cpp
        Habitacao.cpp
        Consola/Terminal.cpp)

target_link_libraries(TPP C:/Users/joaom/pdcurses/pdcurses.a)