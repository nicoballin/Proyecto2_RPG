/**
 * @file stack.h
 * @author Gustavo Navarro
 * @brief Implementación de pila
 * @version 0.1
 * @date 2026-10-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>
#include "item.h"

typedef struct Node* PtrToNode; 
typedef PtrToNode Stack; 
typedef PtrToNode Position; 


typedef struct {
    int tipo_accion;
    Item item;
    int posicion;
} ElementType;

struct Node
{ 
   ElementType Element; 
   Position Next; 
};






/**
 * @brief Crea una pilta vacia
 *   
 * @return Retorna el puntero que apunta al centinela
 * y NULL si hay erorr
 */
Stack Pila_Crear(void);


/**
 * @brief Funcion que inserta X en el top.
 * @param X Elemento (se copia por valor)
 * @param s Pila (no puede ser NULL)
 * @return True si se inserto
 * @return False si algun puntero es NULL o no hay memoria.
 */
bool Push(ElementType X, Stack s);


/**
 * @brief Funcion que elimina el top de la pila
 * @param s Pila (no puede ser NULL)
 * @return True si se eliminó
 * @return False si algun puntero es NULL o no hay memoria.
 */
bool Pop(Stack s, ElementType *resultado);

/**
 * @brief Funcion que retorna el elemento top de la pila
 * @param s Pila (no puede ser NULL)
 * @return True si se logro retornar el elemento del top.
 * @return False si algun puntero es NULL o no hay memoria.
 */
bool Top(Stack s, ElementType *resultado);

/**
 * @brief Comprueba si la pila está vacía.
 *
 * @param s Pila que se desea comprobar.
 * @return true si la pila es NULL o no contiene elementos; false en caso contrario.
 */
bool Pila_Esta_Vacia(Stack s);



#endif