#include <stdlib.h>
#include <assert.h>

#include "LSE.h"

/**
 * glist_crear : retorna una lista simplemente enlazada vacia.
 */
GList glist_crear() {
  return NULL;
}

/**
 * glist_destruir : destruye los elementos de la lista con posibilidad
 * de destruir el nodo
 */
void glist_destruir(GList lista, FuncionFree freeFn) {
  GNodo * nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    if (freeFn != NULL)
      freeFn(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
}
/**
 * glist_agregar_inicio : agrega un elemento al inicio de la lista mediante la
 * ayuda de la función agg.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopiadora agg, FuncionComparadora comp) {
  if(comp!=NULL){}
  GNodo * nuevoNodo = malloc(sizeof(GNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = agg(dato);
  nuevoNodo->sig = lista;
  nuevoNodo->prev = NULL;
  if (lista != NULL)
    lista->prev = nuevoNodo;
  return nuevoNodo;
}

/**
 * glist_recorrer : recorre una lista e imprime mediante la ayuda de la funcion
 * visit.
 */
void glist_recorrer(GList lista, FuncionVisitante visit) {
  for (GNodo * nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}
/**
 * glist_recorrer_doble : recorre una lista y aplica una funcion de 2 argumentos
 * visit.
 */void glist_recorrer_doble(GList lista, FuncionVisitanteDoble visit,
                             void *dato) {
  for (GNodo * nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(dato, nodo->dato);
}

/**
* glist_recorrer_archivo: nos permite guardar data de una LDE a un archivo
*
*/void glist_recorrer_archivo(GList lista, FuncionVisitanteArchivo visit,
                                 FILE * archivo) {
  for (GNodo * nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato, archivo);
}

/**
 * glist_buscar : retorna una lista comenzando con el elemento si este se
 * encuentra en la lista dada como argumento o retorna NULL si no se encuentra
 * mediante la ayuda de la función comp.
 */
GList glist_buscar(GList lista, void *data, FuncionComparadora comp) {
  for (GNodo * nodo = lista; nodo != NULL; nodo = nodo->sig) {
    if (comp(nodo->dato, data) == 0)
      return nodo;
  }
  return NULL;
}
/**
 * glist_buscar_memoria: retorna la dirección de memoria del elemento si este se
 * encuentra en la lista dada como argumento o retorna NULL si no se encuentra
 * mediante la ayuda de la función comp.
 */void **glist_buscar_memoria(GList lista, void *data,
                                   FuncionComparadora comp) {
  for (GNodo * nodo = lista; nodo != NULL; nodo = nodo->sig) {
    if (comp(nodo->dato, data) == 0)
      return &nodo->dato;
  }
  return NULL;
}

/**
 * glist_eliminar_nodo: elimina un dato de la lista si se encuentra en ella, si
 * la operacion es exitosa modifica una bandera.
 */GList glist_eliminar_nodo(GList lista, void *dato, FuncionComparadora comp,
                             FuncionFree freear, int *bandera) {
  if (lista == NULL)
    return NULL;
  GNodo * nodo = lista;
  GNodo * penultimo = NULL;
  if (comp(lista->dato, dato) == 0) {
    freear(lista->dato);
    lista = lista->sig;
    free(nodo);
    (*bandera) = 1;
    return lista;
  }
  while (nodo != NULL && comp(nodo->dato, dato) != 0) {
    penultimo = nodo;
    nodo = nodo->sig;
  }
  if (nodo != NULL) {
    if (penultimo != NULL) {
      penultimo->sig = nodo->sig;
    }
    freear(nodo->dato);
    free(nodo);
    (*bandera) = 1;
    return lista;
  }
  return lista;
}

/**
* glist_arreglar: funcion auxiliar de glist_copiar que
* fixea los punteros en una LDE
*/
void glist_arreglar(GList nodo){
if(nodo->prev != NULL){
    nodo->prev->sig = nodo->sig;
}
if(nodo->sig != NULL){
    nodo->sig->prev = nodo->prev;
}
free(nodo);
}
/**
* glist_agregar_final: funcion auxiliar de glist_copiar que
* agrega al final de una LDE un nodo con malloc
*/
GList glist_agregar_final(GList final){
  final->sig = malloc(sizeof(GNodo));
  final->sig->sig = NULL;
  final->sig->prev = final;
  return final->sig;

}

/**
* glist_copiar: funcion que copia una lista.
*/
GList glist_copiar(GList inicioA, int iod){
  if(inicioA==NULL)
    return NULL;
  GList nueva = malloc(sizeof(GNodo));
  nueva->prev = NULL;
  GList finalnueva = nueva;
  for(GList inicio = inicioA ;inicio!=NULL;){
    finalnueva->dato = inicio->dato;
    finalnueva = glist_agregar_final(finalnueva);
    if(iod == 1){
    GList aEliminar = inicio;
    inicio = inicio->sig;
    free(aEliminar);
    }
    if(iod == 0){
        inicio = inicio->sig;
    }
  }
  glist_arreglar(finalnueva);
return nueva;

}

/**
* mergehash: funcion que une dos listas LDE, en una nueva
* usando como criterio una funcion comparadora.
*/
GList mergehash(GList izq, GList der, FuncionComparadora comp,
                     int *cantidad) {
  if (izq == NULL)
    return glist_copiar(der, 0);
  if (der == NULL)
    return glist_copiar(izq, 1);
  GNodo * lista = malloc(sizeof(GNodo));
  if (comp(izq->dato, der->dato) < 0) {
    lista->dato = izq->dato;
    (*cantidad)++;
    lista->sig = mergehash(izq->sig, der, comp, cantidad);
    free(izq);
    if(lista->sig!=NULL)
        lista->sig->prev = lista;
    return lista;
  } else {
    lista->dato = der->dato;
    (*cantidad)++;
    lista->sig = mergehash(izq, der->sig, comp, cantidad);
    if(lista->sig!=NULL)
        lista->sig->prev = lista;
    return lista;
  }
}
