#include "stPartida.h"

int obtener_ultimo_id_partida(char nombre_archivo_partida[])
{
    FILE *archi = fopen(nombre_archivo_partida, "rb");
    stPartida aux;
    int ultimo_id = 0;

    if (archi != NULL)
    {

        fseek(archi, 0, SEEK_END);

        if (ftell(archi) > 0)
        {

            fseek(archi, -sizeof(stPartida), SEEK_END);
            fread(&aux, sizeof(stPartida), 1, archi);
            ultimo_id = aux.idPartida;
        }
        fclose(archi);
    }

    return ultimo_id;
}



void guardar_partida(stPartida partida, char nombre_archivo[])
{
    FILE *archi = fopen(nombre_archivo, "ab");
    if (archi != NULL)
    {
        fwrite(&partida, sizeof(stPartida), 1, archi);
        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo de partidas.\n");
    }
}
