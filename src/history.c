#include "history.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

    


}


