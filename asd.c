
typedef struct sNodo
{
    void *info;        // Puntero a la información del nodo (guardada con malloc)
    size_t tamInfo;    // Tamaño en bytes de la información
    struct sNodo *sig; // Puntero al siguiente nodo
} tNodo;

typedef tNodo *tLista;

void crearLista(tLista *lista)
{
    *lista = NULL;
}

void listaVacia(tLista *lista)
{
    return *lista ? LISTA_DISPONIBLE : LISTA_VACIA;
}

int listaLlena(const tLista *lista, size_t tamInfo)
{
    // Se intenta reservar memoria para un nuevo nodo
    tNodo *nodo = (tNodo *)malloc(sizeof(tNodo));
    // Se intenta reservar memoria para la informaciÛn que contendr· ese nodo
    void *info = malloc(tamInfo);
    // Se libera inmediatamente la memoria reservada, ya que solo se querÌa verificar disponibilidad
    free(nodo);
    free(info);
    // Si alguna de las asignaciones fallÛ (es decir, devolviÛ NULL), se considera que la lista esta llenar
    return nodo && info ? LISTA_DISPONIBLE : LISTA_LLENA;
}

void vaciarLista(tPila *lista)
{
    while (*lista) // Mientras haya nodos en la pila (no estÈ vacÌa)
    {
        tNodo *aux = *lista; // Se guarda el nodo tope en una auxiliar
        *lista = aux->sig;   // Se avanza el tope al siguiente nodo
        free(aux->info);     // Se libera la memoria de la informaciÛn
        free(aux);           // Se libera la memoria del nodo
    }
}

int insertarPrincipioLista(tLista *lista, void *info, size_t tamInfo)
{
    tNodo *nodo;

    // Reservamos memoria para el nodo
    if (!(nodo = (tNodo *)malloc(sizeof(tNodo)))) // Si falla el malloc del nodo
    {
        return ERROR_MALLOC;
    }

    // Reservamos memoria para la información
    if (!(nodo->info = malloc(tamInfo))) // Si falla el malloc de la información
    {
        free(nodo); // Liberamos el nodo
        return ERROR_MALLOC;
    }

    memcpy(nodo->info, info, tamInfo); // Copiamos la información al nuevo nodo
    nodo->tamInfo = tamInfo;           // Guardamos el tamaño de la información
    nodo->sig = *lista;                // El nuevo nodo apunta al que antes era el primero

    *lista = nodo; // Ahora el nuevo nodo pasa a ser el primero

    return EXITO; // Todo salió bien
}

#define MIN(X, Y) (X) > (Y) ? (Y) : (X) // Obtiene el mínimo entre dos valores

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

#define MIN(X, Y) (X) > (Y) ? (Y) : (X) // Obtiene el mínimo entre dos valores

int sacarPrincipioLista(tLista *lista, void *info, size_t tamInfo)
{
    tNodo *aux = *lista; // Se guarda el nodo de la lista en un aux

    if (!aux) // Si la lista está vacía, se retorna el código de lista vacía
    {
        return LISTA_VACIA;
    }

    *lista = aux->sig; // Se actualiza el tope de la lista al siguiente nodo

    // Se copian los infos del nodo a eliminar al espacio recibido por parámetro.
    // Se copia el mínimo entre info tamaño del info guardado y el que se pide copiar.
    memcpy(info, aux->info, MIN(tamInfo, aux->tamInfo));

    free(aux->info); // Se libera la memoria del info del nodo
    free(aux);       // Se libera la memoria del nodo en sí

    return EXITO;
}

int insertarFinalLista(tLista *lista, void *info, size_t tamInfo)
{
    tNodo *nodo;

    // Reservamos memoria para el nuevo nodo
    if (!(nodo = (tNodo *)malloc(sizeof(tNodo))))
    {
        return ERROR_MALLOC;
    }

    // Reservamos memoria para la información
    if (!(nodo->info = malloc(tamInfo)))
    {
        free(nodo);
        return ERROR_MALLOC;
    }

    memcpy(nodo->info, info, tamInfo); // Copiamos la información al nuevo nodo
    nodo->tamInfo = tamInfo;           // Guardamos el tamaño de la información
    nodo->sig = NULL;                  // El nuevo nodo no apunta a nadie (es el último)

    // Avanzamos hasta posicionarnos en el campo sig del ultimo nodo
    while (*lista)
    {
        lista = &(*lista)->sig;
    }
    // Ya estamos en el campo `sig` del último nodo (que es NULL),

    *lista = nodo; // El puntero a NULL ahora apunta al nuevo nodo

    return EXITO;
}

#define MIN(X, Y) (X) > (Y) ? (Y) : (X) // Obtiene el mínimo entre dos valores

int verUltimoLista(tLista *lista, void *info, size_t tamInfo)
{
    // Verifica si la lista está vacía (no hay nodos)
    if (!*lista)
    {
        return LISTA_VACIA;
    }

    // Nos desplazamos hasta apuntar al ultimo nodo
    while ((*lista)->sig)
    {
        lista = &(*lista)->sig;
    }

    // Copia la información del ultimo nodo hacia 'info'
    memcpy(info, (*lista)->info, MIN(tamInfo, (*lista)->tamInfo));

    return EXITO;
}

#define EXITO 1
#define LISTA_VACIA -1
#define LISTA_LLENA 2
#define LISTA_DISPONIBLE 3

#define MIN(X, Y) (X) > (Y) ? (Y) : (X) // Obtiene el mínimo entre dos valores

int sacarUltimoLista(tLista *lista, void *info, size_t tamInfo)
{
    if (!*lista) // Si la lista está vacía, se retorna el código de lista vacía
    {
        return LISTA_VACIA;
    }

    // Nos desplazamos hasta apuntar al ultimo nodo
    while ((*lista)->sig)
    {
        lista = &(*lista)->sig;
    }

    // Copiamos el contenido del ultimo nodo al parametro 'info'
    memcpy(info, (*lista)->info, MIN(tamInfo, (*lista)->tamInfo));

    // Eliminamos el ultimo nodo
    free((*lista)->info); // Liberamos el contenido
    free(*lista);         // Liberamos el nodo
    *lista = NULL;        // El puntero sig del actual ultimo nodo, apunta a NULL

    return EXITO;
}

#define ERROR_MALLOC -1;

int insertarPosLista(tLista *lista, void *info, size_t tamInfo, size_t pos)
{
    tNodo *nodo;

    // Reservamos memoria para el nuevo nodo
    if (!(nodo = (tNodo *)malloc(sizeof(tNodo)))) // Si falla la reserva del nodo
    {
        return ERROR_MALLOC;
    }

    // Reservamos memoria para la información del nodo
    if (!(nodo->info = malloc(tamInfo))) // Si falla la reserva de la info
    {
        free(nodo);
        return ERROR_MALLOC;
    }

    // Copiamos la información recibida al nodo recién creado
    memcpy(nodo->info, info, tamInfo); // Se copia la info dentro del nodo
    nodo->tamInfo = tamInfo;           // Se guarda el tamaño de la información

    // Nos desplazamos hasta la posición deseada o hasta el final de la lista
    while (*lista && pos)
    {
        lista = &(*lista)->sig; // Avanzamos al siguiente nodo
        pos--;                  // Reducimos la posición restante
    }

    // Insertamos el nuevo nodo en la posición actual
    nodo->sig = *lista; // El nuevo nodo apunta al nodo actual (el que estaba en esa posición)
    *lista = nodo;      // El puntero actual ahora apunta al nuevo nodo

    return EXITO; // Operación exitosa
}

#include <stdio.h>
#define POSICION_INVALIDA 1

#define MIN(X, Y) (X) > (Y) ? (Y) : (X) // Obtiene el mínimo entre dos valores

int verPosLista(tLista *lista, void *info, size_t tamInfo, size_t pos)
{
    // Avanzamos hasta la posición deseada
    while (*lista && pos)
    {
        lista = &(*lista)->sig;
        pos--;
    }

    // Si llegamos al final antes de alcanzar la posición, la posición no existe
    if (!*lista || pos)
    {
        return POSICION_INVALIDA;
    }

    // Copiamos la información del nodo encontrado al buffer recibido
    memcpy(info, (*lista)->info, MIN(tamInfo, (*lista)->tamInfo));

    return EXITO;
}

void recorrerLista(tLista *lista, void accion(void *, size_t))
{
    while (*lista)
    {
        accion((*lista)->info, (*lista)->tamInfo);
        lista = &(*lista)->sig;
    }
}

int eliminarPosLista(tLista *lista, void *info, size_t tamInfo, size_t pos)
{
    tNodo *aux;

    // Recorremos hasta la posición deseada o hasta que la lista termine
    while (*lista && pos)
    {
        lista = &(*lista)->sig;
        pos--;
    }

    // Si no se llegó a la posición deseada, la posición no es válida
    if (!*lista || pos)
    {
        return POSICION_INVALIDA;
    }

    // Guardamos el nodo a eliminar
    aux = *lista;

    // Copiamos la información del nodo eliminado
    memcpy(info, aux->info, MIN(tamInfo, aux->tamInfo));

    // Reconectamos el nodo anterior con el siguiente
    *lista = aux->sig;

    // Liberamos la memoria del nodo
    free(aux->info);
    free(aux);

    return EXITO;
}

#define ELEMENTO_DUPLICADO 10

int insertarEnListaOrdenada(tLista *lista, void *info, size_t tamInfo, int cmp(void *, void *))
{
    tNodo *nuevoNodo;
    int resulCmp;

    // Recorremos la lista hasta encontrar la posición correcta
    while (*lista && (resulCmp = cmp(info, (*lista)->info)) > 0)
    {
        lista = &(*lista)->sig; // Avanzamos al siguiente nodo
    }

    // Si encontramos un elemento igual, no se inserta (evitamos duplicados)
    if (*lista && resulCmp == 0)
    {
        return ELEMENTO_DUPLICADO;
    }

    // Reservamos memoria para el nuevo nodo
    if (!(nuevoNodo = (tNodo*)malloc(sizeof(tNodo))))
    {
        return LISTA_LLENA;
    }

    // Reservamos memoria para la información a copiar
    if (!(nuevoNodo->info = nuevoNodo->info = malloc(tamInfo)))
    {
        free(nuevoNodo);
        return LISTA_LLENA;
    }

    // Copiamos la información al nuevo nodo
    memcpy(nuevoNodo->info, info, tamInfo);
    nuevoNodo->tamInfo = tamInfo;

    // Enlazamos el nuevo nodo en la posición encontrada
    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;

    return EXITO;
}
