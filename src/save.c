#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"
#include "print.h"

bool Partida_Guardar(const char *ruta, const Personaje *P, const Inventario *I)
{
    if (P == NULL || I == NULL) 
        return false;

    FILE *f = fopen(ruta, "w");
    if (!f)
    {
        printf(ROJO_SANGRE "\tError al crear el archivo de guardado."RESET "\n");
        return false;
    }

    /*Formato: Nombre Vida MaxVida Danho Defensa*/
    fprintf(f, "%s %d %d %d %d\n", P->name, P->vida, P->max_vida, P->danho, P->defensa);
    
    /* Cuenta items inventario */
    int total_items = 0;
    ListPosition p = I->items->Next;
    while (p != NULL)
    {
        total_items++;
        p = p->Next;
    }
    fprintf(f, "%d\n", total_items);

    /* Guarda item: ID Tipo Rareza Valor Nombre */
    p = I->items->Next;
    while (p != NULL)
    {
        fprintf(f, "%d %d %d %d %s\n", p->Element.id, (int)p->Element.type, 
                (int)p->Element.rarity, p->Element.value, p->Element.name);
        p = p->Next;
    }

    fclose(f);
    printf(VERDE_ZOMBIE "\n\tPartida guardada con exito en '%s'." RESET "\n", ruta);
    return true;
}

Personaje* Partida_Cargar(const char *ruta, Inventario *I)
{
    if (I == NULL) return NULL;

    FILE *f = fopen(ruta, "r");
    if (!f)
    {
        printf(GRIS_NIEBLA "\n\tNo hay ninguna partida guardada previamente." RESET "\n");
        return NULL;
    }

    /* 49 caracteres + '\0' */
    char nombre[50];
    int vida, max_vida, danho, defensa;
    if (fscanf(f, "%49s %d %d %d %d", nombre, &vida, &max_vida, &danho, &defensa) != 5)
    {
        fclose(f);
        return NULL;
    }

    Personaje *P = Crear_Personaje(nombre, max_vida, danho, defensa);
    if (P != NULL)
        P->vida = vida;

    /* Cargar items */
    int total_items = 0;
    if (fscanf(f, "%d", &total_items) == 1)
    {
        for (int i=0; i < total_items; i++)
        {
            int id, tipo, rareza, valor;
            char nombre_item[100];
            
            /* 99[^\n]: maximo 99 caract, no saltos de linea. | == 5 por los argumentos*/
            if (fscanf(f, "%d %d %d %d %99[^\n]", &id, &tipo, &rareza, &valor, nombre_item) == 5)
            {
                /* Limpia espacio inicial si capturo */
                char *nom = nombre_item;
                while (*nom == ' ') 
                {
                    nom++;
                }

                Item *nuevo = Item_Crear(id, nom, (ItemType)tipo, (ItemRarity)rareza, valor);
                if (nuevo != NULL)
                {
                    Inventario_Anhadir_Item(I, *nuevo);
                    free(nuevo);
                }
            }
        }
    }

    fclose(f);
    printf(VERDE_ZOMBIE "\n\tPartida de %s cargada correctamente." RESET "\n", nombre);
    return P;
}