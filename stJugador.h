#ifndef STJUGADOR_H_INCLUDED
#define STJUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int idJugador;
    char nombre[30];
    char apellido[30];
    char email[50];
    char username[30];
    char password[20];
    char dni[10];
    int ptsTotales;
    int eliminado; // 0 = activo, 1 = eliminado
} stJugador;


stJugador crear_cuenta(int v, stJugador jugadores[], int dim);
int cargar_arreglo_users(stJugador jugadores[], int v, int dim, char nombre_archivo[50]);
void guardar_arreglo_jugadores(stJugador jugadores[], int v, char nombre_archivo[50]);
stJugador iniciar_sesion(stJugador juga[], int v, int dim);
int buscar_email_password(char email[50], char pass[50], stJugador juga[], int v, int dim, int *posi);

#endif // STJUGADOR_H_INCLUDED
