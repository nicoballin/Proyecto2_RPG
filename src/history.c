#include "history.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"

#define DESC_MAX 128

typedef struct { 
    StackElement base; 
    char descripcion[DESC_MAX]; 
    int enemigo_id; 
} AccionExt;

struct _historial {
    Stack acciones;
};

Historial *Historial_Crear(void)
{
    Historial *H = malloc(sizeof*H);
    if (H == NULL)
        return NULL;

    H->acciones = Pila_Crear();
    if (H->acciones == NULL) 
    {
        free(H);
        return NULL;
    }

    return H;
}


bool Historial_Guardar_Descarte(Historial *H, const Item *item, int posicion)
{
    if(H == NULL || item == NULL)
        return false;

    StackElement descarte;
    descarte.tipo_accion = 1;
    descarte.item = *item;
    descarte.posicion = posicion;

    return Push(descarte, H->acciones);

}

bool Historial_Deshacer_Ultima(Historial *H, Inventario *Inv)
{
    if (H == NULL || Inv == NULL) return false;

    StackElement ultima_accion;
    
    // Extrae r ultimo elemento (LIFO)
    if (!Pop(H->acciones, &ultima_accion)) 
    {
        printf("\t" GRIS_NIEBLA "No hay acciones en el historial para deshacer." RESET "\n");
        return false;
    }

    if (ultima_accion.tipo_accion == 1) { 
        // Si fue un descarte, lo devolvemos al inventario
        if (Inventario_Anhadir_Item(Inv, ultima_accion.item)) 
        {
            printf("\t" VERDE_ZOMBIE "Deshiciste la accion. " BLANCO_HUESO "%s" VERDE_ZOMBIE " volvio a tu mochila." RESET "\n", ultima_accion.item.name);
            return true;
        } 
        else 
        {
            printf("\t" ROJO_SANGRE "Error: No se pudo devolver el item al inventario." RESET "\n");
            return false;
        }
    }
    return false;
}

void Historial_Mostrar(const Historial *H)
{
    Print_Titulo("BITACORA DE DECISIONES");
    printf("\n");

    if (H == NULL || Pila_Esta_Vacia(H->acciones))
    {
        printf("\t" BLANCO_HUESO "La bitacora esta vacia." RESET "\n");
        return;
    }
    

    StackPosition actual = H->acciones->Next;
    int i = 1;
    while (actual != NULL) 
    {
        if (actual->Element.tipo_accion == 1) 
        {
            printf("\t" MORADO_TOXICO "%d. " GRIS_NIEBLA "Descartaste: " BLANCO_HUESO "%s" GRIS_NIEBLA " (ID: %d)" RESET "\n",
                   i, actual->Element.item.name, actual->Element.item.id);
        }

        actual = actual->Next;
        i++;
    }
}

void Historial_Destruir(Historial *H)
{
    if (H == NULL) 
        return;
    
    if (H->acciones != NULL) 
    {
        Pila_Destruir(&(H->acciones));
    }

    free(H);
}

bool Historial_Guardar_Archivo(const char *ruta, const Historial *H)
{
    if (H == NULL) return 0;
    if (ruta == NULL) return 0;

    FILE *f = fopen(ruta, "w");
    if (f == NULL) return 0;

    StackPosition p = H->acciones->Next;
    while (p != NULL)
    {
        AccionExt *a = (AccionExt *)p;

        char *nombre_item = "NULL";
        if (a->base.item.name != NULL)
        {
            nombre_item = a->base.item.name;
        }

        fprintf(f, "%d|%s|%d|%s|%d|%d|%d|%d|%d\n",
                a->base.tipo_accion, a->descripcion,
                a->base.item.id, nombre_item,
                a->base.item.type, a->base.item.rarity, a->base.item.value,
                a->base.posicion, a->enemigo_id);

        p = p->Next;
    }
    fclose(f);
    return 1;
}

Historial *Historial_Cargar_Archivo(const char *ruta)
{
    if (ruta == NULL) return NULL;

    FILE *f = fopen(ruta, "r");
    if (f == NULL) return NULL;

    Historial *H = Historial_Crear();
    if (H == NULL)
    {
        fclose(f);
        return NULL;
    }

    AccionExt a;
    char nom[100];

    while (1) {
        /* Tipo y rareza temporal */
        int tipo_temp, rareza_temp;
        int r = fscanf(f, "%d|%127[^|]|%d|%99[^|]|%d|%d|%d|%d|%d\n",
                        &a.base.tipo_accion, a.descripcion, &a.base.item.id, nom,
                        &tipo_temp, &rareza_temp, &a.base.item.value,
                        &a.base.posicion, &a.enemigo_id);
        a.base.item.type = (ItemType)tipo_temp;
        a.base.item.rarity = (ItemRarity)rareza_temp;

        if (r != 9) break;
        if (strcmp(nom, "NULL") != 0)
        {
            a.base.item.name = strdup(nom);
        } 
        else
        {
            a.base.item.name = NULL;
        }

        Push(a.base, H->acciones);
    }

    fclose(f);
    return H;
}

bool Historial_Registrar(Historial *H, int tipo, const char *descripcion,
                          const Item *item, int posicion, int enemigo_id)
{
    if (H == NULL || descripcion == NULL)
        return false;

    AccionExt a = {0};
    a.base.tipo_accion = tipo;
    a.base.posicion = posicion;
    a.enemigo_id = enemigo_id;

    strncpy(a.descripcion, descripcion, DESC_MAX - 1);
    a.descripcion[DESC_MAX - 1] = '\0';

    if (item != NULL)
    {
        a.base.item = *item;                    // Copia superficial
        if (item->name != NULL) 
        {
            a.base.item.name = strdup(item->name); // Copia profunda del string
            if (a.base.item.name == NULL)
                return false;
        }
    } 
    else
    {
        a.base.item.id = -1;
        a.base.item.name = NULL;
        a.base.item.type = 0;
        a.base.item.rarity = 0;
        a.base.item.value = 0;
    }

    return Push(a.base, H->acciones);
}