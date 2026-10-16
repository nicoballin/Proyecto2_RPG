# Proyecto 2: RPG (Estructura de Datos)
Segundo proyecto de la asignatura Estructura de Datos, el cual consiste en un RPG.

# Integrantes
- Nicolas Balic
- Gustavo Navarro
- Ariel Barría

# Compilación & ejecución
```
make        # Compila ejecutable
make run    # Ejecuta el RPG
make clean  # borra obj/ y build/
```

# Buenas prácticas & organización

## Convención de nombres
- Funciones:
- Variables:
- Constantes y ``#defines``:

## Otros

Memoria: Todo malloc tiene su free correspondiente antes de salir del programa.
Documentacion: Cada función lleva comentario de su propósito, parámetros, valor de retorno.
Documentacion: No se utilizan ñ (se reemplaza por nh) en ninguna parte del codgio pra evitar errores en compiladores.
Organizacion: src/ para implementación, inc/ para headers, build//obj/ ignorados por git.
Organizacion: Un archivo .c/.h por módulo funcional

## Ejemplo función
```c
int funcion_valor(int valor1, char* valor2)
{
    if (valor1 == 0)
        return;

    /* case disponibles a elegir */
    int snake_case = 0;
    int camelCase = 0;
    int PascalCase = 0;
}
```

## Organización del proyecto
- Nicolas Balic:
- Gustavo Navarro:
- Ariel Barría:
