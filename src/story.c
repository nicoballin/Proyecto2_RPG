#include "story.h"
#include "combat.h"
#include "item.h"
#include "print.h"

Personaje* Story_Introduccion(void)
{
    char nombre_jugador[50];

    Print_Titulo("U N I V E R S I D A D   Z E R O");
    printf("\n\t" NARANJA_CALABAZA "Noche del 31 de Octubre..." RESET "\n");
    printf("\t" GRIS_NIEBLA "Un desastre biologico en los laboratorios subterraneos" RESET "\n");
    printf("\t" GRIS_NIEBLA "ha transformado el campus  en un infierno." RESET "\n\n");

    printf("\t" BLANCO_HUESO "Identificate, sobreviviente:" RESET "\n");
    Print_Prompt();

    if (scanf("%49s", nombre_jugador) != 1)
    {
        strcpy(nombre_jugador, "Sobreviviente");
    }
    while (getchar() != '\n'); // Limpiar buffer

    // Crear personaje dinamicamente con el nombre ingresado
    Personaje *P = Crear_Personaje(nombre_jugador, 100, 15, 5);

    if (P == NULL)
    {
        printf("\t" ROJO_SANGRE "Error fatal al inicializar al sobreviviente." RESET "\n");
        return NULL;
    }

    printf("\n\t" VERDE_ZOMBIE "Atencion, %s." RESET "\n", P->name);
    printf("\t" GRIS_NIEBLA "Estas atrapado dentro del perimetro de contencion." RESET "\n");
    printf("\t" GRIS_NIEBLA "Tu unico objetivo es encontrar suministros y llegar" RESET "\n");
    printf("\t" GRIS_NIEBLA "a los laboratorios subterraneos para erradicar la amenaza." RESET "\n");

    Esperar_Enter();
    return P;
}

void Story_Explorar_Zona(Personaje *P, Inventario *I, Historial *H)
{
    if(P == NULL || I == NULL) return;

    int opcion_zona = 0;
    Print_Titulo("SELECCION DE SECTOR");
    Print_Opcion(1, "Campus Exterior (Peligro Bajo)");
    Print_Opcion(2, "Facultad de Ingenieria (Peligro Medio)");
    Print_Opcion(3, "Laboratorios Subterraneos (Peligro Extremo)");
    Print_Opcion(0, "Salir");
    opcion_zona = Opcion_Int(0, 3);
    if(opcion_zona == 0) return;

    int enemigos_derrotados = 0;
    int veces_huidas = 0;
    bool explorando = true;

    printf(VERDE_ZOMBIE "\nEmpujas las puertas y entras al sector %d...\n" RESET, opcion_zona);

    while(explorando && P->vida > 0)
    {
        bool buscando = true;

        while(buscando && P->vida > 0)
        {
            //Le puse que al derrotar a MAX_ENEMIGOS_DERROTADOS aparezca el jefe
            if(enemigos_derrotados >= MAX_ENEMIGOS_DERROTADOS)
            {
                Print_Titulo("AMENAZA BIOLOGICA DETECTADA");
                printf(ROJO_SANGRE "Un especimen masivo rompe la pared. Es el Jefe del Sector!\n" RESET);

                Queue jefe_q = Cola_Crear();
                Enemigo* boss = Enemigo_Crear(99, "Mutante Cero", 200 * opcion_zona, 25 * opcion_zona);
                Cola_Enqueue(boss, jefe_q);

                Combate_Iniciar(P, I, jefe_q);
                Cola_Destruir(jefe_q);

                if(P->vida > 0)
                {
                    printf(NARANJA_CALABAZA "\nHas destruido a la aberracion! Entre sus restos encuentras un Objeto EPICO.\n" RESET);
                    
                    Item* epico = Item_Crear(999, "Vacuna Experimental", ITEM_POCION, RAREZA_LEGENDARIA, 100);
                    if(epico != NULL)
                    {
                        Inventario_Anhadir_Item(I, *epico);
                        free(epico);
                    }

                    if(opcion_zona == 3)
                    {
                        Print_Titulo("SUPERVIVENCIA COMPLETADA");
                        printf(BLANCO_HUESO "Has limpiado los laboratorios. La pesadilla ha terminado. Bien Hecho "RESET VERDE_ZOMBIE"%s\n" RESET, P->name);
                        return;
                    }
                    buscando = false;
                    enemigos_derrotados = 0;
                }
                break;
            }

            int probabilidad = rand() % 100;
            if(probabilidad < 33)
            {
                printf(ROJO_SANGRE "\nEscuchas grunhidos! Un grupo de infectados te cierra el paso.\n" RESET);
                printf("1. Luchar por tu vida\n2. Huir\n");
                
                int accion = Opcion_Int(1, 2);

                if(accion == 2)
                {
                    veces_huidas++;
                    printf(GRIS_NIEBLA "Corres por tu vida." ROJO_SANGRE"Huidas: %d/3\n" RESET, veces_huidas);
                    
                    if(veces_huidas >= 3)
                    {
                        printf(ROJO_SANGRE "\nTe acorralan en un pasillo sin salida. Tu cobardia te ha costado la vida "RESET VERDE_ZOMBIE"%s" RESET"...\n", P->name);
                        P->vida = 0;
                    }
                    buscando = false;
                }
                else
                {
                    Queue ola = Generar_Ola(opcion_zona);
                    Combate_Iniciar(P, I, ola);
                    
                    if(!Cola_Esta_Vacia(ola))
                    {
                        Cola_Destruir(ola);
                    }

                    if(P->vida > 0)
                    {
                        enemigos_derrotados++;
                    }
                    buscando = false;
                }
            }
            else if(probabilidad < 53)
            {
                printf(MORADO_TOXICO "\nEl pasillo colapso. Ves dos rutas alternativas:\n" RESET);
                printf("1. Conductos de ventilacion\n2. Salas de aislamiento\n");

                int ruta = Opcion_Int(1, 2);

                if(ruta == 1)
                {
                    printf("Te arrastras por los conductos polvorientos.\n");
                    Item* info_item = Item_Crear(101, "Ruta Conductos", ITEM_OTRO_TIPO, RAREZA_COMUN, 0);
                    Historial_Guardar_Descarte(H, info_item, 1);
                    free(info_item);
                }
                else
                {
                    printf("Avanzas entre camillas oxidadas y sangre seca.\n");
                    Item* info_item = Item_Crear(102, "Ruta Aislamiento", ITEM_OTRO_TIPO, RAREZA_COMUN, 0);
                    Historial_Guardar_Descarte(H, info_item, 2);
                    free(info_item);
                }
            }
            else if(probabilidad < 68)
            {
                printf(NARANJA_CALABAZA "\nVes un casillero semiabierto con suministros RAROS!\n" RESET);
                Item* loot = Item_Crear(rand() % 1000 + 100, "Jeringa de Adrenalina", ITEM_POCION, RAREZA_EPICA, 40);

                if(loot != NULL)
                {
                    printf("Encuentras: %s (Efecto: +%d)\n", loot->name, loot->value);
                    char resp = Opcion_Char("Deseas tomar el objeto? (s/n)");

                    if(resp == 's')
                    {
                        Inventario_Anhadir_Item(I, *loot);
                        printf("Guardado en la mochila.\n");
                    }
                    else
                    {
                        printf("Decides dejar el objeto en el casillero.\n");
                    }
                    free(loot);
                }
                buscando = false;
            }
            else
            {
                printf(GRIS_NIEBLA "Caminas pisando cristales rotos. Solo silencio...\n" RESET);
            }
        }

        if(P->vida > 0 && explorando)
        {
            char continuar = Opcion_Char("Deseas seguir explorando el sector? (s/n)");

            if(continuar != 's')
            {
                explorando = false;
                printf(GRIS_NIEBLA "Regresas a la zona segura.\n" RESET);
            }
        }
    }
}