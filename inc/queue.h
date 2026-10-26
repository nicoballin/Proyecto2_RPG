/**
 * @file queue.h
 * @author Ariel Barría (ariebarr@umagallanes.cl)
 * @brief Header en donde se define la cola a utilizar.
 * @version 0.1
 * @date 2026-10-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Node* Position; 
typedef struct Queue* Queue; 

/* Definicion del tipo de elemento a utilizar 
* (_enemigo: para no crear conflictos con otros tipos de elementos) */
typedef struct _enemigo Enemigo;
typedef Enemigo* ElementType;

/* Definicion del nodo a utilizar */
struct Node
{ 
   ElementType Element; 
   Position Next; 
   Position Prev; 
};

/* Definicion de la cola */
struct Queue
{
    Position Front;
    Position Rear;
    int size;
    int capacity;
};

/**
 * @brief Crea una cola vacia (solo al centinela)
 *   
 * @return Retorna el puntero que apunta al centinela
 * y NULL si hay error
 */
Queue Cola_Crear(void);

/**
 * @brief Funcion que inserta X justo despues de la posicion P.
 * 
 * @param X Elemento (se copia por valor)
 * @param Q Cola (no puede ser NULL)
 * @return True si se inserto
 * @return False si algun puntero es NULL o no hay memoria.
 */
bool Cola_Enqueue(ElementType X, Queue Q);

/**
 * @brief Funcion que Elimina un elemento segun su ID
 * 
 * Funcion booleana.
 * 
 * @param Q la Cola
 * @return TRUE si se elimino
 * @return FALSE si no existe o Q es NULL. 
 */
bool Cola_Dequeue(Queue Q);

/**
 * @brief Funcion que berifica si la cola esta vacia
 * 
 * @param Q la Cola
 * @return TRUE si esta vacia (o es NULL)
 * @return FALSE si tiene al menos 1 elemento
 */
bool Cola_Esta_Vacia(Queue Q);

/**
 * @brief Funcion que devuelve el Frente (front) de la cola
 *
 * Funcion de tipo ElementType (un elemento dentro de la cola)
 *
 * @param Q la Cola
 * @return El elemento que esta en el Frente
 * @return NULL si Q es NULL o esta vacia
 */
ElementType Cola_Front(Queue Q);

/**
 * @brief Funcion par adestruir y liberar la memoria que iutiliza la Cola
 * incluye Nodo y centinela
 * 
 * @param Q Cola
 */
void Cola_Destruir(Queue Q);


#endif