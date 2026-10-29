#include <stdio.h>
#include <stdlib.h>
#include "personaje.h"
#include "history.h"
#include "queue.h"
#include "combat.h"

void Mostrar_Menu_Principal(void)
{
    printf("\n=== MENÚ PRINCIPAL ===\n");
    printf("1. Ver Estado del Personaje\n");
    printf("2. Ver Inventario\n");
    printf("3. Simular Combate (Ola 2)\n");
    printf("4. Ver Historial de Descartes\n");
    printf("5. Salir del Juego\n");
    printf("======================\n");
    printf("Elige una opción: ");
}

int main(void)
{
    printf("Iniciando RPG...\n\n");

    Personaje* heroe = Crear_Personaje("Aventurero", 100, 15, 5);
    Inventario* inventario_heroe = Inventario_Crear();
    Historial* historial_partida = Historial_Crear();

    Item* espada = Item_Crear(1, "Espada de Hierro", ITEM_ARMA, RAREZA_COMUN, 10);
    Item* pocion = Item_Crear(2, "Poción de Vida Menor", ITEM_POCION, RAREZA_COMUN, 25);
    
    if (espada)
    {
        Inventario_Anhadir_Item(inventario_heroe, *espada);
        Inventario_Usar(inventario_heroe, 1, heroe);
    }
    if (pocion) Inventario_Anhadir_Item(inventario_heroe, *pocion);
    
    free(espada);
    free(pocion);

    int opcion = 0;
    bool salir = false;

    while (!salir && heroe->vida > 0)
    {
        Mostrar_Menu_Principal();
        
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n'); 
            continue;
        }

        switch (opcion)
        {
            case 1:
                Mostrar_Personaje(heroe);
                break;
            case 2:
                Inventario_Print_Items(inventario_heroe);
                break;
            case 3:
                {
                    printf("\n--- Entrando en zona hostil ---\n");
                    // Usamos la lógica de tu compañero para el combate
                    Queue cola_enemigos = Generar_Ola(2); 
                    Combate_Iniciar(heroe, inventario_heroe, cola_enemigos);
                    // Cola_Destruir ya es manejado si se derrotan, pero aseguramos
                    if (cola_enemigos) Cola_Destruir(cola_enemigos);
                }
                break;
            case 4:
                Historial_Mostrar(historial_partida);
                break;
            case 5:
                printf("\nSaliendo del juego...\n");
                salir = true;
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }

    Destruir_Personaje(heroe);
    Inventario_Destruir(inventario_heroe);
    Historial_Destruir(historial_partida);

    return 0;
}