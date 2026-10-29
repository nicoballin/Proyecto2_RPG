/**
 * @file list.h
 * @author Nicolas Balic (nbalic@umagallanes.cl)
 * @brief Archivo Header donde se declara una lista y su operaciones
 * @version 0.1
 * @date 2026-10-21
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "item.h"

typedef Item ListElement; 
typedef struct ListNode* PtrToListNode; 
typedef PtrToListNode List; 
typedef PtrToListNode ListPosition; 

struct ListNode
{ 
   ListElement Element; 
   ListPosition Next; 
   ListPosition Prev; 
};

/**
 * @brief Crea una lista Vacia (solo al centinela)
 *   
 * @return Retorna el puntero que apunta al centinela
 * y NULL si hay erorr
 */
List Lista_Crear(void);

/**
 * @brief Funcion que inserta X justo despues de la posicion P.
 * 
 * @param X Elemento (se copia por valor)
 * @param L Lista (no puede ser NULL)
 * @param P Posicion despues de la cual se inserta (L inserta al inicio)
 * @return True si se inserto
 * @return False si algun puntero es NULL o no hay memoria.
 */
bool Lista_Insertar_Elemento(ListElement X, List L, ListPosition P);

/**
 * @brief Funcion que Elimina un elemento segun su ID
 * 
 * @param id ID del Item
 * @param L la Lista
 * @return TRUE si se elimino
 * @return FALSE si no existe o L es NULL. 
 */
bool Lista_Remover_Elemento(int id, List L);

/**
 * @brief Funcion que berifica si la lista esta vacia
 * 
 * @param L la Lista
 * @return TRUE si esta vacia (o es NULL)
 * @return FALSE si tiene al menos 1 elemento
 */
bool Lista_Esta_Vacia(List L);

/**
 * @brief Funcion par adestruir y liberar la memoria que iutiliza la Lista
 * incluye Nodo y centinela
 * 
 * @param L Lista
 */
void Lista_Destruir(List L);

#endif