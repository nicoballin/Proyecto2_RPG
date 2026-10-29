#include <stdio.h>
#include "queue.h"
#include "combat.h"

/* Cola de enemigos: FIFO */
/* whiles para la cola enemigos, pvp */
bool Combate_Iniciar(Personaje *P, Inventario *I, Queue cola)
{
    if (P == NULL || cola == NULL) return false;
    if (Cola_Esta_Vacia(cola))
    {
        printf("No hay enemigos para combatir\n");
        return true;
    }

    printf("=== BATALLA ===");
    /* Si la cola enemigos no esta vacia y el jugador esta vivo: */
    while (!Cola_Esta_Vacia(cola) && P->vida > 0)
    {
        /* COLA: FIFO */
        Enemigo *actual = Cola_Front(cola);
        
        /* Necesitamos vivos a ambos para un pvp 1v1 */
        while (!Enemigo_Muerto(actual) && P->vida > 0)
        {
            Combate_Estado(P, actual, cola->size);
            Combate_Menu();
            int opcion = 0;
            printf("Elige una accion: ");
            scanf("%d", &opcion);
            /* 1: jugador ataca enemigo, 2: inventario, 3: objeto*/
        }
        if (Enemigo_Muerto(actual))
        {
            printf("\nDerrotaste a %s!", actual->name);
            Cola_Dequeue(cola);
            Enemigo_Destruir(actual);
        }
    }

    /* Final batalla y ciclos while. Caso derrota y victoria */
    if (P->vida <= 0)
    {
        printf("Game OVER!\n");
        return false;
    }
    printf("Victoria! Derrotaste a todos los enemigos.\n");
    return true;
}

/*
1) Genera una cola vacia
2) que enemigos apareceran segun numero_ola
3) cada enemigo con orden fifo
4) retornar la cola de enemigos ya lista
*/
Queue Generar_Ola(int numero_ola)
{
    Queue ola = Cola_Crear();
    if (ola == NULL) return NULL;
    
    switch (numero_ola)
    {
        case 1:
            break;
        
        default:
            break;
    }
    return ola;
}

void Combate_Menu(void);

void Combate_Estado(const Personaje *P, const Enemigo *E, int restantes);

void Combate_Inventario(Inventario *inv);

bool Combate_Usar_Objeto(Personaje *P, Inventario *inv);

void Combate_Turno_Enemigo(Personaje *P, Enemigo *E);

void Combate_Ataca_Jugador(Personaje *P, Enemigo *E);