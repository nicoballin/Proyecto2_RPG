/**
 * @file story.h
 * @author Nicolas Balic (nbalic@umagallanes.cl)
 * @brief Archivo Header que define las funciones para la introduccion y el desarrollo de la historia del juego
 * @version 0.1
 * @date 2026-10-29
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef STORY_H
#define STORY_H

#include "personaje.h"
#include "inventario.h"
#include "history.h"
#include "queue.h"
#include <string.h>

#define MAX_ENEMIGOS_DERROTADOS 5

/**
 * @brief Solicita el nombre al usuario, crea el personaje y narra la introduccion.
 * 
 * @return Personaje* Puntero al personaje creado dinamicamente.
 */
Personaje* Story_Introduccion();

/**
 * @brief Inicia la exploracion de una zona con generacion algo random
 * de eventos (nada, objeto, enemigos, jefe).
 *
 * @param P Puntero al personaje.
 * @param I Puntero al inventario.
 * @param H Puntero al historial.
 */
void Story_Explorar_Zona(Personaje *P, Inventario *I, Historial *H);

/**
 * @brief Funcion que genera un item al azar de la rareza indicada y lo entrega al jugador
 * 
 * @param I Puntero al inventario del personaje (no puede ser NULL).
 * @param rareza areza del item a generar (RAREZA_COMUN ... RAREZA_LEGENDARIA).
 * @param preguntar true para preguntar al jugador, false para guardarlo directo
 */
void Story_Encontrar_Item(Inventario *I, ItemRarity rareza, bool preguntar);

#endif