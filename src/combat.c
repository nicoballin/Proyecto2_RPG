#include <stdio.h>
#include "queue.h"
#include "combat.h"

/* Cola de enemigos: FIFO */
/* whiles para la cola enemigos, pvp */
bool Combate_Iniciar(Personaje *P, Inventario *I, Queue cola)
{
    if (P == NULL || cola == NULL) 
        return false;

    if (Cola_Esta_Vacia(cola))
    {
        printf("No hay enemigos para combatir\n");
        return true;
    }

    /* Si la cola enemigos no esta vacia y el jugador esta vivo: */
    printf("=== BATALLA ===");
    while (!Cola_Esta_Vacia(cola) && P->vida > 0)
    {
        Enemigo *actual = Cola_Front(cola);
        
        /* Necesitamos vivos a ambos para un pvp 1v1 */
        while (!Enemigo_Muerto(actual) && P->vida > 0)
        {
            Combate_Estado(P, actual, cola->size);
            Combate_Menu();

            int opcion = 0;
            printf("Elige una accion: ");
            if (scanf("%d", &opcion) != 1)
                while (getchar() != '\n') continue; /* limpieza por si escribio letras */

            /* 1: jugador ataca enemigo, 2: inventario, 3: objeto */
            if (opcion == 1)
            {
                Combate_Ataca_Jugador(P, actual);

                if (!Enemigo_Muerto(actual)) 
                    Combate_Turno_Enemigo(P, actual);
            }
            else if (opcion == 2)
            {
                Combate_Inventario(I);
            }
            else if (opcion == 3)
            {
                // objeto _ bool usado
                bool usado = Combate_Usar_Objeto(P, I);

                if (usado && !Enemigo_Muerto(actual)) 
                    Combate_Turno_Enemigo(P,actual);
            }
            else
            {
                printf("Opcion invalida.\n");
            }
        }

        if (Enemigo_Muerto(actual))
        {
            printf("\n>>> Derrotaste a %s! <<<\n", actual->name);
            Cola_Dequeue(cola);
            Enemigo_Destruir(actual);
        }
    }

    /* Final batalla y ciclos while. Caso derrota y victoria */
    if (P->vida <= 0)
    {
        printf("GAME OVER!!\n");
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
    if (ola == NULL) 
        return NULL;
    
    switch (numero_ola)
    {
        case 1:
            Cola_Enqueue(Enemigo_Crear(1, "Zombie comun", 25, 6), ola);
            Cola_Enqueue(Enemigo_Crear(2, "Dragon bebe", 7, 5), ola);
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
    if (E != NULL) 
    {
        printf(" ENEMIGO: %s | HP: %d / %d PV | ATT: %d\n", E->name, E->vida, E->max_vida, E->danho);
    }
    printf("Enemigos restantes %d\n", restantes);
    printf("==============================================\n");
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
    if (inv == NULL || P == NULL) 
        return false;
    Combate_Inventario(inv);

    int id = 0;
    printf("Ingresa ID del objeto a usar (0 para cancelar): ");

    if (scanf("%d", &id) != 1 || id == 0)
    {
        /* limpieza por si escribio letras */
        while (getchar() != '\n');
        printf("Seleccion: 0, Accion cancelada.\n");
        return false;
    }
    return Inventario_Usar(inv, id, P);
}

void Combate_Turno_Enemigo(Personaje *P, Enemigo *E)
{
    if (P == NULL || E == NULL) return;

    int danho_enemigo = E->danho - P->defensa;
    if (danho_enemigo <= 0) 
        danho_enemigo = 1; /* Si es negativo, = 1*/

    P->vida -= danho_enemigo;
    if (P->vida < 0) 
        P->vida = 0;
    printf(">>> %s te esta atacando con %d de daño! <<<\n", E->name, danho_enemigo);
}

void Combate_Ataca_Jugador(Personaje *P, Enemigo *E)
{
    if (P == NULL || E == NULL) return;

    int danho = P->danho; // danho total (base+arma)
    printf("\n>>> Atacas a %s causando %d de daño! <<<\n", E->name, danho);
    Enemigo_RecibeDanho(E, danho);
}