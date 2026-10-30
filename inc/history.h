/**
 * @file history.h
 * @author Gustavo Navarro
 * @brief Implementacion del historial
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

/* Acciones para el historial */
#define ACC_DESCARTE 1
#define ACC_USO_POCION 2
#define ACC_EQUIPAR 3
#define ACC_DES_EQUIPAR 4
#define ACC_DERROTA_ENEMIGO 5
#define ACC_ENCONTRAR_OBJETO 6
#define ACC_HUIR 7

typedef struct {
    char descripcion[128];    // "Se derrotó al enemigo Goblin"
    Item item;                // Item involucrado (para revertir descarte)
    int posicion_inventario;  // Posición donde estaba en inventario
    int enemigo_id;           // ID del enemigo (referencia)
} Accion;

typedef struct _historial Historial;

/**
 * @brief Crea un historial vacio para registrar acciones.
 */
Historial *Historial_Crear(void);

/**
 * @brief Guarda los datos de un objeto descartado para poder recuperarlo despues.
 */
bool Historial_Guardar_Descarte(Historial *H, const Item *item, int posicion);

/**
 * @brief Registra una acción genérica en el historial (LIFO).
 */
bool Historial_Registrar(Historial *H, int tipo, const char *descripcion, 
                        const Item *item, int posicion, int enemigo_id);

/**
 * @brief Deshace el ultimo descarte registrado y devuelve el objeto al inventario.
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

/**
 * @brief Guarda el historial en archivo de texto.
 */
bool Historial_Guardar_Archivo(const char *ruta, const Historial *H);

/**
 * @brief Carga el historial desde archivo de texto.
 */
Historial *Historial_Cargar_Archivo(const char *ruta);

#endif