# Introducción

## Indice

- [Introducción](#introducción)
  - [Indice](#indice)
  - [Parciales](#parciales)
  - [Información Extra](#información-extra)
- [Clase 1 - Repaso](#clase-1---repaso)
- [Clase 2 - Estructura de Datos - Pila](#clase-2---estructura-de-datos---pila)
  - [Nodos](#nodos)
  - [Memoria Pila (stack)](#memoria-pila-stack)
    - [Pila con un vector estatico](#pila-con-un-vector-estatico)
    - [Ejercicio Parcial](#ejercicio-parcial)

## Parciales

- XX/XX - TP
- XX/XX - Parcial
- XX/XX - Recuperatorio

## Información Extra

- **Profesores:** Federico Pezzola y Guatelli Renata
- **Alumno:** Tiago Pujia
- **Comisión:** 1900 [1 = Lunes, 900 = Noche]
- **Fecha Inicio:** 31/03/2025
- **[Apunte(este mismo)](https://github.com/Tiago-Pujia/Base-De-Datos)**

---

# Clase 1 - Repaso

- Metodo de ordenamaniento por seleccion universal
    - Intercambio
    - Funciones comparación

Realizar unidad 1

# Clase 2 - Estructura de Datos - Pila

## Nodos

Problemas de la aritmeticas de punteros, vectores o TDA:
- Se debe tener previamente una cantidad de espacio disponible
- Puede llegar a reservarse mas de lo que se necesita
- Si se quiere insertar un elemento en una posicion, se debe desplazar todos los elementos de adelante para insertar
- La memoria dinamica realiza un pedido al sistema operativo (ocupando espacio y procesamiento)

La **lista simplemente enlazada**, elimina todos los problemas. Los elementos no necesariamente estan en memoria del CPU, puede estar en cualquier lado y disperzos. Cuenta con los siguientes detalles:
- A cada elemento, se le llamara nodo, en donde cuenta con la siguiente informacion:
    - El primer elemento tiene un espacio reservado para indicar el inicio de la lista
    - El nodo contiene la direccion de memoria del elemento y del siguiente nodo.
    - El ultimo elemento tiene tambien un espacio reservado para indicar que es el final de la lista.

Tiene desventajas:
- Se tiene un puntero extra por cada elemento, por lo que consume memoria por cada uno. Por ejemplo:
  - int -> ocupa x3
  - estructura de 100 bytes -> ocupa el 10% 

## Memoria Pila (stack)

Las variables del main va a la memoria, como al igual del resto de funciones reservan un espacio de memoria, una vez que finaliza libera de memoria. El problema viene con recursividad, que ocupa mucho espacio de memoria en stack.

La pila tiene un punto de entrada y uno de salido que ejercen siempre por el tipo, donde la información se pone una encima del otro. Se puede entender como una pila de platos, si queres guardar un plato lo pones arriba de todo, y si queres sacarlo, lo mismo; por lo tanto, no se recorrer. Se define un tipo de datos *t_pila* donde sera TDA generico, donde se define una serie de funciones:

~~~c
int poner_en_pila(t_pila *pp, const void *el, size_t tam_el); // retorna un verdadero o falso si se pudo poner
int sacar_de_pila(t_pila *pp, const void *el, size_t tam_el);
void crear_pila(t_pila *pp); // es demasiado complicado que falle, por lo que no se evalua
int ver_tope(const t_pila *pp, void *el, size_t tam_el); // puede ser que este vacio
void vaciar_pila(t_pila *pp);
int pila_vacia(t_pila *pp);
int pila_llena(const t_pila *pp, size_t tam_el);
~~~

la pila puede ser estatica (vector comun) o dinamica (nodos).

### Pila con un vector estatico

Hay 2 maneras de implementor, en ambos se crean una variable size_t para indicar hasta que posicion se encuentra la pila:
- Se pone los elementos de inicio a fin. Por lo que la pila comienza en cero y termina segun la longitud del vector
- Se pone los elementos de fin a inicio. Por lo que la pila comienza segun la longitud del vector y termina hasta que llegue a cero. (estilo que se utiliza)
Un elemento puede ocupar mas de una posicion de memoria, puede ocupar hasta 3 espacios o incluso mas. Pero se debe indicar en una posicion de al lado el espacio que ocupa el respectivo elemento, este tambien ocupara para espacio en el vector y sera de 4 o 8 bytes (tamaño de int o size_t), y apartir de ahí se sabe cuantos bytes leer.

![](/imgs/clase-2/t_pila.png)

t_pila sigue la siguiente estructura:
~~~c
typedef struct
{
    char vec[TAM_PILA];
    size_t tope;
} t_pila;
~~~

Las funciones las podemos definir como:

~~~c
#define EXITO 1;
#define PILA_LLENA -3
#define PILA_VACIA -2

void crear_pila(t_pila *pila)
{
    pila->tope = TAM_PILA;
}

void vaciar_pila(t_pila *pila)
{
    pila->tope = TAM_PILA;
}

int pila_llena(t_pila *pila, size_t tam_el)
{
    return pila->tope < tam_el + sizeof(size_t) ? PILA_LLENA : EXITO;
}

int pila_vacia(t_pila *pila)
{
    return pila->tope == TAM_PILA ? PILA_VACIA : EXITO;
}

int ver_tope(t_pila *pila, void *el, size_t tam_el)
{
    size_t tam_info;

    if(pila->tope == TAM_PILA)
    {
        return PILA_VACIA;
    }

    memcpy(&tam_info, pila->vec + pila->tope, sizeof(size_t));
    memcpy(el, pila->vec + pila->tope + sizeof(size_t), tam_el > tam_info ? tam_info : tam_el);

    return EXITO;
}

int sacar_de_pila(t_pila *pila, void *el, size_t tam_el)
{
    size_t tam_info;

    if(pila->tope == TAM_PILA)
    {
        return PILA_VACIA;
    }

    memcpy(&tam_info, pila->tope + pila->vec, sizeof(size_t));
    pila->tope += sizeof(size_t);

    memcpy(el, pila->tope + pila->vec, tam_el > tam_info ? tam_info : tam_el);
    pila->tope += tam_info;

    return EXITO;
}

int poner_en_pila(t_pila *pila, void *el, size_t tam_el)
{
    if(pila->tope < tam_el + sizeof(size_t))
    {
        return PILA_LLENA;
    }

    pila->tope -= tam_el;
    memcpy(pila->vec + pila->tope, el, tam_el);

    pila->tope -= sizeof(size_t);
    memcpy(pila->vec + pila->tope, &tam_el, sizeof(size_t));

    return EXITO;
}
~~~

### Ejercicio Parcial

