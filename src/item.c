#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

Item* Item_Crear(int id, const char* name, ItemType type, ItemRarity rarity, int value)
{
    if (name == NULL)
    {
        printf("Error: el item necesita un nombre\n");
        return NULL;
    }
    
    
    Item* nuevo = malloc(sizeof(Item));
    if (nuevo == NULL)
    {
        printf("Error: Memoria insuficiente para Crear Item\n");
        return NULL;
    }

    //asignacion de memoria para el nombre
    nuevo->name = malloc(strlen(name) + 1);
    if (nuevo->name == NULL)
    {
        printf("Error al asignar memoria para el nombre del nuevo item\n");
        free(nuevo); //libera memoria de nuevo item.
        return NULL;
    }
    strcpy(nuevo->name, name);

    nuevo->id = id;
    nuevo->type = type;     // ej: ITEM_ESPADA, ITEM_POCION
    nuevo->rarity = rarity; // ej: ITEM_COMUN, ITEM_LEGENDARIO
    nuevo->value = value;

    return nuevo;
}

void Item_Destruir(Item* item) 
{
    if (item != NULL) 
    {
        if (item->name != NULL) 
            free(item->name); // Liberar primero el string
        free(item); // Luego liberar el struct
    }
}

const char* Item_Tipo_A_Texto(ItemType type)
{
    switch (type)
    {
        case ITEM_ARMA:         return "Arma";
        case ITEM_ARMADURA:     return "Armadura";
        case ITEM_POCION:       return "Pocion";
        case ITEM_OTRO_TIPO:    return "Otro";
    }
    return "Desconocido";
}

const char* Item_Rareza_A_Texto(ItemRarity rarity)
{
    switch (rarity)
    {
        case RAREZA_LEGENDARIA: return "Legendaria";
        case RAREZA_EPICA:      return "Epica";
        case RAREZA_RARA:       return "Rara";
        case RAREZA_COMUN:      return "Comun";
    }
    return "desconocida";
}