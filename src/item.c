#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

Item* Item_Generar(ItemRarity rareza, int id)
{
    int tipo = rand() % 3; // 0 = pocion, 1 = arma, 2 = armadura

    switch (rareza)
    {
        case RAREZA_COMUN:
            if (tipo == 0) return Item_Crear(id, "Venda Sucia", ITEM_POCION, rareza, 15);
            if (tipo == 1) return Item_Crear(id, "Tubo de Metal", ITEM_ARMA, rareza, 3);
            return Item_Crear(id, "Chaqueta de Cuero", ITEM_ARMADURA, rareza, 1);

        case RAREZA_RARA:
            if (tipo == 0) return Item_Crear(id, "Botiquin Medico", ITEM_POCION, rareza, 35);
            if (tipo == 1) return Item_Crear(id, "Hacha de Bombero", ITEM_ARMA, rareza, 7);
            return Item_Crear(id, "Chaleco Antibalas Viejo", ITEM_ARMADURA, rareza, 3);

        case RAREZA_EPICA:
            if (tipo == 0) return Item_Crear(id, "Jeringa de Adrenalina", ITEM_POCION, rareza, 60);
            if (tipo == 1) return Item_Crear(id, "Machete Reforzado", ITEM_ARMA, rareza, 12);
            return Item_Crear(id, "Traje de Contencion", ITEM_ARMADURA, rareza, 6);

        case RAREZA_LEGENDARIA:
            if (tipo == 0) return Item_Crear(id, "Vacuna Experimental", ITEM_POCION, rareza, 100);
            if (tipo == 1) return Item_Crear(id, "Katana del Rector", ITEM_ARMA, rareza, 20);
            return Item_Crear(id, "Exoesqueleto Zero", ITEM_ARMADURA, rareza, 10);
    }
    return NULL;
}

ItemRarity Rareza_Aleatoria(void)
{
    int tirada = rand() % 100;
    if (tirada < 55) return RAREZA_COMUN;
    if (tirada < 80) return RAREZA_RARA;
    if (tirada < 95) return RAREZA_EPICA;
    return RAREZA_LEGENDARIA;
}