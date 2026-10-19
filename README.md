# Proyecto-2-EDD

Proyecto 2 de Estructura de Datos.

## Integrantes

- Nicolás Balic
- Ariel Barría
- Gustavo Navarro

## Comandos Makefile

make

Compila el proyecto.

make run

Compila y ejecuta el programa.

make clean

Elimina las carpetas obj y build, junto con los archivos generados durante la compilación.

## Estructura del proyecto

El proyecto se separará en distintos archivos .c y .h con el objetivo de mantener una estructura ordenada y modular.

Además, contará con un Makefile para facilitar la compilación y ejecución del programa.

La estructura general contempla archivos asociados a los distintos módulos del juego y a las estructuras de datos utilizadas.

### Carpetas

- src/ → Contiene los archivos .c del proyecto.
- inc/ → Contiene los archivos .h
- obj/ → Contiene los archivos objeto generados durante la compilación.
- build/ → Contiene el ejecutable generado.
- data/ → Contiene los archivos utilizados para guardar y cargar información del programa.

## Convenciones de código

Para mantener un código uniforme entre todos los integrantes del grupo se utilizarán las siguientes convenciones:

### Funciones

Las funciones utilizarán PascalCase con palabras separadas por guion bajo.

Ejemplo:

Crear_Personaje();
Guardar_Partida();
Mostrar_Historial();
Agregar_Objeto();

### Variables

Las variables utilizarán snake_case.

Ejemplo:

int cantidad_de_objetos;
int vida_personaje;
int enemigos_restantes;
char nombre_zona[50];

### Constantes y #define

Las constantes y definiciones realizadas mediante #define se escribirán completamente en MAYÚSCULAS.

Ejemplo:

#define MAX_OBJETOS 100
#define VIDA_MAXIMA 100
#define MAX_ENEMIGOS 20
#define RUNNING 1

## Organización del proyecto

### Nicolás Balic

Módulo de Inventario y Lista Enlazada

- Implementación de la Lista Enlazada mediante list.h y list.c
- Manejo de memoria dinámica utilizando malloc y free.
- Manejo de punteros y casos límite.
- Implementación de funciones de búsqueda y eliminación.
- Implementación de las estructuras Personaje e Item.
- Desarrollo de inventory.h e inventory.c
- Funciones para agregar, buscar, equipar, usar y eliminar objetos.
- Desarrollo de la interfaz del inventario y estado del personaje en ui.c
- Redacción de la sección de Listas Enlazadas del informe.
- Apoyo en la persistencia de datos del inventario.

### Ariel Barría

Módulo de Combate y Cola

- Implementación de la Cola mediante queue.h y queue.c
- Implementación desde cero utilizando nodos enlazados.
- Operaciones enqueue, dequeue y front.
- Implementación de la estructura Enemigo.
- Desarrollo de combat.h , combat.c , enemy.h y enemy.c
- Implementación del combate por turnos.
- Implementación del sistema de olas de enemigos.
- Uso de la cola para mantener el orden de aparición de los enemigos.
- Desarrollo de la interfaz visual del combate por terminal.
- Visualización de daño, estadísticas y vida del enemigo.
- Redacción de la sección de Colas del informe.
- Configuración del Makefile.
- Diseño de diapositivas para la presentación.

### Gustavo Navarro

Módulo de Exploración, Historial y Pila

- Implementación de la Pila mediante stack.h y stack.c
- Implementación desde cero utilizando nodos enlazados.
- Operaciones push , pop y top.
- Desarrollo del sistema de exploración mediante adventure.h y adventure.c
- Implementación de exploración de zonas y generación de eventos.
- Desarrollo del módulo de historial mediante history.h y history.c
- Implementación de la función de deshacer acciones (Undo).
- Implementación de la lógica para recuperar objetos descartados.
- Desarrollo del menú principal en main.c.
- Desarrollo de la interacción de exploración paso a paso.
- Implementación de la consulta del historial.
- Redacción de la sección de Pilas del informe.
- Desarrollo del módulo para guardar y cargar partidas mediante archivos.
- Preparación del libreto para la presentación.