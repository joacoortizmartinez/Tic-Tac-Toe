#ifndef STPROMIEDOS_H_INCLUDED
#define STPROMIEDOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int p_computadora;
    int p_jugador_x_vspc;
    int p_empate_vspc;
    int partidos_pc;

    int p_jugador_x_vso;
    int p_jugador_o;
    int p_empate_vso;
    int partidos_o;
}Promiedos;

Promiedos inicializar();

#endif // STPROMIEDOS_H_INCLUDED
