/**
 * @file combat.h
 * @author Ariel Barría (ariebarr@umagallanes.cl)
 * @brief Header en donde se definen las funcionalidades de combate.
 * @version 0.1
 * @date 2026-10-24
 * 
 * Esta funcionalidad debera permitir (Requerimientos del pdf):
 * - Enfrentar un enemigo (en orden): El sistema debe permitir combates contra varios enemigos. 
 * Cada enemigo tendrá asignado un número de aparición, que determinará el orden en que 
 * deberán ser enfrentados. Por ejemplo, si aparecen tres enemigos, el personaje deberá
 * derrotar primero al enemigo 1, luego al enemigo 2 y, finalmente, al enemigo 3.
 * - Ver inventario
 * - Utilizar objeto
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef COMBAT_H
#define COMBAT_H

/* Involucrar personajes, enemigos e inventario */

#include "enemy.h"
#include "queue.h"
#include "character.h"
#include "inventory.h"

/**
 * @brief Funcion que inicia el combate.
 * 
 * @return TRUE si se inicia el combate correctamente.
 * @return FALSE si no se inicia el combate.
 */
bool Iniciar_Combate(Personaje *P, Inventario *I, Queue cola);

/**
 * @brief Funcion que muestra el menu del combate.
 * 
 * Muestra las opciones de combate:
 * - Enfrentar enemigo
 * - Ver inventario
 * - Utilizar objeto
 * @param void void.
 */
void Combate_Menu(void);

/**
 * @brief Funcion que permite ver el inventario del personaje.
 * 
 * @param inv Puntero a la estructura Inventario.
 */
void Combate_Inventario(Inventario *inv);

#endif