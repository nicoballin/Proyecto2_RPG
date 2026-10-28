/**
 * @file combat.h
 * @author Ariel Barría (ariebarr@umagallanes.cl)
 * @brief Header en donde se definen las funcionalidades de combate por turnos.
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
#include "personaje.h"
#include "inventario.h"

/**
 * @brief Funcion que inicia el combate.
 * 
 * @return TRUE si se inicia el combate correctamente.
 * @return FALSE si no se inicia el combate.
 */
bool Combate_Iniciar(Personaje *P, Inventario *I, Queue cola);

/**
 * @brief Funcion que genera una oleada de enemigos.
 * 
 * 1) Genera una cola vacia
 * 2) que enemigos apareceran segun numero_ola
 * 3) cada enemigo con orden fifo
 * 4) retornar la cola de enemigos ya lista
 *
 * @param numero_ola Tipo de oleada de enemigos (1,2,3)
 * @return Queue 
 */
Queue Generar_Ola(int numero_ola);

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
 * @brief Funcion que muestra el estado actual en combate.
 * HP jugador, HP enemigo, cantidad de enemigos en cola.
 * 
 * @param P Puntero a la estructura Personaje.
 * @param E Puntero a la estructura Enemigo (en combate, front de la queue).
 * @param restantes Cantidad de enemigos en combate restantes.
 */
void Combate_Estado(const Personaje *P, const Enemigo *E, int restantes);

/**
 * @brief Funcion que permite ver el inventario del personaje.
 * 
 * @param inv Puntero a la estructura Inventario.
 */
void Combate_Inventario(Inventario *inv);

/**
 * @brief Funcion que permite seleccionar y utilizr un objeto del inventario.
 * 
 * @param P Puntero a la estructura Personaje.
 * @param inv Puntero a la estructura Inventario.
 * @return true Si se logro utilizar el objeto, false en caso contrario.
 */
bool Combate_Usar_Objeto(Personaje *P, Inventario *inv);

/**
 * @brief Funcion que ejecuta el ataque del enemigo hacia el personaje. 
 * Calcula la reduccion del danho segun la defensa del personaje
 *
 * @param P Puntero a la estructura Personaje (defiende).
 * @param E Puntero a la estructura Enemigo (ataca).
 */
void Combate_Turno_Enemigo(Personaje *P, Enemigo *E);

/**
 * @brief Funcion que realiza el ataque al jugador.
 * 
 * @param P Puntero a la estructura Personaje (defiende).
 * @param E Puntero a la estructura Enemigo (ataca).
 */
void Combate_Ataca_Jugador(Personaje *P, Enemigo *E);

#endif