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

int main(void)
{
    srand(time(NULL));

    //Inicio de la hsitoria con la creacion del personaje
    Personaje *heroe = Story_Introduccion();
    
    if (heroe == NULL) return 1;
    

    // Inicio del inventario e historial
    Inventario *inventario_heroe = Inventario_Crear();
    Historial *historial_partida = Historial_Crear();

    if (inventario_heroe == NULL || historial_partida == NULL)
    {
        printf(ROJO_SANGRE "Error fatal: No se pudieron inicializar los subsistemas." RESET "\n");
        Destruir_Personaje(heroe);
        return 1;
    }

    //Primer objeto (botiquin o nose)
    Item *botiquin = Item_Crear(1, "Botiquin de Emergencia", ITEM_POCION, RAREZA_COMUN, 30);
    if (botiquin != NULL)
    {
        Inventario_Anhadir_Item(inventario_heroe, *botiquin);
        free(botiquin);
    }

    int opcion = 0;
    bool salir = false;

    //Gameloop
    while (!salir && heroe->vida > 0)
    {
        Print_Menu_Inicial();
        opcion = Opcion_Int(1, 5);

        switch (opcion)
        {
            case 1:
            {
                Mostrar_Personaje(heroe);
                Esperar_Enter();
                break;
            }
            case 2:
            {
                Story_Explorar_Zona(heroe, inventario_heroe, historial_partida);
                break;
            }
            case 3:
            {
                Inventario_Print_Items(inventario_heroe);
                Esperar_Enter();
                break;
            }
            case 4:
            {
                Historial_Mostrar(historial_partida);
                Esperar_Enter();
                break;
            }
            case 5:
            {
                printf("\n" VERDE_ZOMBIE "Has decidido rendirte... La oscuridad devora la universidad.\n"RESET);
                printf(VERDE_ZOMBIE"Adios "RESET ROJO_SANGRE"%s" RESET "\n", heroe->name);
                salir = true;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    if (heroe->vida <= 0)
    {
        Print_Titulo("GAME OVER");
        printf("\n\t" ROJO_SANGRE "%s "RESET VERDE_ZOMBIE"ha sucumbido ante las hordas infectadas." RESET "\n\n", heroe->name);
    }

    //Liberacion de memoria
    Destruir_Personaje(heroe);
    Inventario_Destruir(inventario_heroe);
    Historial_Destruir(historial_partida);

    return 0;
}