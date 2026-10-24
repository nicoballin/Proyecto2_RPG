#include <stdio.h>
#include "stack.h"
#include <stdbool.h>

Stack Pila_Crear(void)
{
    Stack s = malloc(sizeof(struct Node));

    if(s == NULL)
        return NULL;

    s->Next = NULL;
    return s;

}

bool Push(ElementType X, Stack s)
{
    if(s==NULL)
    {
        printf("Error en la pila\n");
        return false;
        
    }

    Stack Tmpcell= malloc(sizeof(struct Node));
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

bool Pop(Stack s, ElementType *resultado)
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

bool Top(Stack s, ElementType *resultado)
{
    if(resultado== NULL || Pila_Esta_Vacia(s))
    {

        return false;
    }
    *resultado=s->Next->Element;
    return true;

}



