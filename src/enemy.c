#include <stdio.h>
#include "enemy.h"

Enemigo *Crear_Enemigo(int id, char *name, int hp, int danho)
{
    /* Se reserva memoria */
    Enemigo *E = malloc(sizeof(Enemigo));
    if (E == NULL)
    {
        printf("Error: No hay memoria disponible para crear el enemigo\n");
        return NULL;
    }
    /* Se asignan los valores de la funcion a los punteros */
    E->id = id;
    E->name = name;
    E->vida = hp;
    E->max_vida = hp;
    E->danho = danho;    
    return E;
}

bool Esta_Muerto(Enemigo *E);

void Enemigo_RecibeDanho(Enemigo *E, int danho);

void Destruir_Enemigo(Enemigo *E);