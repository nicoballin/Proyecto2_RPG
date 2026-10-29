#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaje.h"
#include "print.h"

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
        printf("\t" ROJO_SANGRE "Error: Jugador no existente" RESET "\n");
        return;
    }

    Print_Titulo("ESTADO DEL SOBREVIVIENTE");
    printf("\n");
    printf("\t" GRIS_NIEBLA "Nombre  : " VERDE_ZOMBIE "%s" RESET "\n", P->name);
    printf("\t" GRIS_NIEBLA "Vida    : " ROJO_SANGRE "%d / %d PV" RESET "\n", P->vida, P->max_vida);
    printf("\t" GRIS_NIEBLA "Ataque  : " NARANJA_CALABAZA "%d" RESET "\n", P->danho);
    printf("\t" GRIS_NIEBLA "Defensa : " BLANCO_HUESO "%d" RESET "\n", P->defensa);

    if (P->tiene_arma)
        printf("\t" GRIS_NIEBLA "Arma    : " BLANCO_HUESO "%s" NARANJA_CALABAZA " (+%d ataque)" RESET "\n", P->arma_equipada.name, P->arma_equipada.value);
    else
        printf("\t" GRIS_NIEBLA "Arma    : Ninguna" RESET "\n");

    if (P->tiene_armadura)
        printf("\t" GRIS_NIEBLA "Armadura: " BLANCO_HUESO "%s" NARANJA_CALABAZA " (+%d defensa)" RESET "\n", P->armadura_equipada.name, P->armadura_equipada.value);
    else
        printf("\t" GRIS_NIEBLA "Armadura: Ninguna" RESET "\n");
    return;
}

void Destruir_Personaje(Personaje *P)
{
    if (P == NULL)
        return;
    free(P->name);
    free(P);
}

