/**
 * @file print.h
 * @author Nicolas Balic (nabalic@umagallanes.cl)
 * @brief Archivo Header que define colores y funciones esteticas para la UI
 * @version 0.1
 * @date 2026-10-29
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <ctype.h>

// paleta e colores estilo halloween
#define NARANJA_CALABAZA "\033[38;5;208m"
#define VERDE_ZOMBIE     "\033[38;5;118m"
#define MORADO_TOXICO    "\033[38;5;93m"
#define ROJO_SANGRE      "\033[38;5;196m"
#define GRIS_NIEBLA      "\033[38;5;245m"
#define BLANCO_HUESO     "\033[38;5;231m"
#define RESET            "\033[0m"
#define NEGRITA          "\033[1m"

/**
 * @brief Funcion que imprime cualquie texto como TItuo con caracteres epseciales y de color
 * 
 * @param titulo Texto que se quiere mostrar como titulo en ""
 */
void Print_Titulo(const char* titulo);

/**
 * @brief Imprime de manera estetica una opcion en el menu, con laf orma [numero] "Texto".
 * 
 * @param numero es el numero que lleva la opcion (si es -1 no imprime la casilla)
 * @param texto Es lo que dice tal opcion
 */
void Print_Opcion(int numero, const char* texto);

/**
 * @brief Imprime el prompt para ingresar una opcion. 
 *
 * @param n 1 si se queire con mensaje y 0 si se quiere solo simbolo
 */
void Print_Prompt(int n);

/**
 * @brief Imprime el menu inicial*/
void Print_Menu_Inicial();

/**
 * @brief Funcion que usa un getchar par imprimir Prersione Enter para continuar
 * 
 */
void Esperar_Enter();

/**
 * @brief Solicita un numero al usuario, validando la entrada y el rango.
 * 
 * @param min Valor minimo aceptado.
 * @param max Valor maximo aceptado.
 * @return int La opcion valida ingresada por el usuario.
 */
int Opcion_Int(int min, int max);

/**
 * @brief Solicita un caracter al usuario, convirtiendolo a minuscula si es letra y limpiando el buffer.
 * 
 * @param mensaje Texto explicativo que se muestra antes de pedir la entrada.
 * @return char El caracter ingresado.
 */
char Opcion_Char(const char *mensaje);


#endif