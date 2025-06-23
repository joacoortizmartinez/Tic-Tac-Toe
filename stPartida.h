#ifndef STPARTIDA_H_INCLUDED
#define STPARTIDA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int idPartida;
    int dificultad;
    int esContraCpu; // 1 si es contra CPU, 0 si es 1v1
}stPartida;

// Prototipos de funciones
int obtener_ultimo_id_partida(char nombre_archivo[]);
void guardar_partida(stPartida partida, char nombre_archivo[]);


#endif // STPARTIDA_H_INCLUDED
