#include "stPromiedos.h"

Promiedos inicializar()
{
    Promiedos p = {0};
    return p;
}

void prom(Promiedos p)
{
    printf("BIENVENIDO A PROMIEDOS \n");
    printf("\n\n");
    printf("Partidos de X vs PC \n");
    printf("Partidos: %d \n", p.partidos_pc);
    printf("Ganados X: %d \n", p.p_jugador_x_vspc);
    printf("Empates: %d \n", p.p_empate_vspc);
    printf("Ganados PC: %d \n", p.p_computadora);
    printf("\n\n");

    printf("Partidos de X vs O \n");
    printf("Partidos: %d \n", p.partidos_o);
    printf("Ganados X: %d \n", p.p_jugador_x_vso);
    printf("Empates: %d \n", p.p_empate_vso);
    printf("Ganados O: %d \n", p.p_jugador_o);
}
