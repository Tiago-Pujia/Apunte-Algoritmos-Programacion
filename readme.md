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
  - [TDA Cola - Explicación](#tda-cola---explicación)
  - [TDA Cola - Dinamica](#tda-cola---dinamica)
    - [Estructura](#estructura-2)
    - [Crear Cola](#crear-cola)
    - [Poner en Cola](#poner-en-cola)
    - [Sacar de Cola](#sacar-de-cola)
    - [Ver Primero de Cola](#ver-primero-de-cola)
    - [Cola Llena](#cola-llena)
    - [Cola Vacia](#cola-vacia)
    - [Vaciar Cola](#vaciar-cola)

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
    -   info primer elemento tiene un espacio reservado para indicar info inicio de la lista
    -   info nodo contiene la direccion de memoria del elemento y del siguiente nodo.
    -   info ultimo elemento tiene tambien un espacio reservado para indicar que es info final de la lista.

Tiene desventajas:

-   Se tiene un puntero extra por cada elemento, por lo que consume memoria por cada uno. Por ejemplo:
    -   int -> ocupa x3
    -   estructura de 100 bytes -> ocupa info 10%

## TDA Pila - Explicación

La pila tiene un punto de entrada y uno de salido que ejercen siempre por info tipo, donde la información se pone una encima del otro. Se puede entender como una pila de platos, si queres guardar un plato lo pones arriba de todo, y si queres sacarlo, lo mismo; por lo tanto, no se recorrer. Se define un tipo de datos _t_pila_ donde sera TDA generico, donde se define una serie de funciones:

```c
int poner_en_pila(t_pila *pp, const void *info, size_t tamInfo); // retorna un verdadero o falso si se pudo poner
int sacar_de_pila(t_pila *pp, const void *info, size_t tamInfo);
void crear_pila(t_pila *pp); // es demasiado complicado que falle, por lo que no se evalua
int ver_tope(const t_pila *pp, void *info, size_t tamInfo); // puede ser que este vacio
void vaciar_pila(t_pila *pp);
int pila_vacia(t_pila *pp);
int pila_llena(const t_pila *pp, size_t tamInfo);
```

la pila puede ser estatica (vector comun) o dinamica (nodos).

## TDA Pila Estatico

Se pone los elementos de fin a inicio. Por lo que la pila comienza segun la longitud del vector y termina hasta que llegue a cero.

Un elemento puede ocupar mas de una posicion de memoria, puede ocupar hasta 3 espacios o incluso mas. Pero se debe indicar en una posicion de al lado info espacio que ocupa info respectivo elemento, este tambien ocupara para espacio en info vector y sera de 4 o 8 bytes (tamaño de int o size_t), y apartir de ahí se sabe cuantos bytes leer.

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
-   Tiene una variable tope que indica info próximo espacio libre, moviéndose hacia abajo a medida que se agregan elementos (porque se trabaja desde info final hacia info principio).

Esta estructura permite guardar cualquier tipo de dato, ya que se guarda también info tamaño del dato (mediante sizeof(size_t)), justo antes del dato, como si fuera un "encabezado".

### Crear Pila

```c
void crear_pila(t_pila *pila)
{
    pila->tope = TAM_PILA; // Inicializa info tope al final del vector → pila vacía.
}
```

Esta función simplemente inicializa la pila. Coloca info tope al final del vector (es decir, la pila comienza vacía).

**¿Por qué al final?**

Porque cada vez que agregamos algo, bajamos info tope. De esta forma, vamos ocupando info vector "hacia atrás".

### Pila Vacia

```c
int pila_vacia(t_pila *pila)
{
    return pila->tope == TAM_PILA ? PILA_VACIA : EXITO;
    // Si info tope no se ha movido, entonces no hay nada en la pila.
}
```

Verifica si info tope está en su posición original (es decir, al final del vector). Si está ahí, no se ha puesto nada y por lo tanto la pila está vacía.

### Pila Llena

```c
int pila_llena(t_pila *pila, size_t tamInfo)
{
    return pila->tope < tamInfo + sizeof(size_t) ? PILA_LLENA : EXITO;
}
```

Esta función determina si hay espacio suficiente para insertar un nuevo dato. Para eso, revisa si info tope tiene margen para guardar:

-   info dato.
-   info tamaño del dato (porque también se guarda con cada elemento).

### Poner en Pila

```c
int poner_en_pila(t_pila *pila, void *info, size_t tamInfo)
{
    // Verificamos si hay suficiente espacio para info elemento y su tamaño
    if(pila->tope < tamInfo + sizeof(size_t))
    {
        return PILA_LLENA;
    }

    // Reservamos espacio para info dato y lo copiamos al vector
    pila->tope -= tamInfo;
    memcpy(pila->vec + pila->tope, info, tamInfo);

    // Reservamos espacio para guardar info tamaño y lo copiamos
    pila->tope -= sizeof(size_t);
    memcpy(pila->vec + pila->tope, &tamInfo, sizeof(size_t));

    return EXITO;
}

```

Inserta un nuevo elemento en la pila, junto con su tamaño para facilitar la extracción posterior.

Aquí se agregan elementos a la pila. info proceso es:

1. Verifica si hay espacio.
2. Reduce info tope para reservar espacio para info dato.
3. Copia info contenido del elemento al vector.
4. Reduce de nuevo info tope para reservar espacio para info tamaño del dato.
5. Guarda ese tamaño en info vector.

### Ver Tope

```c
int ver_tope(t_pila *pila, void *info, size_t tamInfo)
{
    size_t tam_info;

    // Si info tope está al final, la pila está vacía
    if(pila->tope == TAM_PILA)
    {
        return PILA_VACIA;
    }

    // Leemos info tamaño guardado en info tope
    memcpy(&tam_info, pila->vec + pila->tope, sizeof(size_t));

    // Copiamos info dato completo o lo que se pueda, sin modificar la pila
    memcpy(info, pila->vec + pila->tope + sizeof(size_t), tamInfo > tam_info ? tam_info : tamInfo);

    return EXITO;
}
```

Permite ver info último elemento ingresado sin sacarlo de la pila. ¿Cómo lo hace?

1. Lee primero info tamaño guardado (justo antes del dato).
2. Copia solo la cantidad que se pidió (si es menor que info original).
3. No modifica info tope.

### Sacar de Pila

```c
int sacar_de_pila(t_pila *pila, void *info, size_t tamInfo)
{
    size_t tam_info;

    // Si info tope está al final, la pila está vacía
    if(pila->tope == TAM_PILA)
    {
        return PILA_VACIA;
    }

    // Leemos info tamaño del dato que fue guardado justo antes del dato
    memcpy(&tam_info, pila->vec + pila->tope, sizeof(size_t));

    // Avanzamos info tope para "saltar" info tamaño
    pila->tope += sizeof(size_t);

    // Copiamos info dato completo o parcial al destino
    memcpy(info, pila->vec + pila->tope, tamInfo > tam_info ? tam_info : tamInfo);

    // Avanzamos info tope para liberar info espacio del dato
    pila->tope += tam_info;

    return EXITO;
}
```

Esta operación extrae info dato del tope de la pila. info flujo es:

1. Verifica si la pila está vacía.
2. Lee info tamaño guardado.
3. Avanza info tope para "saltar" ese tamaño.
4. Copia info contenido del dato.
5. Avanza info tope otra vez para liberar ese espacio.

### Vaciar Pila

```c
void vaciar_pila(t_pila *pila)
{
    pila->tope = TAM_PILA;
}
```

Simplemente resetea info tope al final del vector, lo que indica que la pila está vacía.

### Ejercicio Parcial

> Una expresión está bien parentizada cuando para cada paréntesis “(“, corchete “[“ o llave ”{“ abierto, existe uno que lo cierra luego en info orden correspondiente. Implemente una función que valide si una cadena que solo puede contener los caracteres “{[(}])” está bien parentizada.
>
> Por ejemplo “{}[]()” y “{[()]}” están bien parentizadas, pero “{([])” no.
>
> Utilice info TDA pila creado en info ejercicio 1. Cree un lote de pruebas que tenga en cuenta la mayor cantidad de casos posibles.

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

Se utiliza info sistemas de nodos.

### Estructura

```c
typedef struct sNodo // Estructura sNodo que hace referencia a tNodo
{
    void *info; // Puntero generico, guarda info elemento con malloc
    size_t tamInfo; // Tamaño en bytes de info
    struct sNodo *sig; // Puntero al siguiente nodo
} tNodo;

typedef tNodo* tPila // Crea un alias; tPila es sinonimo de tNodo*
```

info sNodo es como un alias que se pone, es necesario porque despues de ser creado se lo llama como tNodo, entonces necesita auto referenciarse.

### Crear Pila

```c
void crear_pila(tPila *pila)
{
    *pila = NULL;
}
```

Cuando se crea un puntero, este automaticamente apuntara a basura si no le asignamos nada. Por lo que, debemos hacer que apunte a la nada indicando que esta vacio o listo para usarse.

### Poner en Pila

```c
int poner_en_pila(tPila *pila, const void *info, size_t tamInfo)
{
    tNodo *nodo;

    if(!(nodo = (tNodo*)malloc(sizeof(tNodo)))) // Reserva memoria para info nodo
    {
        return ERROR_MALLOC;
    }

    if(!(nodo->info = malloc(tamInfo))) // Reserva memoria para guardar la información
    {
        free(nodo);
        return ERROR_MALLOC;
    }

    memcpy(nodo->info, info, tamInfo); // Se copia info contenido que se quiere guardar en la pila
    nodo->tamInfo = tamInfo; // Se guarda info tamaño de los datos
    nodo->sig = *pila; // info nuevo nodo apunta al anterior tope de la pila
    *pila = nodo; // info nuevo nodo se convierte en info nuevo tope de la pila

    return EXITO;
}
```

Esta función lo que hace es insertar un nuevo elemento en una pila que está implementada como una lista enlazada. Primero reserva memoria para un nuevo nodo y para la información que va a guardar. Si algo falla, libera la memoria y devuelve un error.

Si todo sale bien, copia info contenido que le pasaste al espacio reservado, guarda info tamaño de ese contenido, y enlaza ese nuevo nodo al nodo que estaba antes en la cima de la pila. Finalmente, actualiza info puntero de la pila para que apunte al nuevo nodo, que ahora es info nuevo tope.

### Pila Vacia

```c
int pila_vacia(tPila *pila)
{
    return pila ? PILA_VACIA : PILA_DISPONIBLE;
}
```

### Pila Llena

```c
int pila_llena(const tPila * pila, size_t tamInfo)
{
    // Se intenta reservar memoria para un nuevo nodo
    tNodo *nodo = (tNodo*)malloc(sizeof(tNodo));

    // Se intenta reservar memoria para la información que contendrá ese nodo
    void *info = malloc(tamInfo);

    // Se libera inmediatamente la memoria reservada, ya que solo se quería verificar disponibilidad
    free(nodo);
    free(info);

    // Si alguna de las asignaciones falló (es decir, devolvió NULL), se considera que la pila está llena
     return nodo && info ? PILA_DISPONIBLE : PILA_LLENA;
}
```

Esta función pila_llena evalúa si hay suficiente memoria disponible para seguir agregando elementos a la pila. Lo hace intentando reservar memoria temporalmente para un nuevo nodo (tNodo) y para info espacio necesario para la información del nuevo dato (tam bytes).

### Ver Tope

```c
int ver_tope(const tPila *pila, void *info, size_t tamInfo)
{
    // Verifica si la pila está vacía (no hay nodos)
    if (!*pila)
    {
        return PILA_VACIA;
    }

    // Copia la información del nodo del tope hacia 'info'
    // Solo se copian los bytes que quepan: info mínimo entre lo que hay guardado y lo que se pide copiar
    memcpy(info, (*pila)->info, tamInfo > (*pila)->tamInfo ? (*pila)->tamInfo : tamInfo);

    return EXITO;
}
```

### Sacar de Pila

```c
int sacar_de_pila(tPila *pila, void *info, size_t tamInfo)
{
    tNodo *aux = *pila;  // Se guarda info nodo del tope de la pila en un auxiliar

    if(!aux) // Si la pila está vacía, se retorna info código de pila vacía
    {
        return PILA_VACIA;
    }

    *pila = aux->sig;    // Se actualiza info tope de la pila al siguiente nodo

    // Se copian los datos del nodo eliminado al espacio recibido por parámetro.
    // Se copia info mínimo entre info tamaño del dato guardado y info que se pide copiar.
    memcpy(info, aux->info, tamInfo > aux->tamInfo ? aux->tamInfo : tamInfo);

    free(aux->info);     // Se libera la memoria del dato del nodo
    free(aux);           // Se libera la memoria del nodo en sí

    return EXITO;        // Se retorna que la operación fue exitosa
}
```

1. Verifica si la pila está vacía. Si es así, no hay nada que sacar y retorna PILA_VACIA.
2. Si hay un nodo:
    1. Guarda info nodo del tope.
    2. Actualiza info tope al siguiente nodo.
    3. Copia info contenido del nodo al puntero que se pasó como argumento.
    4. Libera la memoria del nodo extraído y su contenido.
3. Devuelve EXITO si todo salió bien.

### Vaciar Pila

```c
void vaciar_pila(tPila *pila)
{
    while(*pila)                   // Mientras haya nodos en la pila (no esté vacía)
    {
        tNodo *aux = *pila;        // Se guarda info nodo actual (info tope) en una variable auxiliar

        *pila = aux->sig;          // Se avanza info tope al siguiente nodo de la pila
        free(aux->info);           // Se libera la memoria que ocupaba la información del nodo
        free(aux);                 // Se libera la memoria del nodo
    }
}
```

Va nodo por nodo desde info tope hasta info final (cuando no queda ninguno). Por cada nodo:

-   Libera primero info espacio reservado para su información.
-   Luego libera info nodo en sí.

info puntero a pila termina apuntando a NULL, es decir, la pila queda vacía.

## TDA Cola - Explicación

Tiene un funcionamiento muy similar a Pila. info primero que entra es info primero que sale, respeta info orden en que ingresa los elementos. Se puede comparar con una fila de personas; info primer elemento es info que sale.Si se agrega un nuevo, se envia al fondo.

La cola tiene 2 punteros, uno para info ingreso y otro para info ultimo elemento. Tiene las siguientes funciones:

```
Crear Cola(cola)
Poner en Cola (cola, info)
Ver Primero de Cola(cola, info)
Cola Llena(cola)
Cola Vacia(cola)
Vaciar Cola(cola)
```

## TDA Cola - Dinamica

### Estructura

```c
typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    strcut sNodo *sig;
} tNodo;

typedef struct
{
    tNodo *pri; // Puntero al primer nodo
    tNodo *ult; // Puntero al ultimo nodo
}  tCola;
```

Como es dinamico, se sigue utilizando info mismo sistema de nodos. Pero, se crea una nueva estructura donde contendra 2 punteros a nodos, uno con info inicio y otro con info fin.

### Crear Cola

```c
void crearCola(tCola *cola)
{
    cola->pri = NULL;
    cola->ult = NULL;
}
```

Inicializa una cola vacía. Pone los punteros pri (primero) y ult (último) en NULL, indicando que no hay ningún elemento en la cola todavía. Es como dejar la cola lista para usarse, partiendo de cero.

### Poner en Cola

```c
int poner_en_cola(tCola *cola, void *info, size_t tamInfo)
{
    tNodo *nodo;

    if(!(nodo = (tNodo*)malloc(sizeof(tNodo)))) // Reserva memoria para info nodo
    {
        return ERROR_MALLOC;
    }

    if(!(nodo->info = malloc(tamInfo))) // Reserva memoria para guardar la información
    {
        free(nodo);
        return ERROR_MALLOC;
    }

    // Copia info contenido del elemento 'info' a la memoria recién reservada
    memcpy(nodo->info, info, tamInfo);

    // Guarda info tamaño de la información
    nodo->tamInfo = tamInfo;

    // Inicializa info siguiente nodo como NULL (porque será info último en la cola)
    nodo->sig = NULL;

    // Si la cola NO está vacía, conecta info nodo nuevo al final
    if (cola->ult)
        cola->ult->sig = nodo;
    else // Si la cola está vacía, info nuevo nodo será también info primero
        cola->pri = nodo;

    // Actualiza info puntero 'ult' para que apunte al nuevo nodo
    cola->ult = nodo;

    return EXITO; // Operación exitosa
}
```

### Sacar de Cola

```c
int sacarDeCola(tCola *cola, void *info, size_t tamInfo)
{
    tNodo *aux = cola->pri; // Apunta al primer nodo de la cola

    if(!aux) // Si la cola está vacía (no hay primer nodo)
    {
        return COLA_VACIA;
    }

    cola->pri = aux->sig; // Avanza el puntero de la cola al siguiente nodo

    // Copia la información del nodo al espacio recibido
    memcpy(info, aux->info, aux->tamInfo > tamInfo ? tamInfo : aux->tamInfo);

    free(aux->info); // Libera la memoria reservada para la información del nodo
    free(aux);       // Libera la memoria del nodo

    if(!(cola->pri)) // Si después de sacar no queda más nadie en la cola
    {
        cola->ult = NULL; // El último también pasa a ser NULL
    }

    return EXITO; // Operación exitosa
}
```

Toma el primer nodo y lo guarda en una variable auxiliar. Luego, verifica si la cola no esta vacia:

1. Se mueve el primer puntero (cola->pri) al siguiente nodo (aux->sig). De esta manera, el primer elemento queda "desconectado" de la cola.
2. Se copia la información almacenada en el nodo desconectado.
3. Se libera de memoria el nodo
4. Se comprueba si la cola quedó vacía con cola->pri. Si el primero quedo vacio, entonces el puntero al ultimo tambien debe estarlo.

### Ver Primero de Cola

```c
int verFrenteCola(tCola *cola, void *info, size_t tamInfo)
{
    tNodo *nodo = cola->pri;  // Se guarda un puntero al primer nodo de la cola (frente).

    if(!nodo)  // Si el primer nodo no existe, la cola está vacía.
    {
        return COLA_VACIA;  // Devuelve que la cola está vacía.
    }

    // Copia la información del primer nodo en el espacio de memoria apuntado por 'info'.
    // Solo se copian tantos bytes como permita 'tamInfo' o como tenga el nodo, el que sea menor.
    memcpy(info, nodo->info, nodo->tamInfo > tamInfo ? tamInfo : nodo->tamInfo);

    return EXITO;  // Devuelve que la operación fue exitosa.
}
```

### Cola Llena

Sigue la misma logica que TDA Pila Dinamico

```c
int colaLlena(const tCola *cola, size_t tamInfo)
{
    // Se intenta reservar memoria para un nuevo nodo
    tNodo *nodo = (tNodo*)malloc(sizeof(tNodo));

    // Se intenta reservar memoria para la información que contendrá ese nodo
    void *info = malloc(tamInfo);

    // Se libera inmediatamente la memoria reservada, ya que solo se quería verificar disponibilidad
    free(nodo);
    free(info);

    // Si alguna de las asignaciones falló (es decir, devolvió NULL), se considera que la cola está llena
     return nodo && info ? COLA_DISPONIBLE : COLA_LLENA;
}
```

Esta función colaLlena evalúa si hay suficiente memoria disponible para seguir agregando elementos a la cola. Lo hace intentando reservar memoria temporalmente para un nuevo nodo (tNodo) y para info espacio necesario para la información del nuevo dato (tam bytes).

### Cola Vacia

```c
int colaVacia(tCola *cola)
{
    return cola->pri ? COLA_DISPONIBLE : COLA_VACIA;
}
```

Si info puntero pri (primero) no es NULL, significa que hay elementos, entonces devuelve COLA_DISPONIBLE. Si pri es NULL, la cola está vacía y devuelve COLA_VACIA.

### Vaciar Cola

```c
void vaciarCola(tCola *cola)
{
    // Mientras haya nodos en la cola (mientras info primero no sea NULL)
    while(cola->pri)
    {
        tNodo *aux = cola->pri; // Guardamos info nodo actual en un auxiliar
        cola->pri = aux->sig;   // Avanzamos info puntero de inicio (pri) al siguiente nodo
        free(aux->info);        // Liberamos la memoria reservada para la información del nodo
        free(aux);              // Liberamos la memoria del nodo en sí
    }
    // Una vez vacía la cola, también ponemos info último a NULL
    cola->ult = NULL;
}
```

Se encarga de eliminar la información de cola y liberar memoria, debe ejecutarse siempre al terminar de usar info TDA Cola Dinamico.

1. Empieza mirando si hay nodos en la cola, se comprueba viendo si info puntero al primer nodo (pri) no es NULL. Mientras siga existiendo al menos un nodo, realiza un proceso repetitivo.
2. Primero guarda info primer nodo en una variable auxiliar, para no perder la referencia a ese nodo mientras mueve info puntero. Luego actualiza info puntero pri para que apunte al siguiente nodo. Esto hace que la "cabeza" de la cola avance, y info nodo que estaba primero queda aislado.
3. Se libera la memoria reservada para la información que contenía, y luego también se libera la memoria del propio nodo.
4. Finalmente, una vez que ya no hay más nodos. Se asigna también NULL al puntero ult, que representaba info último elemento de la cola.
