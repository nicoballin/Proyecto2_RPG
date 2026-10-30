/**
 * @file inventario.h
 * @author Nicolas Balic (nbalic@umagallanes.cl)
 * @brief Archivo Header para la definicion de la estructura Inventario del personaje, 
 * implementado sobre la lista enlazada
 * @version 0.1
 * @date 2026-10-21
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <stdbool.h>
#include "list.h"
#include "personaje.h"

typedef struct _historial Historial;   // evita dependencias circulares

typedef struct _inventario
{
    List items; // Lista doblemente enlazada con centinela
} Inventario;

/**
 * @brief Funcion para Crear un Inventariio Vacio
 * 
 * @return Retorna un Puntero al Header de la lista Inventario
 * o NULL si hay error. 
 */
Inventario* Inventario_Crear(void); 

/**
 * @brief Funcion para Agregar un item al inventario
 * 
 * @param Inv El inventarrio en forma de lista enlazada
 * @param item Item que se quiere agregar
 * 
 * @return TRUE si se anhadio y False si hubo error.
 */
bool Inventario_Anhadir_Item(Inventario *Inv, Item item);

/**
 * @brief Funcion para imprimir todos los items.
 * Imprime Vacio si no hay items
 * @param Inv El inventarrio en forma de lista enlazada
 */
void Inventario_Print_Items(const Inventario *Inv);

/**
 * @brief Funcion que busca un Item segun su nombre dentro del inventario
 * (no distingue mayusculas). 
 * 
 * @param Inv El inventarrio en forma de lista enlazada
 * @param name Nombre del Item
 * @return Retorna un puntero que apunta a ese item o NULL si no existe.
 */
Item* Inventario_Buscar_Nombre(const Inventario *Inv, const char *name);

/**
 * @brief Funcion para buscar un Item segun su ID dentro del inventario
 * 
 * @param Inv El inventarrio en forma de lista enlazada
 * @param item_id Id del Item (Item.id)
 * @return Retorna un puntero que apunta a ese item o NULL si no existe.
 */
Item* Inventario_Buscar_Id(const Inventario *Inv, int item_id);


/**
 * @brief Usa o equipa el item con ese id sobre el personaje.
 *    DE momento:
 *  - Pocion: cura (sin pasar de max_vida) y se elimina del inventario.
 *  - Arma / Armadura: se equipa y actualiza ataque / defensa.
 *  - Otro: no tiene efecto fuera de combate, devuelve false.
 * 
 * @param Inv El inventarrio en forma de lista enlazada
 * @param item_id Id del Item (Item.id)
 * @param P Puntero hacia el personaje
 * 
 * @return TRUE si se utilizo o equipo. FALSE si no existe, no es usable o hay NULL.
 */
bool Inventario_Usar(Inventario *Inv, int item_id, Personaje *P);

/**
 * @brief Elimina un item del Inventario segun su ID
 * 
 * @param Inv El inventarrio en forma de lista enlazada
 * @param item_id Id del Item (Item.id)
 * @param H Puntero al historial
 * @return TRUE si existia y se elimino o FALSE si no existe.
 */
bool Inventario_Quitar_Item(Inventario *Inv, int item_id, Historial *H);

/**
 * @brief Libera el inventario y todos sus items.
 * 
 * @param Inv El inventario en forma de lista enlazada
 */
void Inventario_Destruir(Inventario* Inv);

/**
 * @brief Funcion que busque un id que no este en uso dentor del inventario
 * 
 * @param I Puntero al inventario
 * @return Retorna el id nuevo
 */
int Generar_Id_Libre(Inventario *I);

#endif