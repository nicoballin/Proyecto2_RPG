#include <stdio.h>
#include "queue.h"
#include "enemy.h"

/* Main prueba*/
int main(void)
{
    Queue cola = Cola_Crear();
    if (cola == NULL)
    {
        printf("Error al crear cola\n");
        return 1;
    }

    Enemigo *e1 = Enemigo_Crear(1, "dragon", 30, 8);
    Enemigo *e2 = Enemigo_Crear(2, "guerrero", 67, 15);
    Cola_Enqueue(e1, cola);
    Cola_Enqueue(e2, cola);
    printf("cola enemigos %d\n", cola->size);

    printf("simulando ataque\n\n");
    while (!Cola_Esta_Vacia(cola))
    {
        Enemigo *actual = Cola_Front(cola);
        Enemigo_Mostrar(actual);
        printf(">> jugador ataca %s con 200 danho\n", actual->name);
        Enemigo_RecibeDanho(actual, 200);

        if (Enemigo_Muerto(actual))
        {
            printf(">> derrotado\n");
            Cola_Dequeue(cola);
            Enemigo_Destruir(actual);
            printf("Quedan %d enemigos en cola\n", cola->size);
        }
    }
    Cola_Destruir(cola);
    printf("fin combate\n");
    return 0;
}