#include <stdio.h>
#include "print.h"
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
        printf(GRIS_NIEBLA "El area parece estar despejada... por ahora." RESET "\n");
        return true;
    }

    /* Si la cola enemigos no esta vacia y el jugador esta vivo: */
    Print_Titulo("ENTRANDO EN COMBATE");
    while (!Cola_Esta_Vacia(cola) && P->vida > 0)
    {
        Enemigo *actual = Cola_Front(cola);
        
        /* Necesitamos vivos a ambos para un pvp 1v1 */
        while (!Enemigo_Muerto(actual) && P->vida > 0)
        {
            Combate_Estado(P, actual, cola->size);
            Combate_Menu();

            int opcion = -1;
            opcion = Opcion_Int(1, 3);
        
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
<<<<<<< HEAD
            printf("\n>>> Derrotaste a %s! Se retira de la cola de combate. <<<\n", actual->name);
=======
            printf("\n" NARANJA_CALABAZA ">>> Has destrozado a [%s]! <<<" RESET "\n", actual->name);
>>>>>>> d48f586d691815c140fc43734f339acdb5bc8f77
            Cola_Dequeue(cola);
            Enemigo_Destruir(actual);
        }
    }

    /* Final batalla y ciclos while. Caso derrota y victoria */
    if (P->vida <= 0)
    {
        Print_Titulo("GAME OVER");
        printf(ROJO_SANGRE "Has sido devorado..." RESET "\n");
        return false;
    }
<<<<<<< HEAD
    printf("\t VICTORIA!! DERROTASTE LA OLEADA!!\n");
=======

    printf(VERDE_ZOMBIE "Lograste sobrevivir a este encuentro. El silencio vuelve a la zona." RESET "\n");

>>>>>>> d48f586d691815c140fc43734f339acdb5bc8f77
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
        case 1: // Campus Exterior (Bajo)
            Cola_Enqueue(Enemigo_Crear(1, "Estudiante Infectado", 25, 6), ola);
            Cola_Enqueue(Enemigo_Crear(2, "Perro Callejero Rabioso", 15, 8), ola);
            break;
        case 2: // Ingenieria (Medio)
            Cola_Enqueue(Enemigo_Crear(1, "Conserje Mutado", 45, 12), ola);
            Cola_Enqueue(Enemigo_Crear(2, "Profesor Podrido", 50, 15), ola);
            Cola_Enqueue(Enemigo_Crear(3, "Masa de Carne Temblorosa", 60, 10), ola);
            break;
        case 3: // Laboratorios (Alto)
            Cola_Enqueue(Enemigo_Crear(1, "Investigador Cero", 80, 20), ola);
            Cola_Enqueue(Enemigo_Crear(2, "Sujeto de Pruebas Fallido", 100, 25), ola);
            Cola_Enqueue(Enemigo_Crear(3, "Amalgama Biologica", 150, 30), ola);
            break;
        default: // Caso de error
            Cola_Enqueue(Enemigo_Crear(1, "Error de Sistema Z", 10, 1), ola);
            break;
    }
    return ola;
}

void Combate_Menu(void)
{
    printf("\n");
    Print_Opcion(-1, "--- ACCIONES DE SUPERVIVENCIA ---");
    Print_Opcion(1, "Atacar con tu arma");
    Print_Opcion(2, "Revisar la Mochila");
    Print_Opcion(3, "Usar Suministro Rapido");
}

void Combate_Estado(const Personaje *P, const Enemigo *E, int restantes)
{
    printf("\n" MORADO_TOXICO "==============================================" RESET "\n");
    printf(BLANCO_HUESO " %s " RESET "| " VERDE_ZOMBIE "VIDA: %d / %d" RESET " | ATAQUE: %d | DEFENSA: %d\n", 
           P->name, P->vida, P->max_vida, P->danho, P->defensa);
           
    if (E != NULL) 
    {
        printf(ROJO_SANGRE " AMENAZA: %s " RESET "| VIDA: %d / %d | DAÑO: %d\n", 
               E->name, E->vida, E->max_vida, E->danho);
    }
    printf(GRIS_NIEBLA "Enemigos acechando: %d" RESET "\n", restantes);
    printf(MORADO_TOXICO "==============================================" RESET "\n");
}

void Combate_Inventario(Inventario *inv)
{
    if (inv == NULL)
    {
        printf(GRIS_NIEBLA "Tu mochila esta vacia." RESET "\n");
        return;
    }
    Inventario_Print_Items(inv);
}

bool Combate_Usar_Objeto(Personaje *P, Inventario *inv)
{
    if (inv == NULL || P == NULL) return false;
        
    Combate_Inventario(inv);

    printf(GRIS_NIEBLA "\n(Ingresa 0 para cancelar la accion)" RESET "\n");
    printf("Ingresa el ID del suministro a usar");
    
    int id = 0;
    Print_Prompt(1);
    if (scanf("%d", &id) != 1 || id == 0)
    {
        while (getchar() != '\n');
        printf(GRIS_NIEBLA "Decides guardar tus cosas para despues." RESET "\n");
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
    printf(ROJO_SANGRE "\n!!! [%s] te ataca causando %d de danho !!!" RESET "\n", E->name, danho_enemigo);
}

void Combate_Ataca_Jugador(Personaje *P, Enemigo *E)
{
    if (P == NULL || E == NULL) return;

    int danho = P->danho; // danho total (base+arma)
    printf("\n" VERDE_ZOMBIE ">>> Golpeas a [%s] con todas tus fuerzas causandole %d de danho!" RESET "\n", E->name, danho);
    Enemigo_RecibeDanho(E, danho);
}