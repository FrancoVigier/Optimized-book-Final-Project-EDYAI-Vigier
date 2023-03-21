#include <stdlib.h>

#include "pila.h"

/**
 * pila_crear : retorna una pila vacía.
 */
Pila pila_crear() {
  return NULL;
}

/**
 * pila_destruir : destruye la pila y los datos mediante la ayuda de la funcion
 * freeFn.
 */
void pila_destruir(Pila pila, FuncionFree freeFn) {
  glist_destruir(pila, freeFn);
}
/**
 * pila_ultimo : devuelve el elemento que se encuentra al tope de la pila.
 */
void *pila_ultimo(Pila pila) {
  if (pila == NULL)
    return NULL;
  return pila->dato;
}

/**
 * pila_apilar : agrega un elemento al tope de la pila mediante la ayuda de la
 * funcion agg. Y ademas actualiza un contado de cantidad "disponible" para
 * desapilar
 */
Pila pila_apilar(Pila pila, void *dato, FuncionCopiadora agg,
                     int *disponibleDesapilar, int *capacidadMax) {
  if ((*capacidadMax) > (*disponibleDesapilar)) {
    (*disponibleDesapilar)++;
  }
  pila = glist_agregar_inicio(pila, dato, agg, NULL);
  return pila;
}
/**
 * pila_desapilar : elimina el elemento y sus datos que se encuentra al tope
 * de la pila mediante la ayuda de la funcion freeFn.
 */
Pila pila_desapilar(Pila pila, FuncionFree freeFn) {
  if (pila == NULL)
    return NULL;
  Pila nodoADesapilar = pila;
  freeFn(nodoADesapilar->dato);
  pila = pila->sig;
  free(nodoADesapilar);
  return pila;
}
