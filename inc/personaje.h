/**
 * @file personaje.h
 * @author Nicolas Balic (nbalic@umag.cl)
 * @brief Header en donde se define el struct del personaje y algunas funciones
 * @version 0.1
 * @date 2026-10-21
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef CHARACTER_H
#define CHARACTER_H
#include <stdbool.h>
#include "item.h"

// Estructura del Personaje
typedef struct _personaje
{
    char* name;             // Nombre
    int vida;               // Puntos de vida actuales
    int max_vida;           // Puntos de vida max
    int danho;              // Puntos de ataque
    int danho_base;         // Ataque base (sin arma las puras manos)
    int defensa;            // Puntos de defensa
    int defensa_base;            // Puntos de defensa base
    Item arma_equipada;     // Arma equipada actualmente
    bool tiene_arma;        // Bandera por si tiene un arma equipada
    Item armadura_equipada;     // Armadura equipada actualmente
    bool tiene_armadura;        // Bandera por si tiene un armadura equipada
} Personaje;

//Funciones para manejar al personaje
/**
 * @brief Funcion para Crear e inicializar un Personaje en memoria dinamica.
 * 
 * Reserva memoria dinamica con malloc para el struct Personaje
 *  y se asignan sus stats base y atributos por ejemplo equipamiento.
 *
 * @param name Nombre del personaje creado
 *Vida > 0, Otras stats >= 0
 * @param hp Vida inicial del personaje (inicial y max)
 * @param attack Ataueq base del personaje
 * @param defense Defensa base del personaje
 * @return Puntero al Personaje. 
 * Retorna NULL si no se puede asignar memoria para la estructur aen genral o nombre
 * 
 */
Personaje* Crear_Personaje(const char *name, int hp, int attack, int defense);

/**
 * @brief Imprime en consola el estado actual y las estadisticas del personaje.
 *
 * Imprime la info detallada del personaje, su nombre, vida actual/max
 * puntos de ataque, puntos de defensa y el arma actualmente equipada.
 *
 * @param c Puntero a la estruct Personaje que se desea ver.
 *          Si el puntero es NULL se imprime un aviso.
 */
void Mostrar_Personaje(Personaje *P);

/**
 * @brief Libera el personaje y su nombre. Acepta NULL.
 * 
 * @param P Puntero a la estruct Personaje que se desea ver.
 *          Si el puntero es NULL se imprime un aviso.
 */
void Destruir_Personaje(Personaje *P);

#endif