#ifndef _GLIST_H_
#define _GLIST_H_
#include <stdbool.h>
#include <stdio.h>
// Funciones Punteros.
/**
 * Funci�n puntero que permitira destruir los datos y asi liberar la memoria
 * pedida.
 */
typedef void (*FuncionFree)(void *);

/**
 * Funci�n puntero que permite agregar datos.
 */
typedef void *(*FuncionAgregadora)(void *, void *);

/**
 * Funci�n puntero que permite agregar datos mediante copia.
 */typedef void *(*FuncionCopiadora)(void *);

/**
 * Funci�n puntero que permite imprimir el dato.
 */
typedef void (*FuncionVisitante)(void *);

/**
 * Funci�n puntero que permite pasar el dato al archivo.
 */typedef void (*FuncionVisitanteArchivo)(void *, FILE *);

/**
 * Funci�n puntero que permite pasar el dato (void*) a la estructura **.
 */typedef void (*FuncionVisitanteDoble)(void **, void *);

/**
 * Funci�n puntero que compara dos datos.
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
 * Elimina un nodo de la lista, a trav�s de una func comparaci�n
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
* Funcion que ayudar�a en el rehasheo del �rea de rebalse de la tabla hash.
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
