#include <stdio.h>
#include "list.h"


List Lista_Crear(void)
{
    List L = malloc(sizeof(struct Node));
    if(L == NULL)
    {
        printf("Error: No hay memoria disponible para crear la lista\n");
        return NULL;
    }
    L->Next = NULL;
    L->Prev = NULL;

    return L;
}

bool Lista_Insertar_Elemento(ElementType X, List L, Position P)
{
    if (L == NULL || P == NULL)
    {
        printf("Error: Lista o Posicion NULL\n");
        return false;
    }
        
    Position TmpCell = malloc(sizeof(struct Node)); 
    if (TmpCell == NULL)
    {
        printf("Error: No hay memoria disponible para insertar el elemento\n");
        return false;
    }

    TmpCell->Element = X; 
    TmpCell->Next = P->Next;          
    TmpCell->Prev = P;                

    if (P->Next != NULL) 
        P->Next->Prev = TmpCell;      
        
    P->Next = TmpCell;

    return true;
}

bool Lista_Remover_Elemento(int id, List L)
{
    if(L == NULL)
    {
        printf("Error: la lista esta vacia!!\n");
        return false;
    }

    Position P = L->Next; 
    while (P != NULL && P->Element.id != id) 
    {
        P = P->Next;
    }
    if(P == NULL)
    {
        printf("El item de ID %d no exite!!\n", id);
        return false;
    }

    P->Prev->Next = P->Next;
    if(P->Next != NULL)
        P->Next->Prev = P->Prev;
    free(P);

    return true;
}

bool Lista_Esta_Vacia(List L)
{
    if(L == NULL || L->Next == NULL)
        return false;
    
    return true;
}

void Lista_Destruir(List L)
{
    Position P = L;
    while (P != NULL) 
    {
        Position Tmp = P->Next;
        free(P);
        P = Tmp;
    }
}
