#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaje.h"

Personaje* Crear_Personaje(const char *name, int hp, int attack, int defense)
{
    if (name == NULL || hp <= 0 || attack < 0 || defense < 0)
    {
        printf("Error: datos invalidos para crear el personaje\n");
        return NULL;
    }
    
    Personaje* P = malloc(sizeof(struct _personaje));
    if(P == NULL)
    {
        printf("Error al asignar memoria para el personaje!!\n");
        return NULL;
    }

    //Nombre
    P->name = malloc(strlen(name) + 1);
	if(P->name == NULL){
		printf("Error: no hay memoria disponible para el nombre del personaje\n");
        free(P);
		return NULL;
	}
	strcpy(P->name, name);

    //Vida
    P->max_vida = P->vida = hp;

    //Ataque
    P->danho_base = P->danho = attack;
    
    //Defensa
    P->defensa_base = P->defensa = defense;

    //Equipamiento
    P->tiene_arma = P->tiene_armadura = false;

    return P;
}

void Mostrar_Personaje(Personaje *P)
{
    if (P == NULL)
    {
        printf("Error: Jugador no existente\n");
        return;
    }

    printf("\n=== ESTADO DEL PERSONAJE ===\n");
    printf("Nombre : %s\n", P->name);
    printf("Vida   : %d / %d PV\n", P->vida, P->vida);
    printf("Ataque : %d\n", P->danho);
    if (P->tiene_arma) 
    {
        printf("Arma equipada: %s (+%d ataque)\n", P->arma_equipada.name, P->arma_equipada.value);
    } else {
        printf("Arma equipada: Ninguna\n");
    }

    if (P->tiene_armadura)
        printf("Armadura equipada: %s (+%d defensa)\n", P->armadura_equipada.name, P->armadura_equipada.value);
    else
        printf("Armadura equipada: Ninguna\n");

    printf("Defensa: %d\n", P->defensa);
    printf("============================\n");
    return;
}

void Destruir_Personaje(Personaje *P)
{
    if (P == NULL)
        return;
    free(P->name);
    free(P);
}

