#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "stJugador.h"
#include "stPartida.h"
#include "stPartidaXJugador.h"


char nom_jugadores[50] = "jugadores.dat";
char nom_partidas[50] = "partidas.dat";
char nom_pxj[50] = "partidaXjugador.dat";


void cargar_tablero(char tab[3][3]);
void mostrar_tab(char tab[3][3]);
void jugar_x(char tab[3][3]);
void jugar_o_pc(char tab[3][3]);
int verificar(char tab[3][3], char dato);
int empate(char tab[3][3]);
void jugar_o(char tab[3][3]);
void actualizar_puntos(stJugador jugadores[], int v, int id_jugador, int puntos);


int main()
{
    stJugador jugadores[100];
    int v_jugadores = 0;
    int dim_jugadores = 100;
    stJugador jugador1 = {0}, jugador2 = {0};

    stPartida partida;
    stPartidaXJugador pj1, pj2;

    int ultimo_id_partida = 0;
    int ultimo_id_pxj = 0;

    char tablero[3][3];
    char op_menu;
    int opcion;


    srand(time(NULL));
    v_jugadores = cargar_arreglo_users(jugadores, v_jugadores, dim_jugadores, nom_jugadores);
    ultimo_id_partida = obtener_ultimo_id_partida(nom_partidas);
    ultimo_id_pxj = obtener_ultimo_id_pxj(nom_pxj);

    // --- MENU PRINCIPAL ---
    do {
        printf("===============================\n");
        printf("      BIENVENIDO AL TA-TE-TI\n");
        printf("===============================\n");
        printf(" Jugadores registrados: %d\n", v_jugadores);
        printf("-------------------------------\n");
        printf("1 - Jugar contra la maquina\n");
        printf("2 - Jugar 1 vs 1\n");
        printf("3 - Crear cuenta de jugador\n");
        printf("4 - Salir\n");
        printf("-------------------------------\n");
        printf("Elija una opcion: ");
        scanf(" %d", &opcion);
        system("cls");

        switch(opcion) {
        case 1: // JUGAR VS CPU
            if(jugador1.idJugador == 0) { /// Si no hay nadie logueado
                printf("Debe iniciar sesion el Jugador 1\n");
                jugador1 = iniciar_sesion(jugadores, v_jugadores, dim_jugadores);
            }

            /// Crea y guarda la partida
            partida.idPartida = ++ultimo_id_partida;
            partida.dificultad = 1; // Nivel facil
            partida.esContraCpu = 1;
            guardar_partida(partida, nom_partidas);

            cargar_tablero(tablero);
            mostrar_tab(tablero);

            while (1) {
                jugar_x(tablero); // Turno del jugador
                system("cls");
                mostrar_tab(tablero);

                if (verificar(tablero, 'X')) {
                    printf("FELICIDADES GANASTE BRO\n");
                    pj1 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador1.idJugador, 1); // 1 = gana
                    guardar_registro_pxj(pj1, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador1.idJugador, pj1.puntosJugador);
                    break;
                }
                if (empate(tablero)) {
                    printf("EMPATE NT \n");
                    pj1 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador1.idJugador, 2); // 2 = empate
                    guardar_registro_pxj(pj1, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador1.idJugador, pj1.puntosJugador);
                    break;
                }

                printf("Turno de la computadora...\n");
                jugar_o_pc(tablero); // Turno de la PC
                system("cls");
                mostrar_tab(tablero);

                if (verificar(tablero, 'O')) {
                    printf("PERDISTE, PC GANA JAJAJ\n");
                    pj1 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador1.idJugador, 0); // 0 = pierde
                    guardar_registro_pxj(pj1, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador1.idJugador, pj1.puntosJugador);
                    break;
                }
                if (empate(tablero)) {
                    printf("empate nt\n");
                    pj1 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador1.idJugador, 2); // 2 = empate
                    guardar_registro_pxj(pj1, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador1.idJugador, pj1.puntosJugador);
                    break;
                }
            }
            break;

        case 2: // JUGAR 1 VS 1
            printf("Inicia sesion Jugador 1 (X):\n");
            jugador1 = iniciar_sesion(jugadores, v_jugadores, dim_jugadores);
            printf("\nInicia sesion Jugador 2 (O):\n");
            jugador2 = iniciar_sesion(jugadores, v_jugadores, dim_jugadores);


            partida.idPartida = ++ultimo_id_partida;
            partida.dificultad = 0;
            partida.esContraCpu = 0;
            guardar_partida(partida, nom_partidas);

            cargar_tablero(tablero);

            while (1) {
                system("cls");
                mostrar_tab(tablero);
                printf("\nTurno de %s (X)\n", jugador1.username);
                jugar_x(tablero);

                if (verificar(tablero, 'X')) {
                    system("cls");
                    mostrar_tab(tablero);
                    printf("\nGANA %s (X)!\n", jugador1.username);


                    /// Registro para Jugador 1 (gana)
                    pj1 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador1.idJugador, 1);
                    guardar_registro_pxj(pj1, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador1.idJugador, pj1.puntosJugador);


                    ///  Registro para Jugador 2 (pierde)
                    pj2 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador2.idJugador, 0);
                    guardar_registro_pxj(pj2, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador2.idJugador, pj2.puntosJugador);
                    break;
                }
                if (empate(tablero)) {
                    system("cls");
                    mostrar_tab(tablero);
                    printf("\nPARTIDA EMPATADA!\n");


                    /// Registro para Jugador 1 (empate)



                    pj1 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador1.idJugador, 2);
                    guardar_registro_pxj(pj1, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador1.idJugador, pj1.puntosJugador);


                    /// Registro para Jugador 2 (empate)



                    pj2 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador2.idJugador, 2);
                    guardar_registro_pxj(pj2, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador2.idJugador, pj2.puntosJugador);
                    break;
                }

                system("cls");
                mostrar_tab(tablero);
                printf("\nTurno de %s (O)\n", jugador2.username);
                jugar_o(tablero);

                if (verificar(tablero, 'O')) {
                    system("cls");
                    mostrar_tab(tablero);
                    printf("\nGANA %s (O)!\n", jugador2.username);



                    // Registro para Jugador 1 (pierde)
                    pj1 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador1.idJugador, 0);
                    guardar_registro_pxj(pj1, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador1.idJugador, pj1.puntosJugador);



                    // Registro para Jugador 2 (gana)
                    pj2 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador2.idJugador, 1);
                    guardar_registro_pxj(pj2, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador2.idJugador, pj2.puntosJugador);
                    break;
                }
                 if (empate(tablero)) { // Se vuelve a comprobar por si el ultimo movimiento fue empate
                    system("cls");
                    mostrar_tab(tablero);
                    printf("\nPARTIDA EMPATADA!\n");
                    pj1 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador1.idJugador, 2);
                    guardar_registro_pxj(pj1, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador1.idJugador, pj1.puntosJugador);
                    pj2 = crear_registro_pxj(++ultimo_id_pxj, partida.idPartida, jugador2.idJugador, 2);
                    guardar_registro_pxj(pj2, nom_pxj);
                    actualizar_puntos(jugadores, v_jugadores, jugador2.idJugador, pj2.puntosJugador);
                    break;
                }
            }
            break;

        case 3: // CREAR CUENTA
            if (v_jugadores < dim_jugadores)
            {

                int proximo_id = (v_jugadores > 0) ? jugadores[v_jugadores - 1].idJugador + 1 : 1;
                jugadores[v_jugadores] = crear_cuenta(proximo_id, jugadores, v_jugadores);
                v_jugadores++;


                guardar_arreglo_jugadores(jugadores, v_jugadores, nom_jugadores);
                printf("\nCuenta creada con exito! Ahora puede iniciar sesion \n");
            }
            else
            {
                printf("No se pueden agregar mas jugadores, acordate el user\n");
            }
            break;

        case 4:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opcion no valida.\n");
            break;
        }

        if (opcion != 4) {
             printf("\nPresione cualquier tecla para volver al menu principal...");
             getch();
             system("cls");
        }

    } while(opcion != 4);


    guardar_arreglo_jugadores(jugadores, v_jugadores, nom_jugadores);
    printf("Todos los datos han sido guardados\n");

    return 0;
}




void actualizar_puntos(stJugador jugadores[], int v, int id_jugador, int puntos) {
    for (int i = 0; i < v; i++) {
        if (jugadores[i].idJugador == id_jugador) {
            jugadores[i].ptsTotales += puntos;
            printf("Puntos de %s actualizados. Total: %d\n", jugadores[i].username, jugadores[i].ptsTotales);
            return;
        }
    }
}






void cargar_tablero(char tab[3][3])
{
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            tab[i][j] = ' ';
        }
    }
}

void mostrar_tab(char tab[3][3])
{
    printf("        C1  C2  C3\n");
    for(int i = 0; i < 3; i++)
    {
        printf("Fila %d ", i + 1);
        for(int j = 0; j < 3; j++)
        {
            printf(" %c ", tab[i][j]);
            if(j < 2) printf("|");
        }
        printf("\n");
        if(i < 2) printf("       ---|---|---\n");
    }
}

void jugar_x(char tab[3][3])
{
    int fila, colu;
    int valido = 0;

    while(valido == 0)
    {
        printf("Ingrese Fila (1-3): ");
        scanf(" %d", &fila);

        printf("Ingrese Columna (1-3): ");
        scanf(" %d", &colu);

        if(fila >= 1 && fila <= 3 && colu >= 1 && colu <= 3 && tab[fila-1][colu-1] == ' ')
        {
            tab[fila-1][colu-1] = 'X';
            valido =1;
        }
        else
        {
            printf("Posicion invalida o ya ocupada. Intente de nuevo.\n");
        }
    }
}

void jugar_o(char tab[3][3])
{
    int fila, colu;
    int valido = 0;

    while(valido == 0)
    {
        printf("Ingrese Fila (1-3): ");
        scanf(" %d", &fila);

        printf("Ingrese Columna (1-3): ");
        scanf(" %d", &colu);

        if(fila >= 1 && fila <= 3 && colu >= 1 && colu <= 3 && tab[fila-1][colu-1] == ' ')
        {
            tab[fila-1][colu-1] = 'O';
            valido =1;
        }
        else
        {
            printf("Posicion invalida o ya ocupada. Intenta de nuevo\n");
        }
    }
}

void jugar_o_pc(char tab[3][3])
{
    int fila, colu;
    int flag = 0;
    while(flag == 0)
    {
        fila = rand() % 3;
        colu = rand() % 3;

        if(tab[fila][colu] == ' ')
        {
            tab[fila][colu] = 'O';
            flag = 1;
        }
    }
}

int verificar(char tab[3][3], char dato)
{
    int flag = 0;
    for(int i = 0; i<3; i++)
    {
        if(tab[i][0] == dato && tab[i][1] == dato && tab[i][2] == dato) flag = 1;
        if(tab[0][i] == dato && tab[1][i] == dato && tab[2][i] == dato) flag = 1;
    }
    if(tab[0][0] == dato && tab[1][1] == dato && tab[2][2] == dato) flag = 1;
    if(tab[0][2] == dato && tab[1][1] == dato && tab[2][0] == dato) flag = 1;
    return flag;
}

int empate(char tab[3][3])
{
    int flag = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tab[i][j] == ' ') {
                flag = 0;
                break;
            }
        }
        if (flag == 0) break;
    }
    return flag;
}
