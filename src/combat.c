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
            Combate_Estado(P, actual, cola_size);
            Combate_Menu();

            int opcion = 0;
            printf("Elige una accion: ");
            if (scanf("%d", &opcion) != 1)
            {
                /* mientras no sea enter se salta */
                while (getchar() != '\n') continue;
            }

            /* 1: jugador ataca enemigo, 2: inventario, 3: objeto */
            if (opcion == 1)
            {
                Combate_Ataca_Jugador(P, actual);
                if (!Enemigo_Muerto(actual)) Combate_Turno_Enemigo(P, actual);
            }
            else if (opcion == 2)
            {
                Combate_Inventario(I);
            }
            else if (opcion == 3)
            {
                // objeto _ bool usado
                Combate_Usar_Objeto(P, I);
                if (!Enemigo_Muerto(actual)) Combate_Turno_Enemigo(P,actual);
            }
            else
            {
                printf("Opcion invalida\n");
            }
        }

        if (Enemigo_Muerto(actual))
        {
            printf("\nDerrotaste a %s!", actual->name);
            Cola_Dequeue(cola);
            Destruir_Enemigo(actual);
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
            Cola_Enqueue(Enemigo_Crear(1, "Estudiante de ing civil", 25, 6), ola);
            Cola_Enqueue(Enemigo_Crear(2, "Umagin", 6, 7), ola);
            break;
        case 2:
            Cola_Enqueue(Enemigo_Crear(1, "bariel", 67, 20), ola);
            Cola_Enqueue(Enemigo_Crear(2, "inacapin", 20, 50), ola);
            Cola_Enqueue(Enemigo_Crear(3, "Goblin", 40, 17), ola);
            break;
        default:
        /*caso generico*/
            Cola_Enqueue(Enemigo_Crear(1, "Missingno", 6, 5), ola);
            break;
    }
    return ola;
}

void Combate_Menu(void)
{
    printf("\n=== COMBATE ===\n");
    printf("[1] Atacar\n[2] Ver inventario\n[3] Usar objeto\n");
    printf("==================================================\n");
}

void Combate_Estado(const Personaje *P, const Enemigo *E, int restantes)
{
    printf("\n==============================================\n");
    printf(" JUGADOR: %s | HP: %d / %d PV | ATT: %d | DEF: %d\n", P->name, P->vida, P->max_vida, P->danho, P->defensa);
    printf("Enemigos restantes %d\n", restantes);
    printf("\n==============================================\n");
}

void Combate_Inventario(Inventario *inv)
{
    if (inv == NULL)
    {
        printf("El inventario esta vacio.\n");
        return;
    }
    printf("\n--- MOCHILA DEL JUGADOR ---\n");
    Inventario_Print_Items(inv);
    printf("---------------------------\n");
}

bool Combate_Usar_Objeto(Personaje *P, Inventario *inv)
{
    if (inv == NULL || P = NULL) return false;
}

void Combate_Turno_Enemigo(Personaje *P, Enemigo *E)
{
    if (P == NULL || E == NULL) return;
}

void Combate_Ataca_Jugador(Personaje *P, Enemigo *E)
{
    if (P == NULL || E == NULL) return;

    int danho = P->danho; // danho total (base+arma)
    printf("\n Atacas a %s causando %d de daño! <<<\n", E->name, danho);
    Enemigo_RecibeDanho(E, danho);
}