# Introducción

## Indice

- [Introducción](#introducción)
  - [Indice](#indice)
  - [Parciales](#parciales)
  - [Información Extra](#información-extra)
- [Clase 1 - Repaso](#clase-1---repaso)
- [Clase 2 - Estructura de Datos - Pila](#clase-2---estructura-de-datos---pila)
  - [Nodos](#nodos)
  - [TDA Pila - Explicación](#tda-pila---explicación)
  - [TDA Pila Estatico](#tda-pila-estatico)
    - [Estructura](#estructura)
    - [Crear Pila](#crear-pila)
    - [Pila Vacia](#pila-vacia)
    - [Pila Llena](#pila-llena)
    - [Poner en Pila](#poner-en-pila)
    - [Ver Tope](#ver-tope)
    - [Sacar de Pila](#sacar-de-pila)
    - [Vaciar Pila](#vaciar-pila)
    - [Ejercicio Parcial](#ejercicio-parcial)
- [Clase 3 - TDA Pila Dinamico y TDA Cola](#clase-3---tda-pila-dinamico-y-tda-cola)
  - [TDA Pila Dinamico](#tda-pila-dinamico)
    - [Estructura](#estructura-1)
    - [Crear Pila](#crear-pila-1)
    - [Poner en Pila](#poner-en-pila-1)
    - [Pila Vacia](#pila-vacia-1)
    - [Pila Llena](#pila-llena-1)
    - [Ver Tope](#ver-tope-1)
    - [Sacar de Pila](#sacar-de-pila-1)
    - [Vaciar Pila](#vaciar-pila-1)
  - [TDA Cola](#tda-cola)

## Parciales

-   XX/XX - TP
-   XX/XX - Parcial
-   XX/XX - Recuperatorio

## Información Extra

-   **Profesores:** Federico Pezzola y Guatelli Renata
-   **Alumno:** Tiago Pujia
-   **Comisión:** 1900 [1 = Lunes, 900 = Noche]
-   **Fecha Inicio:** 31/03/2025
-   **[Apunte(este mismo)](https://github.com/Tiago-Pujia/Base-De-Datos)**

---

# Clase 1 - Repaso

-   Metodo de ordenamaniento por seleccion universal
    -   Intercambio
    -   Funciones comparación

Realizar unidad 1

# Clase 2 - Estructura de Datos - Pila

## Nodos

Problemas de la aritmeticas de punteros, vectores o TDA:

-   Se debe tener previamente una cantidad de espacio disponible
-   Puede llegar a reservarse mas de lo que se necesita
-   Si se quiere insertar un elemento en una posicion, se debe desplazar todos los elementos de adelante para insertar
-   La memoria dinamica realiza un pedido al sistema operativo (ocupando espacio y procesamiento)

La **lista simplemente enlazada**, elimina todos los problemas. Los elementos no necesariamente estan en memoria del CPU, puede estar en cualquier lado y disperzos. Cuenta con los siguientes detalles:

-   A cada elemento, se le llamara nodo, en donde cuenta con la siguiente informacion:
    -   El primer elemento tiene un espacio reservado para indicar el inicio de la lista
    -   El nodo contiene la direccion de memoria del elemento y del siguiente nodo.
    -   El ultimo elemento tiene tambien un espacio reservado para indicar que es el final de la lista.

Tiene desventajas:

-   Se tiene un puntero extra por cada elemento, por lo que consume memoria por cada uno. Por ejemplo:
    -   int -> ocupa x3
    -   estructura de 100 bytes -> ocupa el 10%

## TDA Pila - Explicación

La pila tiene un punto de entrada y uno de salido que ejercen siempre por el tipo, donde la información se pone una encima del otro. Se puede entender como una pila de platos, si queres guardar un plato lo pones arriba de todo, y si queres sacarlo, lo mismo; por lo tanto, no se recorrer. Se define un tipo de datos _t_pila_ donde sera TDA generico, donde se define una serie de funciones:

```c
int poner_en_pila(t_pila *pp, const void *el, size_t tam_el); // retorna un verdadero o falso si se pudo poner
int sacar_de_pila(t_pila *pp, const void *el, size_t tam_el);
void crear_pila(t_pila *pp); // es demasiado complicado que falle, por lo que no se evalua
int ver_tope(const t_pila *pp, void *el, size_t tam_el); // puede ser que este vacio
void vaciar_pila(t_pila *pp);
int pila_vacia(t_pila *pp);
int pila_llena(const t_pila *pp, size_t tam_el);
```

la pila puede ser estatica (vector comun) o dinamica (nodos).

## TDA Pila Estatico

Se pone los elementos de fin a inicio. Por lo que la pila comienza segun la longitud del vector y termina hasta que llegue a cero.

Un elemento puede ocupar mas de una posicion de memoria, puede ocupar hasta 3 espacios o incluso mas. Pero se debe indicar en una posicion de al lado el espacio que ocupa el respectivo elemento, este tambien ocupara para espacio en el vector y sera de 4 o 8 bytes (tamaño de int o size_t), y apartir de ahí se sabe cuantos bytes leer.

![](/imgs/clase-2/t_pila.png)

### Estructura

```c
typedef struct
{
    char vec[TAM_PILA]; // Vector que almacena los datos en forma genérica (como bytes).
    size_t tope;         // Indica la posición del próximo espacio libre (va decreciendo).
} t_pila;
```

Es una pila estática, lo que significa que su espacio está predefinido (no cambia en tiempo de ejecución). Internamente:
- Usa un vector de caracteres (vec) como espacio de almacenamiento genérico.
- Tiene una variable tope que indica el próximo espacio libre, moviéndose hacia abajo a medida que se agregan elementos (porque se trabaja desde el final hacia el principio).

Esta estructura permite guardar cualquier tipo de dato, ya que se guarda también el tamaño del dato (mediante sizeof(size_t)), justo antes del dato, como si fuera un "encabezado".

### Crear Pila

```c
void crear_pila(t_pila *pila)
{
    pila->tope = TAM_PILA; // Inicializa el tope al final del vector → pila vacía.
}
```

Esta función simplemente inicializa la pila. Coloca el tope al final del vector (es decir, la pila comienza vacía).

**¿Por qué al final?**

Porque cada vez que agregamos algo, bajamos el tope. De esta forma, vamos ocupando el vector "hacia atrás".

### Pila Vacia

```c
int pila_vacia(t_pila *pila)
{
    return pila->tope == TAM_PILA ? PILA_VACIA : EXITO;
    // Si el tope no se ha movido, entonces no hay nada en la pila.
}
```

Verifica si el tope está en su posición original (es decir, al final del vector). Si está ahí, no se ha puesto nada y por lo tanto la pila está vacía.

### Pila Llena

```c
int pila_llena(t_pila *pila, size_t tam_el)
{
    return pila->tope < tam_el + sizeof(size_t) ? PILA_LLENA : EXITO;
}
```

Esta función determina si hay espacio suficiente para insertar un nuevo dato. Para eso, revisa si el tope tiene margen para guardar:
- El dato.
- El tamaño del dato (porque también se guarda con cada elemento).

### Poner en Pila

```c
int poner_en_pila(t_pila *pila, void *el, size_t tam_el)
{
    // Verificamos si hay suficiente espacio para el elemento y su tamaño
    if(pila->tope < tam_el + sizeof(size_t))
    {
        return PILA_LLENA;
    }

    // Reservamos espacio para el dato y lo copiamos al vector
    pila->tope -= tam_el;
    memcpy(pila->vec + pila->tope, el, tam_el);

    // Reservamos espacio para guardar el tamaño y lo copiamos
    pila->tope -= sizeof(size_t);
    memcpy(pila->vec + pila->tope, &tam_el, sizeof(size_t));

    return EXITO;
}

```
Inserta un nuevo elemento en la pila, junto con su tamaño para facilitar la extracción posterior.

Aquí se agregan elementos a la pila. El proceso es:

1. Verifica si hay espacio.
2. Reduce el tope para reservar espacio para el dato.
3. Copia el contenido del elemento al vector.
4. Reduce de nuevo el tope para reservar espacio para el tamaño del dato.
5. Guarda ese tamaño en el vector.

### Ver Tope

```c
int ver_tope(t_pila *pila, void *el, size_t tam_el)
{
    size_t tam_info;

    // Si el tope está al final, la pila está vacía
    if(pila->tope == TAM_PILA)
    {
        return PILA_VACIA;
    }

    // Leemos el tamaño guardado en el tope
    memcpy(&tam_info, pila->vec + pila->tope, sizeof(size_t));

    // Copiamos el dato completo o lo que se pueda, sin modificar la pila
    memcpy(el, pila->vec + pila->tope + sizeof(size_t), tam_el > tam_info ? tam_info : tam_el);

    return EXITO;
}
```

Permite ver el último elemento ingresado sin sacarlo de la pila. ¿Cómo lo hace?

1. Lee primero el tamaño guardado (justo antes del dato).
2. Copia solo la cantidad que se pidió (si es menor que el original).
3. No modifica el tope.

### Sacar de Pila

```c
int sacar_de_pila(t_pila *pila, void *el, size_t tam_el)
{
    size_t tam_info;

    // Si el tope está al final, la pila está vacía
    if(pila->tope == TAM_PILA)
    {
        return PILA_VACIA;
    }

    // Leemos el tamaño del dato que fue guardado justo antes del dato
    memcpy(&tam_info, pila->vec + pila->tope, sizeof(size_t));

    // Avanzamos el tope para "saltar" el tamaño
    pila->tope += sizeof(size_t);

    // Copiamos el dato completo o parcial al destino
    memcpy(el, pila->vec + pila->tope, tam_el > tam_info ? tam_info : tam_el);

    // Avanzamos el tope para liberar el espacio del dato
    pila->tope += tam_info;

    return EXITO;
}
```

Esta operación extrae el dato del tope de la pila. El flujo es:
1. Verifica si la pila está vacía.
2. Lee el tamaño guardado.
3. Avanza el tope para "saltar" ese tamaño.
4. Copia el contenido del dato.
5. Avanza el tope otra vez para liberar ese espacio.

### Vaciar Pila

```c
void vaciar_pila(t_pila *pila)
{
    pila->tope = TAM_PILA;
}
```

Simplemente resetea el tope al final del vector, lo que indica que la pila está vacía.

### Ejercicio Parcial

> Una expresión está bien parentizada cuando para cada paréntesis “(“, corchete “[“ o llave ”{“ abierto, existe uno que lo cierra luego en el orden correspondiente. Implemente una función que valide si una cadena que solo puede contener los caracteres “{[(}])” está bien parentizada.
>
> Por ejemplo “{}[]()” y “{[()]}” están bien parentizadas, pero “{([])” no.
>
> Utilice el TDA pila creado en el ejercicio 1. Cree un lote de pruebas que tenga en cuenta la mayor cantidad de casos posibles.

**Resolución:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CAD 20
#define OBT_SIMB_ABIER(s) ((s) == ')' ? '(' : (s) == '}' ? '{' : '[')
#define ES_SIM_ABIER(s) ((s) == '(' || (s) == '{' || (s) == '[')

int esCadParametrizada(char *cadena)
{
    tPila pilaComp;
    char aux;

    if(strlen(cadena) == 0)
        return 0;

    crearPila(&pilaComp);

    while(*cadena)
    {
        if(ES_SIM_ABIER(*cadena))
            ponerEnPila(&pilaComp, &(*cadena), sizeof(char));

        else
        {
            if(esPilaVacia(&pilaComp))
                return 0;

            sacarPila(&pilaComp, &aux, sizeof(char));

            if(OBT_SIMB_ABIER(*cadena) != aux)
            {
                vaciarPila(&pilaComp);
                return 0;
            }
        }
        cadena++;
    }

    if(esPilaVacia(&pilaComp))
        return 1;

    vaciarPila(&pilaComp);
    return 0;
}
```

# Clase 3 - TDA Pila Dinamico y TDA Cola

## TDA Pila Dinamico

Se utiliza el sistemas de nodos.

### Estructura

```c
typedef struct sNodo // Estructura sNodo que hace referencia a tNodo
{
    void *info; // Puntero generico, guarda el elemento con malloc
    size_t tamInfo; // Tamaño en bytes de info
    struct sNodo *sig; // Puntero al siguiente nodo
} tNodo;

typedef tNodo* tPila // Crea un alias; tPila es sinonimo de tNodo*
```

el sNodo es como un alias que se pone, es necesario porque despues de ser creado se lo llama como tNodo, entonces necesita auto referenciarse.

### Crear Pila

```c
void crear_pila(tPila *pila)
{
    *pila = NULL;
}
```

Cuando se crea un puntero, este automaticamente apuntara a basura si no le asignamos nada. Por lo que, debemos hacer que apunte a la nada indicando que esta vacio o creado.

### Poner en Pila

```c
int poner_en_pila(tPila *pila, const void *el, size_t tamEl)
{
    tNodo *nue;

    // Se intenta reservar memoria para un nuevo nodo
    if(
        !(nue = (tNodo*)malloc(sizeof(tNodo))) ||      // malloc del nodo
        !(nue->info = malloc(tamEl))                   // malloc de la copia de la info
    )
    {
        // Si falla cualquiera de los malloc, se libera el nodo (si fue asignado) y se sale
        free(nue); // Es seguro hacer free(NULL) si malloc del nodo falló
        return ERROR_MALLOC;
    }

    memcpy(nue->info, el, tamEl); // Se copia el contenido que se quiere guardar en la pila
    nue->tamInfo = tamEl; // Se guarda el tamaño de los datos
    nue->sig = *pila; // El nuevo nodo apunta al anterior tope de la pila
    *pila = nue; // El nuevo nodo se convierte en el nuevo tope de la pila

    return EXITO;
}
```

Esta función lo que hace es insertar un nuevo elemento en una pila que está implementada como una lista enlazada. Primero reserva memoria para un nuevo nodo y para la información que va a guardar. Si algo falla, libera la memoria y devuelve un error.

Si todo sale bien, copia el contenido que le pasaste al espacio reservado, guarda el tamaño de ese contenido, y enlaza ese nuevo nodo al nodo que estaba antes en la cima de la pila. Finalmente, actualiza el puntero de la pila para que apunte al nuevo nodo, que ahora es el nuevo tope.

### Pila Vacia

```c
int pila_vacia(tPila *pila)
{
    return pila ? PILA_VACIA : PILA_DISPONIBLE;
}
```

### Pila Llena

```c
int pila_llena(const tPila * pila, size_t tamEl)
{
    // Se intenta reservar memoria para un nuevo nodo
    tNodo *nodo = (tNodo*)malloc(sizeof(tNodo));

    // Se intenta reservar memoria para la información que contendrá ese nodo
    void *info = malloc(tamEl);

    // Se libera inmediatamente la memoria reservada, ya que solo se quería verificar disponibilidad
    free(nodo);
    free(info);

    // Si alguna de las asignaciones falló (es decir, devolvió NULL), se considera que la pila está llena
     return nodo && info ? PILA_DISPONIBLE : PILA_LLENA;
}
```

Esta función pila_llena evalúa si hay suficiente memoria disponible para seguir agregando elementos a la pila. Lo hace intentando reservar memoria temporalmente para un nuevo nodo (tNodo) y para el espacio necesario para la información del nuevo dato (tam bytes).

### Ver Tope

```c
int ver_tope(const tPila *pila, void *el, size_t tamEl)
{
    // Verifica si la pila está vacía (no hay nodos)
    if (!*pila)
    {
        return PILA_VACIA;
    }

    // Copia la información del nodo del tope hacia 'el'
    // Solo se copian los bytes que quepan: el mínimo entre lo que hay guardado y lo que se pide copiar
    memcpy(el, (*pila)->info, tamEl > (*pila)->tamInfo ? (*pila)->tamInfo : tamEl);

    return EXITO;
}
```

### Sacar de Pila

```c
int sacar_de_pila(tPila *pila, void *el, size_t tamEl)
{
    tNodo *aux = *pila;  // Se guarda el nodo del tope de la pila en un auxiliar

    if(!aux) // Si la pila está vacía, se retorna el código de pila vacía
    {
        return PILA_VACIA;
    }

    *pila = aux->sig;    // Se actualiza el tope de la pila al siguiente nodo

    // Se copian los datos del nodo eliminado al espacio recibido por parámetro.
    // Se copia el mínimo entre el tamaño del dato guardado y el que se pide copiar.
    memcpy(el, aux->info, tamEl > aux->tamInfo ? aux->tamInfo : tamEl);

    free(aux->info);     // Se libera la memoria del dato del nodo
    free(aux);           // Se libera la memoria del nodo en sí

    return EXITO;        // Se retorna que la operación fue exitosa
}
```

1. Verifica si la pila está vacía. Si es así, no hay nada que sacar y retorna PILA_VACIA.
2. Si hay un nodo:
   1. Guarda el nodo del tope.
   2. Actualiza el tope al siguiente nodo.
   3. Copia el contenido del nodo al puntero que se pasó como argumento.
   4. Libera la memoria del nodo extraído y su contenido.
3. Devuelve EXITO si todo salió bien.

### Vaciar Pila

```c
void vaciar_pila(tPila *pila)
{
    while(*pila)                   // Mientras haya nodos en la pila (no esté vacía)
    {
        tNodo *aux = *pila;        // Se guarda el nodo actual (el tope) en una variable auxiliar

        *pila = aux->sig;          // Se avanza el tope al siguiente nodo de la pila
        free(aux->info);           // Se libera la memoria que ocupaba la información del nodo
        free(aux);                 // Se libera la memoria del nodo
    }
}
```

Va nodo por nodo desde el tope hasta el final (cuando no queda ninguno). Por cada nodo:
- Libera primero el espacio reservado para su información.
- Luego libera el nodo en sí.

El puntero a pila termina apuntando a NULL, es decir, la pila queda vacía.

## TDA Cola

Tiene un funcionamiento muy similar a Pila. Se puede comparar como una fila de personas; la primer persona que ingresa es la que salda de la fila, y si se suma otra persona ira al final de la fila y sera la ultima que saldra.

```c
typedef struct sNodo
{
    void *info;
    size_t tamEl;
    strcut sNodo *sigNodo;
} tNodo;

typedef struct
{
    tNodo *pri; // Puntero al primer nodo
    tNodo *ult; // Puntero al ultimo nodo
}  tCola;

void crearCola(tCola *pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}
```
