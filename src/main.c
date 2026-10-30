#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "personaje.h"
#include "inventario.h"
#include "history.h"
#include "queue.h"
#include "combat.h"
#include "story.h"
#include "print.h"
#include "save.h"

#define RUTA_GUARDADO "partida.sav"

int main(void)
{
    srand(time(NULL));

    Inventario *inventario_heroe = Inventario_Crear();
    Historial *historial_partida = Historial_Crear();

    if (inventario_heroe == NULL || historial_partida == NULL)
    {
        printf(ROJO_SANGRE "Error fatal: No se pudieron inicializar los subsistemas." RESET "\n");
        Inventario_Destruir(inventario_heroe);   // aceptan NULL
        Historial_Destruir(historial_partida);
        return 1;
    }

    /* ---------- Menu de inicio ---------- */
    Print_Titulo("U N I V E R S I D A D   Z E R O");
    printf("\n");
    Print_Opcion(1, "Nueva Partida");
    Print_Opcion(2, "Cargar Partida");
    Print_Opcion(3, "Salir");
    Print_Prompt(1);
    int inicio = Opcion_Int(1, 3);

    if (inicio == 3)
    {
        Inventario_Destruir(inventario_heroe);
        Historial_Destruir(historial_partida);
        return 0;
    }

    Personaje *heroe = NULL;

    if (inicio == 2)
    {
        heroe = Partida_Cargar(RUTA_GUARDADO, inventario_heroe);
        Historial *h = Partida_Cargar_Historial("partida.sav.hist");
        if (h != NULL)
        {
            Historial_Destruir(historial_partida);
            historial_partida = h;
        }
        if (heroe == NULL)
            printf(GRIS_NIEBLA "\n\tSe iniciara una nueva partida.\n" RESET);
        Esperar_Enter();
    }

    if (heroe == NULL)   // Nueva partida (o fallo al cargar)
    {
        heroe = Story_Introduccion();
        if (heroe == NULL)
        {
            Inventario_Destruir(inventario_heroe);
            Historial_Destruir(historial_partida);
            return 1;
        }

        // inventario inicial
        Item *botiquin = Item_Crear(1, "Botiquin de Primeros Auxilios", ITEM_POCION, RAREZA_COMUN, 30);
        Item *arma_inicial = Item_Crear(2, "Bate de Beisbol con Clavos", ITEM_ARMA, RAREZA_COMUN, 15);
        Item *armadura_inicial = Item_Crear(3, "Chaqueta de Cuero Gruesa", ITEM_ARMADURA, RAREZA_COMUN, 5);

        if (botiquin != NULL && arma_inicial != NULL && armadura_inicial != NULL)
        {
            Inventario_Anhadir_Item(inventario_heroe, *botiquin);
            Inventario_Anhadir_Item(inventario_heroe, *arma_inicial);
            Inventario_Anhadir_Item(inventario_heroe, *armadura_inicial);
            
            free(botiquin);
            free(arma_inicial);
            free(armadura_inicial);

            Inventario_Usar(inventario_heroe, 2, heroe);
            Inventario_Usar(inventario_heroe, 3, heroe);
        }
    }

    int opcion = 0;
    bool salir = false;

    //Gameloop
    while (!salir && heroe->vida > 0)
    {
        Print_Menu_Inicial();
        opcion = Opcion_Int(1, 6);

        switch (opcion)
        {
            case 1:
                Mostrar_Personaje(heroe);
                Esperar_Enter();
                break;
            case 2:
                Story_Explorar_Zona(heroe, inventario_heroe, historial_partida);
                break;
            case 3:
                Inventario_Print_Items(inventario_heroe);
                Esperar_Enter();
                break;
            case 4:
                Historial_Mostrar(historial_partida);
                Esperar_Enter();
                break;
            case 5:
                Partida_Guardar(RUTA_GUARDADO, heroe, inventario_heroe);
                Partida_Guardar_Historial("partida.sav.hist", historial_partida);
                Esperar_Enter();
                break;
            case 6:
                printf("\n" VERDE_ZOMBIE "Has decidido rendirte... La oscuridad devora la universidad.\n" RESET);
                printf(VERDE_ZOMBIE "Adios " RESET ROJO_SANGRE "%s" RESET "\n", heroe->name);
                salir = true;
                break;
            default:
                break;
        }
    }

    if (heroe->vida <= 0)
    {
        Print_Titulo("GAME OVER");
        printf("\n\t" ROJO_SANGRE "%s " RESET VERDE_ZOMBIE "ha sucumbido ante las hordas infectadas." RESET "\n\n", heroe->name);
    }

    Destruir_Personaje(heroe);
    Inventario_Destruir(inventario_heroe);
    Historial_Destruir(historial_partida);

    return 0;
}