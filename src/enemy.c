#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enemy.h"

Enemigo *Crear_Enemigo(int id, const char *name, int hp, int danho)
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
    /* Falta asignar name por memoria dianmica para luego liberarlo */
    E->name = name;
    E->vida = hp;
    E->max_vida = hp;
    E->danho = danho;    
    return E;
}

void Destruir_Enemigo(Enemigo *E);

bool Esta_Muerto(Enemigo *E)
{
    if (E == NULL) return true;
    return (E->vida <= 0); 
}

void Enemigo_RecibeDanho(Enemigo *E, int danho)
{
    if (E == NULL || danho <= 0) return;
    E->vida -= danho;
    if (E->vida < 0) E->vida = 0; /* No existe la vida negativa*/
}