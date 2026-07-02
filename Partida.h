#ifndef PARTIDA_H
#define PARTIDA_H

#include <iostream>
#include <string>
#include "Tablero.h"
#include "constantes.h"
#include "utilidades.h"

using namespace std;

class Partida {
private:
    Tablero tablero;
    int turno;
    string jugador1;
    string jugador2;

    // Historial de movimientos
    string historial[MAX_HISTORIAL];
    int numMovimientos;

    // Regla de los 50 movimientos
    int contador50;

    // Repeticion de posicion
    string posiciones[MAX_HISTORIAL];
    int numPosiciones;

    // Peon al paso
    bool huboDobleAvance;
    int ultimaPeonFila;
    int ultimaPeonCol;

    // Flags de enroque
    bool reyBlancoMovido;
    bool reyNegroMovido;
    bool torreBlancoA_Mov;
    bool torreBlancoH_Mov;
    bool torreNegroA_Mov;
    bool torreNegroH_Mov;

    // Inicializar piezas en el tablero
    void inicializarPiezas();

    // Reiniciar todos los flags y contadores
    void reiniciarEstado();

    // Obtener char del color del turno actual ('B' o 'N')
    char colorActual() const;

    // Verificar si un movimiento deja al rey propio en jaque
    bool dejaPropioReyEnJaque(int fo, int co, int fd, int cd) const;

    // Intentar enroque
    bool manejarEnroque(int fo, int co, int fd, int cd);

    // Intentar peon al paso
    bool manejarPeonAlPaso(int fo, int co, int fd, int cd);

    // Registrar movimiento en historial
    void registrarMovimiento(int fo, int co, int fd, int cd);

    // Mostrar historial debajo del tablero
    void mostrarHistorial() const;

    // Guardar estado actual del tablero como string de 64 chars
    string estadoTablero() const;

    // Verificar tablas por repeticion
    bool verificarRepeticion();

    // Verificar regla de los 50 movimientos
    bool verificar50Movimientos() const;

    // Verificar si el jugador actual tiene movimientos legales
    bool tieneMovimientosLegales();

    // Verificar jaque mate
    bool esJaqueMate();

    // Verificar ahogado
    bool esAhogado();

    // Procesar un turno completo
    void procesarTurno();

    // Mostrar tablero + historial
    void mostrarEstado() const;

public:
    Partida();
    ~Partida();

    // Iniciar partida nueva
    void iniciar();

    // Loop principal del juego
    void jugar();

    // Guardar partida en archivo
    void guardarPartida() const;

    // Cargar partida desde archivo
    bool cargarPartida();
};

#endif // PARTIDA_H