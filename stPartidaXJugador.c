#include "stPartidaXJugador.h"


int obtener_ultimo_id_pxj(char nombre_archivo[])
{
    FILE *archi = fopen(nombre_archivo, "rb");
    stPartidaXJugador aux;
    int ultimo_id = 0;

    if (archi != NULL)
    {
        fseek(archi, 0, SEEK_END);
        if (ftell(archi) > 0)
        {
            fseek(archi, -sizeof(stPartidaXJugador), SEEK_END);
            fread(&aux, sizeof(stPartidaXJugador), 1, archi);
            ultimo_id = aux.idPartidaJugador;
        }
        fclose(archi);
    }
    return ultimo_id;
}


stPartidaXJugador crear_registro_pxj(int id_pxj, int id_partida, int id_jugador, int resultado)
{
    stPartidaXJugador nuevo;
    nuevo.idPartidaJugador = id_pxj;
    nuevo.idPartida = id_partida;
    nuevo.idJugador = id_jugador;
    nuevo.resultado = resultado;


    if (resultado == 1) { /// Gana
        nuevo.puntosJugador = 3;
    } else if (resultado == 2) { /// Empata
        nuevo.puntosJugador = 1;
    } else { /// Pierde
        nuevo.puntosJugador = 0;
    }

    return nuevo;
}


void guardar_registro_pxj(stPartidaXJugador registro, char nombre_archivo[])
{
    FILE *archi = fopen(nombre_archivo, "ab");
    if (archi != NULL)
    {
        fwrite(&registro, sizeof(stPartidaXJugador), 1, archi);
        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo de partida por jugador.\n");
    }
}

