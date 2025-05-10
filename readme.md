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
- [Clase 4 - TDA Cola Estatica](#clase-4---tda-cola-estatica)
  - [Explicacion Estrategia](#explicacion-estrategia)
  - [Estructura](#estructura-2)
  - [Crear cola](#crear-cola)
  - [Poner en Cola](#poner-en-cola)
- [Clase 5 - TDA Lista](#clase-5---tda-lista)
  - [Explicación Problema](#explicación-problema)
  - [Estrategia Problema](#estrategia-problema)
  - [Estructura](#estructura-3)
  - [Crear Lista](#crear-lista)
  - [Esta Vacio?](#esta-vacio)
  - [Esta Lleno?](#esta-lleno)
  - [Vaciar Lista](#vaciar-lista)
  - [Operaciones al Principio](#operaciones-al-principio)
    - [Insertar Nodo Al Principio](#insertar-nodo-al-principio)
    - [Ver Nodo Del Principio](#ver-nodo-del-principio)
    - [Sacar Nodo Del Principio](#sacar-nodo-del-principio)
  - [Desplazamiento en TDA](#desplazamiento-en-tda)
  - [Operaciones al Final](#operaciones-al-final)
    - [Insertar Nodo Al Final](#insertar-nodo-al-final)
    - [Ver Nodo Del Final](#ver-nodo-del-final)
    - [Saca Nodo Del Final](#saca-nodo-del-final)
  - [Operaciones en Posiciones Determinadas](#operaciones-en-posiciones-determinadas)
    - [Insertar Nodo en Posiciones Determinadas](#insertar-nodo-en-posiciones-determinadas)
    - [Ver Nodo en Posiciones Determinadas](#ver-nodo-en-posiciones-determinadas)
    - [Sacar Nodo en Posiciones Determinadas](#sacar-nodo-en-posiciones-determinadas)
  - [Recorrer](#recorrer)
- [Clase 6 -](#clase-6--)

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

-   Usa un vector de caracteres (vec) como espacio de almacenamiento genérico.
-   Tiene una variable tope que indica el próximo espacio libre, moviéndose hacia abajo a medida que se agregan elementos (porque se trabaja desde el final hacia el principio).

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

-   El dato.
-   El tamaño del dato (porque también se guarda con cada elemento).

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

-   Libera primero el espacio reservado para su información.
-   Luego libera el nodo en sí.

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

# Clase 4 - TDA Cola Estatica

## Explicacion Estrategia

Se hace uso de vectores. Se utiliza 2 variables topes:

-   \*pri -> primero
-   \*ult -> ultimo
    Al igual que TDA Pila, se debe especificar en un espacio, el tamaño que ocupa el elemento.

Un vector a medida que pasa el tiempo, va a tener espacios libres en el primero. Y puede que no se puedan insertas datos adelante pero hay espacio libre, por lo que un elemento va a tener la mitad ahi adelante, y la otra mitad atras.

No es como TDA Pila Estatico, puede tener un principio y un fin aleatorio en el vector, no necesariamente en el principio o fin del mismo, porque los datos giran en circulos.

## Estructura

```c
#define TAM_COLA 100

typedef struct
{
    char info[TAM_COLA];
    size_t *pri;
    size_t *ult;
    size_t tamDisponible;
} tCola;
```

## Crear cola

```c
void crearCola(tCola *cola)
{
    cola->tamDisponible = cola->pri = cola->ult = TAM_COLA;
}
```

Se elige el fin simplemente por la costumbre agarrada de TDA Pila Estatica

## Poner en Cola

```c
int ponerEnCola(tCola *cola, void *el, size_t tamEl)
{
    int ini, fin;

    // Comprobamos si hay espacio disponible
    if(cola->tamDisponible < sizeof(tamEl) + tamEl)
    {
        return COLA_LLENA;
    }

    if((ini = MIN(TAM_COLA - cola->ult, sizeof(tamEl))) > 0)
    {
        memcpy(cola->info + cola->ult, &tamEl, ini);
    }

    if((fin = sizeof(tamEl) - ini) > 0)
    {
        memcpy(cola->info,(char*)(&tamEl) + ini, fin);
    }

    cola->ult = fin ? fin : cola->ult + ini;

    if(ini = MIN(TAM_COLA - cola->ult, tamEl) > 0)
    {
        memcpy(cola->info + cola>ult, ,ini);
    }

    return EXITO;
}
```

Vamos a crear una variable para marcar el principio del dato `el` y otra variable para el fin.

# Clase 5 - TDA Lista

## Explicación Problema

Una lista es una sucesión de nodos. Se tiene una estructura donde apunta al primer nodo, estos se comenzaran a apuntar como en TDA Pila-

## Estrategia Problema

Se tiene un TDA Lista Estatico que es el TDA Base ya visto en Topicos de Programación, y el Dinamico que veremos ahora.

![](/imgs/clase-5/tda%20lista.png)

Se puede insertar:

-   Principio
-   Final
-   Ordenado
-   Posición Particular

Se puede sacar de:

-   Principio
-   Final
-   Posición Particular

## Estructura

```c
typedef struct sNodo
{
    void *info;         // Puntero a la información del nodo (guardada con malloc)
    size_t tamInfo;     // Tamaño en bytes de la información
    struct sNodo *sig;  // Puntero al siguiente nodo
} tNodo;

typedef tNodo* tLista;
```

El sNodo es como un alias que se pone (sNodo = tNodo), es necesario porque despues de ser creado, recien ahi se lo llama como tNodo, entonces esto es necesario para poder auto-referenciarse con el campo \*_sig_. El typedef es otro sinonimo que se le pone para tLista.

## Crear Lista

Mismo metodo que el resto, comienza a apuntar a null.

```c
void crearLista(tLista *lista)
{
    *lista = NULL;
}
```

Cuando se crea un puntero, este apuntara a basura si no le asignamos nada. Por lo que, debemos hacer que apunte a la nada (NULL) indicando que esta vacio o listo para usarse.

## Esta Vacio?

Como se utiliza un sistema de nodos, se calcula la disponibilidad de la misma
manera que Pila y Cola Dinamica.

```c
void listaVacia(tLista *lista)
{
    return *lista ? LISTA_DISPONIBLE : LISTA_VACIA;
}
```

Si el puntero \*lista no es NULL, significa que hay elementos, entonces devuelve LISTA_DISPONIBLE. Si \*lista es NULL, la LISTA esta vacia y devuelve LISTA_VACIA.

## Esta Lleno?

Como se utiliza un sistema de nodos, se calcula la disponibilidad de la misma
manera que Pila y Cola Dinamica

```c
int listaLlena(const tLista *lista, size_t tamInfo)
{
    // Se intenta reservar memoria para un nuevo nodo
    tNodo *nodo = (tNodo*)malloc(sizeof(tNodo));
    // Se intenta reservar memoria para la informaciÛn que contendr· ese nodo
    void *info = malloc(tamInfo);
    // Se libera inmediatamente la memoria reservada, ya que solo se querÌa verificar disponibilidad
    free(nodo);
    free(info);
    // Si alguna de las asignaciones fallÛ (es decir, devolviÛ NULL), se considera que la lista esta llenar
    return nodo && info ? LISTA_DISPONIBLE : LISTA_LLENA;
}
```

Esta función listaLlena evalúa si hay suficiente memoria disponible para seguir agregando elementos a la lista. Lo hace intentando reservar memoria temporalmente para un nuevo nodo (tNodo) y para el espacio necesario para la información del nuevo dato (tam bytes).

## Vaciar Lista

Como es una lista de nodos secuenciales, se utiliza el mismo metodo que TDA Cola y Pila

```c
void vaciarLista(tPila *lista)
{
    while(*lista) // Mientras haya nodos en la pila (no estÈ vacÌa)
    {
        tNodo *aux = *lista; // Se guarda el nodo tope en una auxiliar
        *lista = aux->sig;   // Se avanza el tope al siguiente nodo
        free(aux->info);    // Se libera la memoria de la informaciÛn
        free(aux);          // Se libera la memoria del nodo
    }
}
```

Va nodo por nodo desde el tope hasta el final (cuando no queda ninguno). Por cada nodo se libera la informacion que guarda y luego el nodo en si. El puntero a pila termina apuntando a NULL, es decir, la pila queda vacia.

## Operaciones al Principio

Las operaciones al principio sigue practicamente el mismo mecanismo ya visto en TDA Pila. No cambia nada mas que los nombres.

### Insertar Nodo Al Principio

```c
int insertarPrincipioLista(tLista *lista, void *info, size_t tamInfo)
{
    tNodo *nodo;

    // Reservamos memoria para el nodo
    if(!(nodo  = (tNodo*)malloc(sizeof(tNodo)))) // Si falla el malloc del nodo
    {
        return ERROR_MALLOC;
    }

    // Reservamos memoria para la información
    if(!(nodo->info = malloc(tamInfo))) // Si falla el malloc de la información
    {
        free(nodo); // Liberamos el nodo
        return ERROR_MALLOC;
    }

    memcpy(nodo->info, info, tamInfo); // Copiamos la información al nuevo nodo
    nodo->tamInfo = tamInfo;           // Guardamos el tamaño de la información
    nodo->sig = *lista; // El nuevo nodo apunta al que antes era el primero

    *lista = nodo; // Ahora el nuevo nodo pasa a ser el primero

    return EXITO; // Todo salió bien
}
```

Esta función lo que hace es insertar un nuevo elemento en una lista. Primero reserva memoria para un nuevo nodo y para la información que va a guardar. Si algo falla, libera la memoria y devuelve un error.

Si todo sale bien, copia el contenido de los parametros al espacio reservado del nuevo nodo, guarda el tamaño de ese contenido, y enlaza ese nuevo nodo al nodo que estaba antes en la cima de la lista. Finalmente, actualiza el puntero de la lista para que apunte al nuevo nodo, que ahora es el nuevo primer nodo.

En la siguiente pagina vamos a darle una explicación grafica.

### Ver Nodo Del Principio

```c
#define MIN(X,Y) (X) > (Y) ? (Y) : (X) // Obtiene el mínimo entre dos valores

int verPrincipioLista(tLista *lista, void *info, size_t tamInfo)
{
    // Verifica si la lista está vacía (no hay nodos)
    if (!*lista)
    {
        return PILA_VACIA;
    }

    // Copia la información del nodo del principio hacia el parametro 'info'
    memcpy(info, (*lista)->info, MIN(tamInfo, (*lista)->tamInfo));

    return EXITO;
}
```

Copiamos el contenido del principio a la dirección parámetro ‘info’.

### Sacar Nodo Del Principio

La función `sacarPrincipioLista` elimina el nodo que está en el principio de la lista y obtiene su información.

```c
#define MIN(X,Y) (X) > (Y) ? (Y) : (X) // Obtiene el mínimo entre dos valores

int sacarPrincipioLista(tLista *lista, void *info, size_t tamInfo)
{
    tNodo *aux = *lista; // Se guarda el nodo de la lista en un aux

    if(!aux) // Si la lista está vacía, se retorna el código de lista vacía
    {
        return LISTA_VACIA;
    }

    *lista = aux->sig; // Se actualiza el tope de la lista al siguiente nodo

    // Se copian los datos del nodo a eliminar al espacio recibido por parámetro.
    // Se copia el mínimo entre info tamaño del dato guardado y el que se pide copiar.
    memcpy(info, aux->info, MIN(tamInfo,aux->tamInfo));

    free(aux->info); // Se libera la memoria del dato del nodo
    free(aux); // Se libera la memoria del nodo en sí

    return EXITO;
}
```

Primero guarda ese nodo en una variable auxiliar para poder manipularlo sin perder su dirección. Luego verifica si la lista está vacía: si no hay nodos, devuelve el error LISTA_VACIA.

Si hay nodos, actualiza el principio de la lista apuntando al siguiente nodo (\*lista = aux->sig). Después, copia la información del nodo retirado al espacio de memoria recibido como parámetro. Para no copiar de más, usa la macro MIN(X,Y) y copia solo lo que entre: el tamaño guardado o el tamaño que el usuario pidió, el menor de los dos.

Finalmente libera la memoria reservada tanto para la información (aux->info) como para el nodo en sí (aux).

En la siguiente página vamos a darle una explicación grafica.

## Desplazamiento en TDA

Las operaciones al final o en posiciones particulares, siguen casi lo mismo que las operaciones al principio anteriormente vistas. La diferencia, es que nos vamos a dirigir hasta la posicion que deseemos, por lo que debemos agregar 2 lineas más para movernos, el resto del codigo, es mas de lo mismo. Lo unico que cambia en cada operacion (insertar, ver, sacar), es lo siguiente:

```c
while(*lista)
    lista = &(*lista)->sig;
```

o su otra versión con uso distinto:

```c
while((*lista)->sig)
    lista = &(*lista)->sig;
```

Ante esta situación podemos tomar 2 decisiones:

-   Entender a fondo qué hace este código.
-   Memorizarlo y reutilizarlo (también válido).

-   **Explicación `&(*lista)->sig;`**

![](</imgs/clase-5/&(lista)-sig.jpg>)

La expresión `&(*lista)->sig` o escrita con paréntesis completos `&( (*lista)->sig )`, obtiene la dirección de memoria del campo sig del nodo al que apunta \*lista. Para que quede más claro vamos a explicarlo paso a paso:

1. `lista` es un puntero a puntero: tNodo \*\*lista.
2. `*lista` es el nodo actual: tNodo\*.
3. `(*lista)->sig` es el valor del campo puntero `sig` de ese nodo (es decir, a dónde apunta).
4. `&(*lista)->sig` es la dirección de ese campo `sig`, que vive dentro del nodo actual.

-   **Explicación Bucle 1: Posicionarnos en el campo sig del ultimo nodo**

Recorre la lista enlazada por medio de los campos `sig` hasta llegar al ultimo nodo, que se indica estando el campo sig como vacio. En este punto, al estar el campo vacio, es la posición ideal para crear un nuevo nodo (por ejemplo) y conectar el campo al que nos desplazamos con el nuevo nodo. Se puede hacer algo tan simple como: `*lista = nuevoNodo;`

Por lo que, lista deja de ser un puntero que apunta al primer nodo, para pasar a ser un puntero posicionado en la dirección del campo `sig` del ultimo nodo. Que, como es el ultimo, tiene contenido nulo.

-   **Explicación Bucle 2: Posicionarnos en el campo sig del ante ultimo nodo**

Recorrer la lista enlazada por medio de los campos `sig` hasta llegar al ante ultimo nodo, que se indica estando nulo el campo `sig` del siguiente nodo. En este punto, nos encontramos en una dirección que apunta al ultimo nodo, por lo que es la situación ideal como para eliminar el ultimo nodo (por ejemplo).

Por lo que, lista deja de ser un puntero que apunta al primer nodo, para pasar a ser un puntero posicionado en la dirección del campo `sig` del ante ultimo nodo.

## Operaciones al Final

Como ya se nombro anteriormente, las operaciones al final son lo mismo que las operaciones al principio, con la diferencia que debemos desplazarnos al final de la lista para realizarlo.

### Insertar Nodo Al Final

Crea un nuevo nodo, lo llena con la información que le damos, y lo engancha al final de la cola, actualizando las referencias necesarias para que la cola siga funcionando correctamente.

```c
int insertarFinalLista(tLista *lista, void *info, size_t tamInfo)
{
    tNodo *nodo;

    // Reservamos memoria para el nuevo nodo
    if(!(nodo = (tNodo*)malloc(sizeof(tNodo))))
    {
        return ERROR_MALLOC;
    }

    // Reservamos memoria para la información
    if(!(nodo->info = malloc(tamInfo)))
    {
        free(nodo);
        return ERROR_MALLOC;
    }

    memcpy(nodo->info, info, tamInfo); // Copiamos la información al nuevo nodo
    nodo->tamInfo = tamInfo;           // Guardamos el tamaño de la información
    nodo->sig = NULL;                  // El nuevo nodo no apunta a nadie (es el último)

    // Avanzamos hasta posicionarnos en el campo sig del ultimo nodo
    while(*lista)
    {
        lista = &(*lista)->sig;
    }
    // Ya estamos en el campo `sig` del último nodo (que es NULL),

    *lista = nodo; // El puntero a NULL ahora apunta al nuevo nodo

    return EXITO;
}
```

Esta función lo que hace es insertar un nuevo elemento al final que está implementada como una lista enlazada. Primero reserva memoria para un nuevo nodo y para la información que va a guardar. Si algo falla, libera la memoria y devuelve un error.

Si todo sale bien, copia el contenido de los parámetros al espacio reservado del nuevo nodo, guarda el tamaño de ese contenido, y se deja el puntero \*sig como NULL porque ahora este es el último de la lista.

Finalmente, nos desplazamos al final de la lista para posicionarnos en el campo sig del ultimo nodo, y actualizar este puntero para apuntar hacia el nuevo nodo creado que es ahora el ultimo.

### Ver Nodo Del Final

La función verUltimoLista copia el contenido del ultimo nodoa la dirección `info` dada por parametro

```c
#define MIN(X,Y) (X) > (Y) ? (Y) : (X) // Obtiene el mínimo entre dos valores

int verUltimoLista(tLista *lista, void *info, size_t tamInfo)
{
    // Verifica si la lista está vacía (no hay nodos)
    if(!*lista)
    {
        return LISTA_VACIA;
    }

    // Nos desplazamos hasta apuntar al ultimo nodo
    while((*lista)->sig)
    {
        lista = &(*lista)->sig;
    }

    // Copia la información del ultimo nodo hacia 'info'
    memcpy(info, (*lista)->info, MIN(tamInfo, (*lista)->tamInfo));

    return EXITO;
}
```

### Saca Nodo Del Final

La función sacarUltimoLista copia el contenido que se encuentra en el ultimo nodo al parametro info, para luego eliminar el nodo.

~~~c
#define MIN(X,Y) (X) > (Y) ? (Y) : (X) // Obtiene el mínimo entre dos valores

int sacarUltimoLista(tLista *lista, void *info, size_t tamInfo)
{
    if(!*lista) // Si la lista está vacía, se retorna el código de lista vacía
    {
        return LISTA_VACIA;
    }

    // Nos desplazamos hasta apuntar al ultimo nodo
    while( (*lista)->sig )
    {
        lista = &(*lista)->sig;
    }

    // Copiamos el contenido del ultimo nodo al parametro 'info'
    memcpy(info, (*lista)->info, MIN(tamInfo, (*lista)->tamInfo) );

    // Eliminamos el ultimo nodo
    free((*lista)->info); // Liberamos el contenido
    free(*lista); // Liberamos el nodo
    *lista = NULL; // El puntero sig del actual ultimo nodo, apunta a NULL

    return EXITO;
}
~~~

## Operaciones en Posiciones Determinadas

Se realizan operaciones en una posición determinada, tiene un actuar similar a un vector estatico. Nosotros decidimos si queremos que comienze a contar desde 0 o 1, esto depende del programador. No obstante, en el parcial se indicara si se quiere que comienze a leer desde alguno de esos 2 numeros. Por mi parte, como costumbre a los vectores, comenzare a contar desde cero.

### Insertar Nodo en Posiciones Determinadas

Insertamos un nodo en una posición determinada

El codigo correcto, no deberia ser el siguiente:

~~~c
int insertarPosLista(tLista *lista, void *info, size_t tamInfo, size_t pos)
{
    tNodo *nodo;

    // Nos desplazamos hasta la posición deseada o hasta el final de la lista
    while(*lista && pos)
    {
        lista = &(*lista)->sig; // Avanzamos al siguiente nodo
        pos--;                  // Reducimos la posición restante
    }

    // Si pos es diferente de 0, quiere decir que no recorrió todo
    if (pos)
    {
        return POSICION_INVALIDA;
    }

    // Reservamos memoria para el nuevo nodo
    if(!(nodo = (tNodo*)malloc(sizeof(tNodo)))) // Si falla la reserva del nodo
    {
        return ERROR_MALLOC;
    }

    // Reservamos memoria para la información del nodo
    if(!(nodo->info = malloc(tamInfo))) // Si falla la reserva de la info
    {
        free(nodo);
        return ERROR_MALLOC;
    }

    // Copiamos la información recibida al nodo recién creado
    memcpy(nodo->info, info, tamInfo); // Se copia la info dentro del nodo
    nodo->tamInfo = tamInfo;           // Se guarda el tamaño de la información

    // Insertamos el nuevo nodo en la posición actual
    nodo->sig = *lista; // El nuevo nodo apunta al nodo actual (el que estaba en esa posición)
    *lista = nodo;      // El puntero actual ahora apunta al nuevo nodo

    return EXITO; // Operación exitosa
}
~~~

Creamos e insertamos los datos a un nodo como ya se conoce. Luego, nos desplazamos en la posición queredia. El nuevo 

### Ver Nodo en Posiciones Determinadas

~~~c
#define MIN(X,Y) (X) > (Y) ? (Y) : (X) // Obtiene el mínimo entre dos valores

int verPosLista(tLista *lista, void *info, size_t tamInfo, size_t pos)
{
    // Avanzamos hasta la posición deseada
    while (*lista && pos)
    {
        lista = &(*lista)->sig;
        pos--;
    }

    // Si llegamos al final antes de alcanzar la posición, la posición no existe
    if (!*lista)
    {
        return POSICION_INVALIDA;
    }

    // Copiamos la información del nodo encontrado al buffer recibido
    memcpy(info, (*lista)->info, MIN(tamInfo, (*lista)->tamInfo));

    return EXITO;
}
~~~

### Sacar Nodo en Posiciones Determinadas

## Recorrer

~~~c
void mapLista(tLista *lista, void accion(void*,void*), void *param)
{
    while(*lista)
    {
        accion((*lista)->info, param);
        lista = &(*lista)->sig;
    }
}
~~~

Recorrido generico con los conocimientos aplicados hasta ahora. Lo unico extra es `param`, esta función

Ejemplo:

Se tiene una lista con los alumnos, y se los quiere escribir en un archivo.

~~~c
struct typedef 
{
    char *alumno;
    unsigned short int edad;
} tAlumno;

void aluTxt(void *info, void *param) // En este caso, param recibe el archivo *arch
{
    tAlumno *alumno = (alumno*)info;
    fwrite();
}

int main()
{
    tLista alumnos;
    FILE *arch;

    if(fopen("alumnos.txt","wb"))
    {
        return ERROR_ARCH;
    }

    crearLista(&lista);

    /*
    se ingresan los alumnos...
    */

    mapLista(&lista, aluTxt, arch);

    vaciarLista(&lista);

    return EXITO;
}
~~~

---

# Clase 6 - 