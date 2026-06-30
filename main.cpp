#include <iostream>
#include <string>
#include "Partida.h"
#include "constantes.h" // Incluido para que el main conozca las reglas globales

using namespace std;

int main() {
    cout << "=================================================" << endl;
    cout << "          BIENVENIDO AL JUEGO DE AJEDREZ         " << endl;
    cout << "=================================================" << endl;

    // 1. Instanciar la clase controladora que programaron
    Partida juego;

    // 2. Configurar la partida (pedir nombres de jugadores, inicializar las piezas, etc.)
    juego.configurarPartida();

    cout << "\n¡La partida ha comenzado! Buena suerte.\n" << endl;

    // 3. Bucle principal de juego usando las funciones reales de tu Partida.h
    while (!juego.esJaqueMate() && !juego.esAhogado() && !juego.verificar50Movimientos()) {

        // Mostrar el estado gráfico del tablero actual e historial en consola
        juego.mostrarEstado();

        // Avisar el turno correspondiente usando colorActual() de tu clase
        if (juego.colorActual() == 'B') {
            cout << "\n>>> TURNO DE LAS PIEZAS BLANCAS <<<" << endl;
        } else {
            cout << "\n>>> TURNO DE LAS PIEZAS NEGRAS <<<" << endl;
        }

        // procesarTurno() se encarga de: pedir las coordenadas al usuario, validar
        // los movimientos de tus piezas con polimorfismo, procesar capturas y cambiar el turno.
        juego.procesarTurno();
    }

    // --- PANTALLA DE FIN DE JUEGO ---
    cout << "\n=================================================" << endl;
    cout << "                FIN DE LA PARTIDA                " << endl;
    cout << "=================================================" << endl;

    // Imprimir el tablero en su posición final
    juego.mostrarEstado();

    // Evaluar cuál fue la condición de salida del bucle usando tus métodos
    if (juego.esJaqueMate()) {
        // Si hay jaque mate y el color actual es 'B', significa que las blancas acaban
        // de iniciar su turno en jaque sin salida, por ende ganaron las negras (y viceversa).
        if (juego.colorActual() == 'B') {
            cout << "\n¡JAQUE MATE! Las piezas NEGRAS han ganado el juego." << endl;
        } else {
            cout << "\n¡JAQUE MATE! Las piezas BLANCAS han ganado el juego." << endl;
        }
    } else if (juego.esAhogado()) {
        cout << "\n¡TABLAS POR REY AHOGADO! El juego termina en empate." << endl;
    } else if (juego.verificar50Movimientos()) {
        cout << "\n¡TABLAS POR LA REGLA DE LOS 50 MOVIMIENTOS! El juego termina en empate." << endl;
    }

    return 0;
}