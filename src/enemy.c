#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enemy.h"

Enemigo *Crear_Enemigo(int id, const char *name, int hp, int danho)
{
    /* Comprobacion previa*/
    if (hp <= 0 || danho < 0 || name == NULL) return NULL;

    /* Se reserva memoria */
    Enemigo *E = malloc(sizeof(Enemigo));
    if (E == NULL)
    {
        printf("Error: No hay memoria disponible para crear el enemigo\n");
        return NULL;
    }

    /* Se asignan los valores de la funcion a los punteros */
    E->id = id;
    E->vida = hp;
    E->max_vida = hp;
    E->danho = danho;

    /* Se asigna el nombre del enemigo (+1: caracter nulo \0) */
    E->name = malloc(strlen(name) + 1);
    if (E->name == NULL)
    {
        printf("Error: Sin memoria disponible para nombre del enemigo\n");
        free(E);
        return NULL;
    }
    strcpy(E->name, name); /* Se copia cadena */

    return E;
}

void Destruir_Enemigo(Enemigo *E)
{
    if (E == NULL) return;
    /* La funcion free ignora los punteros NULL por defecto*/
    free(E->name);
    free(E);
}

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

void Mostrar_Enemigo(const Enemigo *E)
{
    if (E == NULL) return;
    printf("\n=== Un [%s] aparecio! ===\n", E->name);
    printf("Vida: %d / %d PV\n" E->vida, E->max_vida);
    printf("Ataque: %d\n", E->danho);
    printf("============================\n");
}