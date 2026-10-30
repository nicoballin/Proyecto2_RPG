#include "print.h"

void Print_Titulo(const char* titulo)
{
    printf("\n");
    printf("\t" VERDE_ZOMBIE "☣ " MORADO_TOXICO "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" VERDE_ZOMBIE "☣" RESET "\n");
    printf("\t  " NEGRITA NARANJA_CALABAZA "✦ " BLANCO_HUESO "%s" NARANJA_CALABAZA " ✦" RESET "\n", titulo);
    printf("\t" VERDE_ZOMBIE "☣ " MORADO_TOXICO "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" VERDE_ZOMBIE "☣" RESET "\n");
}

void Print_Opcion(int numero, const char* texto)
{
    if(numero == -1) 
        printf("\t" ROJO_SANGRE "%s" RESET "\n", texto);
    else
        printf("\t" MORADO_TOXICO "[" NEGRITA VERDE_ZOMBIE "%d" RESET MORADO_TOXICO "]" RESET " " GRIS_NIEBLA "%s" RESET "\n", numero, texto);
}

void Print_Prompt(int n)
{
    if(n == 0)
    {
        printf("\t" ROJO_SANGRE "  [?] " NARANJA_CALABAZA " > " RESET);
    }
    else
    {
        printf("\t" ROJO_SANGRE "  [?] " GRIS_NIEBLA "Que decides hacer..." NARANJA_CALABAZA " > " RESET);
    }
}

void Print_Menu_Inicial(void)
{
    Print_Titulo("U N I V E R S I D A D   Z E R O");
    printf("\n");
    Print_Opcion(-1, "--- SUPERVIVENCIA ---");
    Print_Opcion(1, "Ver Estado del Sobreviviente");
    Print_Opcion(2, "Explorar Instalaciones");
    Print_Opcion(3, "Revisar Mochila (Inventario)");
    Print_Opcion(4, "Bitacora de Decisiones (Historial)");
    Print_Opcion(5, "Guardar partida");
    Print_Opcion(6, "Rendirse (Salir)");
    Print_Prompt(1);
}

void Esperar_Enter()
{
    printf("\n\t" GRIS_NIEBLA "Presione " ROJO_SANGRE "ENTER" GRIS_NIEBLA " para volver..." RESET);

    // Limpia cualquier residuo que haya quedado en el buffer ANTES de esperar
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int Opcion_Int(int min, int max)
{
    int opcion;
    int leidos;
    
    while (1) 
    {
        leidos = scanf("%d", &opcion);
        
        if (leidos != 1) 
        {
            // Si no leyo un numero (ej. el usuario puso una letra), limpiamos el buffer
            while (getchar() != '\n'); 
            printf("\t" ROJO_SANGRE "Error: Debes ingresar un numero valido." RESET "\n");
        } 
        else if (opcion < min || opcion > max) 
        {
            // Si el numero esta fuera de rango
            printf("\t" ROJO_SANGRE "Error: Opcion fuera de rango (%d - %d)." RESET "\n", min, max);
            while (getchar() != '\n'); // Limpiamos por si puso espacios extras
        } 
        else 
        {
            // Entrada valida
            while (getchar() != '\n'); // Limpiar el salto de linea restante
            return opcion;
        }
    }
}

char Opcion_Char(const char *mensaje)
{
    char c;
    
    while (1) 
    {
        if (mensaje != NULL) {
            printf("%s", mensaje);
        }
        Print_Prompt(0);

        // Leemos un caracter saltando espacios iniciales
        if (scanf(" %c", &c) == 1) 
        {
            // Limpiar el resto de la linea (evita problemas con cadenas largas)
            while (getchar() != '\n'); 
            return (char)tolower((unsigned char)c); // Retorna la letra en minuscula siempre
        }
        
        while (getchar() != '\n'); 
        printf("\t" ROJO_SANGRE "Entrada invalida. Intenta de nuevo." RESET "\n");
    }
}