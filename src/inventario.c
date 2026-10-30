#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
#include "history.h"
#include "print.h"
#include "history.h"
#include "stack.h"


Inventario* Inventario_Crear(void)
{
    Inventario* I = malloc(sizeof(Inventario));
    if(I == NULL)
    {
        printf("Error: Memoria insuficiente para crear el inventario\n");
        return NULL;
    }

    I->items = Lista_Crear();
    if(I->items == NULL)
    {
        free(I);
        return NULL;
    }

    return I;
} 

bool Inventario_Anhadir_Item(Inventario *Inv, Item item)
{
    if(Inv == NULL)
        return false;
    if(Inventario_Buscar_Id(Inv, item.id) != NULL)
    {
        printf("Error: ya existe un item con id %d\n", item.id);
        return false;
    }

    Lista_Insertar_Elemento(item, Inv->items, Inv->items); 
    return true;
}

void Inventario_Print_Items(const Inventario *Inv)
{
    Print_Titulo("MOCHILA");
    printf("\n");
    if (Inv == NULL || Lista_Esta_Vacia(Inv->items))
    {
        printf("\t" GRIS_NIEBLA "La mochila esta vacia." RESET "\n");
        return;
    }

    ListPosition P = Inv->items->Next; 
    while (P != NULL) 
    { 
        printf("\t" MORADO_TOXICO "[" VERDE_ZOMBIE "%d" MORADO_TOXICO "] " BLANCO_HUESO "%s" GRIS_NIEBLA " (%s | %s) - Efecto: " NARANJA_CALABAZA "%d" RESET "\n",
               P->Element.id, P->Element.name, Item_Tipo_A_Texto(P->Element.type), Item_Rareza_A_Texto(P->Element.rarity), P->Element.value);
        P = P->Next;
    }
}

Item* Inventario_Buscar_Nombre(const Inventario *Inv, const char *name)
{
    if (Inv == NULL || name == NULL)
        return NULL;
    ListPosition P = Inv->items->Next;   
    while (P != NULL) 
    {
        if (strcasecmp(P->Element.name, name) == 0)
        {
            return &(P->Element);
        }

        P = P->Next;
    }

    return NULL;
}

Item* Inventario_Buscar_Id(const Inventario *Inv, int item_id)
{
    if (Inv == NULL)
        return NULL;

    ListPosition P = Inv->items->Next;
    while(P!=NULL)
    {
        if(P->Element.id == item_id)
        {
            return &(P->Element);
        }
        P = P->Next;
    }

    return NULL;
}

bool Inventario_Usar(Inventario *Inv, int item_id, Personaje *P)
{
    if (Inv == NULL || P == NULL)
        return false;

    Item *it = Inventario_Buscar_Id(Inv, item_id);
    if (it == NULL)
    {
        printf("Error: no existe un item con id %d\n", item_id);
        return false;
    }
    
    Item copia = *it;
    switch (it->type)
    {
        case ITEM_POCION:
        {
            int antes = P->vida;
            P->vida += copia.value;
            if (P->vida > P->max_vida)
                P->vida = P->max_vida;
            printf("\t" VERDE_ZOMBIE "Usas %s: recuperas %d PV. " GRIS_NIEBLA "%s: %d/%d PV." RESET "\n",
                    copia.name, P->vida - antes, P->name, P->vida, P->max_vida);
            // Guardar nombre antes de borrar (copia superficial -> puntero name se libera en Lista_Remover_Elemento)
            char *nombre_item = copia.name;
            Lista_Remover_Elemento(item_id, Inv->items);
            printf("\t" GRIS_NIEBLA "%s se elimina del inventario." RESET "\n", nombre_item);
            return true;
        }
        case ITEM_ARMA:
        {
            int nuevo_danho = P->danho_base + copia.value;
            P->arma_equipada = copia;
            P->tiene_arma = true;
            printf("\t" VERDE_ZOMBIE "Equipas %s. " NARANJA_CALABAZA "Ataque: %d -> %d." RESET "\n", copia.name, P->danho, nuevo_danho);
            P->danho = P->danho_base + copia.value;
            return true;
        }
        case ITEM_ARMADURA:
        {
            P->armadura_equipada = copia;
            P->tiene_armadura = true;
            printf("\t" VERDE_ZOMBIE "Equipas %s. " NARANJA_CALABAZA "Defensa: %d -> %d." RESET "\n", copia.name, P->defensa, P->defensa_base + copia.value);
            P->defensa = P->defensa_base + copia.value;
            return true;
        }
        case ITEM_OTRO_TIPO:
        {
            printf("\t" GRIS_NIEBLA "%s no se puede usar de esta forma." RESET "\n", copia.name);
            return false;
        }
    }
    return false;
}

bool Inventario_Quitar_Item(Inventario *Inv, int item_id, Historial *H)
  {
      if (Inv == NULL) return 0;

      Item *it = Inventario_Buscar_Id(Inv, item_id);
      if (it == NULL) return 0;

      if (H != NULL) {
          Historial_Registrar(H, ACC_DESCARTE, "Descartaste item", it, item_id, 0);
      }

      return Lista_Remover_Elemento(item_id, Inv->items);
  }

void Inventario_Destruir(Inventario *Inv)
{
    if (Inv == NULL)
        return;
    Lista_Destruir(Inv->items);
    free(Inv);
}

int Generar_Id_Libre(Inventario *Inv)
{
    int id = rand() % MAX_ID + MIN_ID;
    while (Inventario_Buscar_Id(Inv, id) != NULL)
        id = rand() % MAX_ID + MIN_ID;
    return id;
}