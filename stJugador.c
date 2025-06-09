#include "stJugador.h"

char nombre_archivo_jugadores[] = "jugadores.dat";

stJugador crear_cuenta(int v, stJugador jugadores[], int dim)
{
    stJugador creando;

    int flag = 0;
    int flag_mayus = 0;
    int flag_minus = 0;


    printf("\n ------ Crea tu cuenta ------ \n");

    creando.idJugador = v;
    printf(" Nombre: ");
    scanf(" %29s", creando.nombre);

    printf(" Apellido: ");
    scanf(" %29s", creando.apellido);

    printf(" DNI: ");
    scanf(" %9s", creando.dni);

    int username_ok = 0;
    while (!username_ok)
    {
        username_ok = 1;
        printf(" Username: ");
        scanf(" %29s", creando.username);

        for (int i = 0; i < v; i++) {
            if (strcmp(jugadores[i].username, creando.username) == 0) {
                printf("El username ya existe, por favor cambialo.\n");
                username_ok = 0;
                break;
            }
        }
    }

    flag = 0;
    while (flag == 0)
    {
        printf(" Email: ");
        scanf(" %49s", creando.email);

        if (strchr(creando.email, '@') != NULL && strstr(creando.email, ".com") != NULL) {
            flag = 1;
        } else {
            printf("Email invalido. Debe contener '@' y terminar en '.com'\n");
        }
    }

    while (flag_mayus == 0 || flag_minus == 0)
    {
        flag_mayus = 0;
        flag_minus = 0;
        printf(" Password: ");
        scanf(" %19s", creando.password);

        for (int i = 0; i < strlen(creando.password); i++) {
            if (isupper(creando.password[i])) {
                flag_mayus = 1;
            }
            if (islower(creando.password[i])) {
                flag_minus = 1;
            }
        }

        if (!flag_mayus || !flag_minus) {
            printf("Contraseña invalida perro. Tiene que tener una mayus y minuscula\n");
        }
    }

    creando.ptsTotales = 0;
    creando.eliminado = 0;

    return creando;
}

int cargar_arreglo_users(stJugador jugadores[], int v, int dim, char nombre_archivo[50])
{
    FILE *archi = fopen(nombre_archivo, "rb");
    int i = 0;
    if (archi)
    {
        while (i < dim && fread(&jugadores[i], sizeof(stJugador), 1, archi) == 1)
        {
            i++;
        }
        fclose(archi);
    }

    return i;
}

void guardar_arreglo_jugadores(stJugador jugadores[], int v, char nombre_archivo[50]) {
    FILE *archi = fopen(nombre_archivo, "wb");
    if (archi) {
        fwrite(jugadores, sizeof(stJugador), v, archi);
        fclose(archi);
    } else {
        printf("Error: no se pudo abrir el archivo '%s' para escritura.\n", nombre_archivo);
    }
}
