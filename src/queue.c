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
    if(Q == NULL) return true;
    return (Q->size == 0);
}

bool Cola_Enqueue(QueueElementType X, Queue Q)
{
    if (Q == NULL) return false;

    /* Nuevo nodo, se define P localmente */
    Position P = malloc(sizeof(struct QueueNode));
    if (P == NULL)
    {
        printf("Error de memoria!\n");
        return false;
    }

    P->Element = X;
    P->Next = NULL;

    if (Cola_Esta_Vacia(Q))
    {
        Q->Front = P;
    }
    else
    {
        Q->Rear->Next = P;
    }
    Q->Rear = P;
    Q->size++;
    //Q->capacity++;
    return true;
}

bool Cola_Dequeue(Queue Q)
{
    if(Cola_Esta_Vacia(Q)) return false;

    /* Localmente la posicion que se va a devolver y front pasa al sig. */
    Position P = Q->Front;
    Q->Front = Q->Front->Next;

    /* Si el el frente quedo en NULL la cola esta vacia */
    if (Q->Front == NULL) Q->Rear = NULL;

    free(P); /* Ya actualizada la posicion */
    Q->size--;
    // Q->capacity--;
    return true;
}

QueueElementType Cola_Front(Queue Q)
{
    if (Cola_Esta_Vacia(Q)) return NULL;
    return Q->Front->Element;
}

void Cola_Destruir(Queue Q)
{
    if (Q == NULL) return;

    /* Si la cola esta vacia hace dequeue a cada elemento*/
    while(!Cola_Esta_Vacia(Q))
    {
        Cola_Dequeue(Q);
    }
    free(Q);
}