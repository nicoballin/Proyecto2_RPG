/**
 * @file history.h
 * @author Gustavo Navarro
 * @brief Implementación del historial
 * @version 0.1
 * @date 2026-10-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef HISTORY_H
#define HISTORY_H

#include <stdbool.h>
#include "item.h"
#include "inventario.h"

typedef struct _historial Historial;

/**
 * @brief Crea un historial vacío para registrar acciones.
 */
Historial *Historial_Crear(void);

/**
 * @brief Guarda los datos de un objeto descartado para poder recuperarlo después.
 */
bool Historial_Guardar_Descarte(Historial *H, const Item *item, int posicion);

/**
 * @brief Deshace el último descarte registrado y devuelve el objeto al inventario.
 */
bool Historial_Deshacer_Ultima(Historial *H, Inventario *Inv);

/**
 * @brief Muestra las acciones registradas en el historial.
 */
void Historial_Mostrar(const Historial *H);

/**
 * @brief Libera la memoria utilizada por el historial.
 */
void Historial_Destruir(Historial *H);

#endif