#ifndef _GLIST_H_
#define _GLIST_H_
#include <stdbool.h>
#include <stdio.h>
// Funciones Punteros.
/**
 * Función puntero que permitira destruir los datos y asi liberar la memoria
 * pedida.
 */
typedef void (*FuncionFree)(void *);

/**
 * Función puntero que permite agregar datos.
 */
typedef void *(*FuncionAgregadora)(void *, void *);

/**
 * Función puntero que permite agregar datos mediante copia.
 */typedef void *(*FuncionCopiadora)(void *);

/**
 * Función puntero que permite imprimir el dato.
 */
typedef void (*FuncionVisitante)(void *);

/**
 * Función puntero que permite pasar el dato al archivo.
 */typedef void (*FuncionVisitanteArchivo)(void *, FILE *);

/**
 * Función puntero que permite pasar el dato (void*) a la estructura **.
 */typedef void (*FuncionVisitanteDoble)(void **, void *);

/**
 * Función puntero que compara dos datos.
 */
typedef int (*FuncionComparadora)(void *, void *);

// Estructura
/**
 * Estructura del nodo de una lista simplemente enlazada.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo siguiente de la lista (sig) y
 * un puntero al nodo previo de la lista(prev).
 */
typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
  struct _GNodo *prev;
} GNodo;

/// Listas que utilizo en el trabajo.
typedef GNodo *Pila;
typedef GNodo *GList;

/**
 * Retorna una lista simplemente enlazada vacia.
 */
GList glist_crear();

/**
 * Destruye la lista, con posibilidad de tambien sus
 * nodos
 */
void glist_destruir(GList, FuncionFree);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList, void *, FuncionCopiadora, FuncionComparadora);

/**
 * Recorre la lista.
 */
void glist_recorrer(GList, FuncionVisitante);

/**
 * Retorna una lista si el elemento esta en la lista pasada como argumento o no.
 */
GList glist_buscar(GList, void *, FuncionComparadora);
/**
 * Retorna una direccion de mem. si el elemento esta en la lista.
 */void **glist_buscar_memoria(GList, void *, FuncionComparadora);

/**
 * Elimina un nodo de la lista, a través de una func comparación
 */GList glist_eliminar_nodo(GList, void *, FuncionComparadora,
                           FuncionFree, int *);

/**
 * Retorna el merge de dos LDE.
 */GList mergehash(GList, GList, FuncionComparadora, int *);

/**
* Lector de archivo.
*/void glist_recorrer_archivo(GList, FuncionVisitanteArchivo,
                             FILE *);

/**
* Funcion que ayudaría en el rehasheo del área de rebalse de la tabla hash.
*/void glist_recorrer_doble(GList, FuncionVisitanteDoble, void *);

/**
* Funcion que corrige los punteros sig y prev.
*/
void glist_arreglar(GList nodo);
/**
* Funcion que agrega al final por medio de puntero.
*/
GList glist_agregar_final(GList);
/**
* Funcion que retorna la copia de una LDE.
*/
GList glist_copiar(GList, int);
#endif  /* _GLIST_H_ */
