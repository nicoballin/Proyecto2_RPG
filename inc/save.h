/**
 * @file save.h
 * @author Ariel Barria (ariebarr@umagallanes.cl)
 * @brief Header en donde se definen las funcionalidades de guardado.
 * @version 0.1
 * @date 2026-10-29
 * 
 * Requerimiento del pdf: Se debe poder guardar el progreso del juego
 * mediante archivos y cargarlo al iniciar de nuevo el juego.
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef SAVE_H
#define SAVE_H

#include <stdbool.h>
#include "personaje.h"
#include "inventario.h"

/**
 * @brief Guarda el personaje y su inventario en un archivo de texto.
 *
 * 1) Guarda datos del Personaje: Nombre Vida MaxVida Danho Defensa
 * 2) Cuenta items inventario
 * 3) Guarda cada item: ID Tipo Rareza Valor Nombre
 * 4) Guarda partida en archivo
 *
 * @param ruta Ruta del archivo
 * @param P Puntero a estructura del personaje
 * @param I Puntero a estructura inventario
 */
bool Partida_Guardar(const char *ruta, const Personaje *P, const Inventario *I);

/**
 * @brief Carga los datos del archivo en el personaje y en el inventario.
 *
 * 1) Lee en archivo: Nombre (49 caracteres) Vida MaxVida Danho Defensa
 * 2) Crea personaje
 * 3) Carga items
 * 4) Limpia espacio inicial si lo capturo
 *
 * @param ruta Ruta del archivo
 * @param I Puntero a estructura inventario
 */
Personaje* Partida_Cargar(const char *ruta, Inventario *I);

/**
 * @brief Guarda el historial en los datos del archivo (Progreso). Nuevo archivo.
 * 
 * Si bien estas funciones corresponden tambien al historial
 * Por conveniencia y no romper funciones es mejor definirlas en save y usarlas en historial.c
 *
 * @param ruta Ruta del archivo
 * @param H Puntero a historial
 * @return true 
 * @return false 
 */
bool Partida_Guardar_Historial(const char *ruta, const Historial *H);

/**
 * @brief Carga el historial en los datos del archivo (para el progreso).
 * 
 * @param ruta Ruta del archivo
 * @return Historial* 
 */
Historial *Partida_Cargar_Historial(const char *ruta);

#endif