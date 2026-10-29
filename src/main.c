#include <stdio.h>
#include <stdlib.h>
#include "personaje.h"
#include "inventario.h"
#include "combat.h"
#include "history.h"
#include "queue.h"

// Función auxiliar para imprimir el menú principal a
void Mostrar_Menu_Principal(void)
{
    printf("\n=== MENÚ PRINCIPAL ===\n");
    printf("1. Ver Estado del Personaje\n");
    printf("2. Ver Inventario\n");
    printf("3. Simular Combate\n");
    printf("4. Ver Historial de Descartes\n");
    printf("5. Salir del Juego\n");
    printf("======================\n");
    printf("Elige una opción: ");
}

int main(void)
{
    printf("Iniciando RPG...\n\n");

    // 1. Inicialización de Estructuras Principales
    Personaje* heroe = Crear_Personaje("Aventurero", 100, 15, 5);
    Inventario* inventario_heroe = Inventario_Crear();
    Historial* historial_partida = Historial_Crear();

    if (heroe == NULL || inventario_heroe == NULL || historial_partida == NULL) {
        printf("Error fatal: No se pudieron inicializar las estructuras base.\n");
        return 1;
    }

    // 2. Creación de Objetos de Prueba (Añadir al inventario)
    Item* espada = Item_Crear(1, "Espada de Hierro", ITEM_ARMA, RAREZA_COMUN, 10);
    Item* pocion = Item_Crear(2, "Poción de Vida Menor", ITEM_POCION, RAREZA_COMUN, 25);
    Item* armadura = Item_Crear(3, "Peto de Cuero", ITEM_ARMADURA, RAREZA_COMUN, 5);

    if (espada) Inventario_Anhadir_Item(inventario_heroe, *espada);
    if (pocion) Inventario_Anhadir_Item(inventario_heroe, *pocion);
    if (armadura) Inventario_Anhadir_Item(inventario_heroe, *armadura);

    // Los punteros de los items creados individualmente ya se copiaron por valor a la lista. 
    // Liberamos los temporales para evitar memory leaks (la lista tiene su propia copia).
    Item_Destruir(espada);
    Item_Destruir(pocion);
    Item_Destruir(armadura);

    // 3. Bucle Principal del Juego
    int opcion = 0;
    bool salir = false;

    while (!salir)
    {
        Mostrar_Menu_Principal();
        
        // Leer la entrada del usuario
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada inválida. Por favor, ingresa un número.\n");
            // Limpiar el buffer de entrada en caso de error
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
                    // Simulación de Combate (Se genera una cola de prueba)
                    printf("\n--- Entrando en zona hostil ---\n");
                    Queue cola_enemigos = Cola_Crear();
                    
                    Enemigo* e1 = Enemigo_Crear(1, "Goblin Explorador", 30, 8);
                    Enemigo* e2 = Enemigo_Crear(2, "Orco Guerrero", 50, 15);
                    
                    Cola_Enqueue(e1, cola_enemigos);
                    Cola_Enqueue(e2, cola_enemigos);

                    // Se asume que en combat.c terminarás la implementación de la interfaz de batalla.
                    // Combate_Iniciar(heroe, inventario_heroe, cola_enemigos);
                    
                    // Nota: Si usas Combate_Iniciar, asegúrate de liberar la cola al final.
                    printf("Simulando inicio de combate (Funcionalidad en desarrollo)\n");
                    Cola_Destruir(cola_enemigos);
                }
                break;
            case 4:
                Historial_Mostrar(historial_partida);
                break;
            case 5:
                printf("\nSaliendo del juego... ¡Hasta la próxima!\n");
                salir = true;
                break;
            default:
                printf("Opción no válida. Intenta de nuevo.\n");
                break;
        }
    }

    // 4. Liberación de Memoria General
    printf("Liberando recursos...\n");
    Destruir_Personaje(heroe);
    Inventario_Destruir(inventario_heroe);
    Historial_Destruir(historial_partida);

    return 0;
}