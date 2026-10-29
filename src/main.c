#include <stdio.h>
#include <stdlib.h>
#include "../inc/personaje.h"
#include "../inc/inventario.h"

int main() {
    printf("Iniciando prueba del modulo de Nicolas...\n");

    // 1. Crear personaje
    Character *hero = character_create("Arturo", 100, 15, 10);
    if (hero == NULL) {
        printf("Error al crear el personaje.\n");
        return 1;
    }

    // 2. Crear inventario (inicializa la lista doble con centinela)
    Inventory *inv = inventory_create();
    if (inv == NULL) {
        printf("Error al crear el inventario.\n");
        free(hero);
        return 1;
    }

    // 3. Crear objetos
    Item espada = {1, "Espada Larga", "arma", 12};
    Item pocion = {2, "Pocion de Vida", "pocion", 25};

    // 4. Agregar objetos al inventario
    inventory_add_item(inv, espada);
    inventory_add_item(inv, pocion);

    // 5. Listar e interactuar
    inventory_list_items(inv);
    printf("\nEquipando espada...\n");
    inventory_use_or_equip(inv, 1, hero);

    // 6. Verificar estado
    character_show_status(hero);

    // 7. Liberar memoria
    inventory_destroy(inv);
    free(hero);

    printf("\nPrueba finalizada exitosamente.\n");
    return 0;
}