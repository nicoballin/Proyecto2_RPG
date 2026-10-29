/**
 * @file item.h
 * @author Nicolas Balic
 * @brief Header que contiene la definicion de un Item
 * @version 0.1
 * @date 2026-10-21
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef ITEM_H
#define ITEM_H
#define MAX_ITEMS 50 //nu, de items maximos
#define MIN_ID 1
#define MAX_ID 500
/**
 * @brief Enum destinado a los tipos de items que existen en el juego con la forma ITEM_NOMBRE
 * 
 */
typedef enum 
{
    ITEM_ARMA,
    ITEM_POCION,
    ITEM_ARMADURA,
    ITEM_OTRO_TIPO
} ItemType;

/**
 * @brief Enum destinado a las calidades / Rarezas que pueden tener los items. forma ITEM_RAREZA
 * 
 */
typedef enum
{
    RAREZA_LEGENDARIA,
    RAREZA_EPICA,
    RAREZA_RARA,
    RAREZA_COMUN
} ItemRarity;

/**
 * @brief Struct destinada a definir lo que es un Item, su numbre, id, tipo y valor. Mas por agregar:
 * 
 */
typedef struct _item
{
    int id;              // ID unico del objeto (Hacer defines)
    char* name;          // Nombre del objeto
    ItemType type;       // Tipo de objeto  (ej: arma, armadura, poti)
    ItemRarity rarity;   // Rareza del objeto
    int value;           // Valor o efecto (ej: +5 ataque, +20 salud)
} Item;


//Funciones
/**
 * @brief Crea un Item en memoria dinamica.
 * 
 * @param id Id del item (identifica cual es)
 * @param name Nombre del item
 * @param type Tipo de item con la forma ITEM_TIPO
 * @param rarity Rareza del item con la forma ITEM_RAREZA 
 * @param value Valor del item o efecto
 * @return Puntero al Item, NULL si no hay memoria disponible.
 */
Item* Item_Crear(int id, const char* name, ItemType type, ItemRarity rarity, int value);

/**
 * @brief Funcion que Destruye un Item (libera memoria)
 * 
 * @param item Puntero al item 
 */
void Item_Destruir(Item* item);

/**
 * @brief FUncion que devuelve el Tipo de item como texto
 * 
 * @param type Tipo de item con la forma ITEM_TIPO
 * @return El Tipo del item como texto
 */
const char* Item_Tipo_A_Texto(ItemType type);

/**
 * @brief Funcion que devuelve la Rareza del item como texto
 * 
 * @param rarity Rareza del item con la forma ITEM_RAREZA
 * @return La Rareza del item como texto
 */
const char* Item_Rareza_A_Texto(ItemRarity rarity);

/**
 * @brief Crea un item al azar entre los predeterminados de una rareza.
 *
 * @param rareza Rareza deseada (RAREZA_COMUN ... RAREZA_LEGENDARIA)
 * @param id Id que tendra el item
 * @return Puntero al Item, NULL si hay error.
 */
Item* Item_Generar(ItemRarity rareza, int id);

/**
 * @brief Funcion que asigna una rareza aleatoria a un item
 * 
 * @return ItemRarity 
 */
ItemRarity Rareza_Aleatoria(void);

#endif