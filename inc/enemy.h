/**
 * @file enemy.h
 * @author Ariel Barría (ariebarr@umag.cl)
 * @brief Header en donde se define el struct del enemigo y funciones esenciales
 * @version 0.1
 * @date 2026-10-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef ENEMY_H
#define ENEMY_H
#include <stdbool.h>

typedef struct _enemigo
{
    int id;                // Identificador del enemigo (unico)
    char* name;            // Nombre del enemigo;
    int vida;              // Puntos de vida actuales
    int max_vida;          // Puntos de vida max    
    int danho;             // Puntos de ataque del enemigo al jugador
} Enemigo;

/* Manejo del enemigo */
/**
 * @brief Funcion que crea un enemigo en memoria dinamica.
 * 
 * @param id Identificador del enemigo [o tipo]
 * @param name Nombre del enemigo
 * @param hp Vida inicial del enemigo (inicial y max)
 * @param danho Ataque del enemigo al jugador
 * @return Puntero al Enemigo.
 */
Enemigo *Crear_Enemigo(int id, char *name, int hp, int danho);

 /**
  * @brief Indica si el enemigo esta muerto o no.
  * 
  * @param E Puntero a la estruct Enemigo que se desea ver.
  * Si el puntero es NULL se imprime un aviso.
  * @return true si el enemigo esta muerto, false en caso contrario.
  */
bool Esta_Muerto(Enemigo *E);

  /**
   * @brief Realiza un ataque al enemigo y actualiza las estadisticas.
   * 
   * @param E Puntero a la estruct Enemigo que se desea atacar.
   * Si el puntero es NULL se imprime un aviso.
   * @param danho Puntos de ataque del enemigo.
   */
void Enemigo_RecibeDanho(Enemigo *E, int danho);

 /**
  * @brief Libera el Enemigo en memoria. Acepta NULL.
  *
  * @param E Puntero a la estruct Enemigo que se desea liberar. 
  * Si el puntero es NULL se imprime un aviso.
  */
void Destruir_Enemigo(Enemigo *E);

#endif