#include <stdio.h>
#include "stack.h"
#include <stdbool.h>

Stack Pila_Crear(void)
{
    Stack s = malloc(sizeof(struct StackNode));

    if(s == NULL)
        return NULL;

    s->Next = NULL;
    return s;

}

bool Push(StackElement X, Stack s)
{
    if(s==NULL)
    {
        printf("Error en la pila\n");
        return false;
        
    }

    StackPosition Tmpcell= malloc(sizeof(struct StackNode));
    if(Tmpcell == NULL)
    {
        return false;
    }
    Tmpcell->Element=X;
    Tmpcell->Next=s->Next;
    s->Next=Tmpcell;
    return true;
}

bool Pila_Esta_Vacia(Stack s)
{
    return s == NULL || s->Next == NULL;
}

bool Pop(Stack s, StackElement *resultado)
{
    Stack FirstCell;

    if(resultado== NULL || Pila_Esta_Vacia(s))
    {

        return false;

    }
    
    FirstCell=s->Next;
    *resultado = FirstCell->Element;
    s->Next=s->Next->Next;
    free(FirstCell);
    return true;

}

bool Top(Stack s, StackElement *resultado)
{
    if(resultado== NULL || Pila_Esta_Vacia(s))
    {

        return false;
    }
    *resultado=s->Next->Element;
    return true;

}

void Pila_Destruir(Stack *s)
{
    if (s == NULL || *s == NULL)
        return;

    StackPosition actual = (*s)->Next; /* saltar el header */

    while (actual != NULL)
    {
        StackPosition siguiente = actual->Next;
        if (actual->Element.item.name != NULL)
        {
            free(actual->Element.item.name); /*nombre guardado en la accion*/
        }
        free(actual);
        actual = siguiente;
    }
    free(*s); /* free a la cabecera*/
    *s = NULL;

}

