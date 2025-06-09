#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "stPromiedos.h"
#include "stJugador.h"

char nom[50] = "jugadores.dat";
void cargar_tablero(char tab[3][3]);
void mostrar_tab(char tab[3][3]);
void jugar_x(char tab[3][3]);
void jugar_o_pc(char tab[3][3]);
int verificar(char tab[3][3], char dato);
int empate(char tab[3][3]);
void jugar_o(char tab[3][3]);
Promiedos cargar(char nombreArchivo[50]);
void guardar(Promiedos p, char nombreArchivo[50]);

int main()
{


    stJugador jugadores[100];
    int v_jugadores = 0;
    int dim_jugadores = 100;

    v_jugadores = cargar_arreglo_users(jugadores, v_jugadores, dim_jugadores, nom);
    //jugadores[v_jugadores] = crear_cuenta(v_jugadores, jugadores, dim_jugadores);
    // v_jugadores++;
    //guardar_arreglo_jugadores(jugadores, v_jugadores, nom);


    stJugador jugador1;
    printf("Inicia sesion jugador 1 \n");
    jugador1 =  iniciar_sesion(jugadores, v_jugadores, dim_jugadores);

    /** jugador2 =  INICIA SESION 2*/
    char tablero[3][3];
    int flag = 0;
    char op = 's';
    char nom[50] = "promiedos.dat";
    Promiedos promiedos = cargar(nom);



    int opcion = 0;
    do{
        printf("Bienvenido al ta-te-ti\n");
        printf("Jugar contra la maquina o 1v1? 1/2 \n");
        scanf(" %d", &opcion);




        switch(opcion)
        {
        case 1:
            {
                cargar_tablero(tablero);
                mostrar_tab(tablero);
                promiedos.partidos_pc++;
                while(flag == 0)
            {
            /** TURNO x */
            jugar_x(tablero);
            system("cls");
            mostrar_tab(tablero);

            if(verificar(tablero, 'X'))
            {
                printf("Ganaste! Te felicito \n");

                promiedos.p_jugador_x_vspc++;
                break;
            }

            if(empate(tablero))
            {
                printf("Empate! nt \n");
                promiedos.p_empate_vspc++;
                break;
            }

            /** TURNO DE o (pc)*/
            jugar_o_pc(tablero);
            system("cls");
            mostrar_tab(tablero);

            if(verificar(tablero, 'O'))
            {
                printf("PErdiste! burro (O)\n");
                promiedos.p_computadora++;
                break;
            }

            if(empate(tablero))
            {
                printf("Empate! nt\n");
                promiedos.p_empate_vspc++;
                break;
            }
        }
                break;
            }
        case 2:
            {
                promiedos.partidos_o++;
                stJugador jugador2;
        printf("Inicia sesion jugador 2\n");
        jugador2 =  iniciar_sesion(jugadores, v_jugadores, dim_jugadores);
        cargar_tablero(tablero);
        mostrar_tab(tablero);
            while(flag == 0)
            {
            /** TURNO x */
            jugar_x(tablero);
            system("cls");
            mostrar_tab(tablero);

            if(verificar(tablero, 'X'))
            {
                printf("Ganaste! Te felicito \n");
                promiedos.p_jugador_x_vso++;
                break;
            }

            if(empate(tablero))
            {
                printf("Empate! nt \n");
                promiedos.p_empate_vso++;
                break;
            }

            /** TURNO DE o */
            jugar_o(tablero);
            system("cls");
            mostrar_tab(tablero);

            if(verificar(tablero, 'O'))
            {
                printf("Ganaste O!\n");
                promiedos.p_jugador_o++;
                break;
            }

            if(empate(tablero))
            {
                printf("Empate! nt\n");
                promiedos.p_empate_vso++;
                break;
            }
        }

        break;
            }
        }

        printf("Queres volver a jugar? s/n \n");
        scanf(" %c", &op);

        system("cls");
        }while(op=='s');
        guardar(promiedos, nom);

        prom(promiedos);

    return 0;
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
    printf("Jugas vos! X \n");
    while(valido == 0)
    {
        printf("Ingrese numero de fila \n");
        scanf(" %d", &fila);

        printf("Ingrese numero de columna \n");
        scanf(" %d", &colu);

        if(tab[fila-1][colu-1] == ' ')
        {
            tab[fila-1][colu-1] = 'X';
            valido =1;
        }
        else
        {
            printf("Posicion invalida\n");
        }

    }

}


void jugar_o(char tab[3][3])
{
    int fila, colu;
    int valido = 0;
    printf("Jugas vos! O \n");
    while(valido == 0)
    {
        printf("Ingrese numero de fila \n");
        scanf(" %d", &fila);

        printf("Ingrese numero de columna \n");
        scanf(" %d", &colu);

        if(tab[fila-1][colu-1] == ' ')
        {
            tab[fila-1][colu-1] = 'O';
            valido =1;
        }
        else
        {
            printf("Posicion invalida\n");
        }

    }

}

void jugar_o_pc(char tab[3][3])
{
    int fila, colu;
    int flag = 0;
    srand(time(NULL));
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
        /* HORIZONTAL*/
        if(tab[i][0] == dato && tab[i][1] == dato && tab[i][2] == dato)
        {
            flag = 1;
        }

        /* VERTICAL*/
        if(tab[0][i] == dato && tab[1][i] == dato && tab[2][i] == dato)
        {
            flag = 1;
        }
    }


    /* DIAGONAL*/
    if(tab[0][0] == dato && tab[1][1] == dato && tab[2][2] == dato)
    {
        flag = 1;
    }

    if(tab[0][2] == dato && tab[1][1] == dato && tab[2][0] == dato)
    {
        flag = 1;
    }

    return flag;
}


int empate(char tab[3][3])
{
    int flag = 1;

    if (verificar(tab, 'X') || verificar(tab, 'O'))
    {
        flag = 0;
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (tab[i][j] == ' ')
                {
                    flag = 0;
                }
            }
        }
    }

    return flag;
}


void guardar(Promiedos p, char nombreArchivo[50]) {
    FILE *archi = fopen(nombreArchivo, "wb");
    if (archi == NULL) {
        printf("Error\n");
    }
    fwrite(&p, sizeof(Promiedos), 1, archi);
    fclose(archi);
}

Promiedos cargar(char nombreArchivo[50]) {
    Promiedos p = {0};
    FILE *archi = fopen(nombreArchivo, "rb");
    if (archi != NULL) {
        fread(&p, sizeof(Promiedos), 1, archi);
    }
    fclose(archi);
    return p;
}

void guardar_jugador_al_final(stJugador nuevoJugador, const char* nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "ab");
    if (archivo) {
        fwrite(&nuevoJugador, sizeof(stJugador), 1, archivo);
        fclose(archivo);
    }
}
