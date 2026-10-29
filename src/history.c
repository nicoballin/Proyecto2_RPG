#include "history.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"

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


