/**
 * @file stack.h
 * @author Gustavo Navarro
 * @brief Implementacion de pila
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

typedef struct StackNode *Stack;

typedef struct {
    int tipo_accion;
    Item item;
    int posicion;
} StackElement;

typedef struct StackNode *StackPosition;

struct StackNode {
    StackElement Element;
    StackPosition Next;
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
bool Push(StackElement, Stack s);


/**
 * @brief Funcion que elimina el top de la pila
 * @param s Pila (no puede ser NULL)
 * @return True si se elimino
 * @return False si algun puntero es NULL o no hay memoria.
 */
bool Pop(Stack s, StackElement *resultado);

/**
 * @brief Funcion que retorna el elemento top de la pila
 * @param s Pila (no puede ser NULL)
 * @return True si se logro retornar el elemento del top.
 * @return False si algun puntero es NULL o no hay memoria.
 */
bool Top(Stack s, StackElement *resultado);

/**
 * @brief Comprueba si la pila esta vacia.
 *
 * @param s Pila que se desea comprobar.
 * @return true si la pila es NULL o no contiene elementos; false en caso contrario.
 */
bool Pila_Esta_Vacia(Stack s);


/**
 * @brief Libera todos los nodos de la pila, incluido el nodo centinela.
 *
 * @param s Direccion de la pila que se desea destruir.
 * Si s o la pila apuntada son NULL, no realiza ninguna accion.
 * @post La pila queda establecida en NULL.
 */
void Pila_Destruir(Stack *s);

#endif