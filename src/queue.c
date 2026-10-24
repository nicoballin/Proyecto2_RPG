#include <stdio.h>
#include "queue.h"

/*
Implementación desde cero utilizando nodos enlazados. (Sin tamanho fijo).
*/
Queue Cola_Crear(void)
{
    Queue Q = malloc(sizeof(struct Queue));
    if(Q == NULL)
    {
        printf("Error: No hay memoria disponible para crear la cola\n");
        return NULL;
    }
    Q->Front = NULL;
    Q->Rear = NULL;
    Q->size = 0;
    Q->capacity = 0;

    return Q;
}

/* Si la cola esta vacia, se devuelve NULL */
bool Cola_Esta_Vacia(Queue Q)
{
    if(Q == NULL)
    {
        printf("La cola esta vacia!\n");
        return true;
    }
    return (Q->size == 0);
}

bool Cola_Enqueue(ElementType X, Queue Q, Position P)
{
    if (Q == NULL) return false;

    /* Nuevo nodo */
    P = malloc(sizeof(struct Node));
    if (P == NULL) return false;

    P->Element = X;
    P->Next = NULL;

    if (Cola_Esta_Vacia(Q))
    {
        Q->Front = P;
        Q->Rear = P;
        Q->size++;
        Q->capacity++;
    }
    else
    {
        Q->Rear->Next = P;
        Q->Rear = P;
        Q->size++;
    }
    return true;
}

bool Cola_Dequeue(int id, Queue Q)
{
    if (Q == NULL) return false;

    /* La id entregada en la funcion se vuelve la id del primer elemento de la cola*/
    id = Q->Front->Element.id;
    Position P = Q->Front;
    Q->Front = Q->Front->Next;
    
    /* Si al avanzar qued vacia se actualiza el puntero del final */
    if (Q->size == 0)
    {
        Q->Front = NULL;
        Q->Rear = NULL;
    }

    free(P); /* Ya actualizada la posicion */
    Q->size--;
    Q->capacity--;
    return true;
}