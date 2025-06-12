#ifndef STPARTIDAXJUGADOR_H_INCLUDED
#define STPARTIDAXJUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int idPartidaJugador;
    int idPartida;
    int idJugador;
    int resultado;       // 0 = pierde, 1 = gana, 2 = empate
    int puntosJugador;   // 3 = gana, 1 = empate y 0 = derrota
} stPartidaXJugador;


int obtener_ultimo_id_pxj(char nombre_archivo[]);
stPartidaXJugador crear_registro_pxj(int id_pxj, int id_partida, int id_jugador, int resultado);
void guardar_registro_pxj(stPartidaXJugador registro, char nombre_archivo[]);

#endif // STPARTIDAXJUGADOR_H_INCLUDED
