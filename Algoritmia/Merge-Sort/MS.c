#include "MS.h"

/**
* Funcion que une dos listas por referencia, bajo la comparacion
* de una funcion argumento
*/ GList merge(GList izq, GList der, FuncionComparadora comp) {
  if (izq == NULL)
    return der;
  if (der == NULL)
    return izq;
  if (comp(izq->dato, der->dato) < 0) {
    izq->sig = merge(izq->sig, der, comp);
    izq->sig->prev = izq;
    return izq;
  } else {
    der->sig = merge(izq, der->sig, comp);
    der->sig->prev = der;
    return der;
  }
}

/**
* Ordenamiento M-S: primero spliteamos la lista, llamamos
* recursivamente y unimos bajo el criterio de una foo comparadora
*/GList merge_sort(GList lista, FuncionComparadora comp) {
  GList izq = lista, der = lista;
  if (lista == NULL || lista->sig == NULL)
    return lista;
  //Dividimos
  for (; lista != NULL && lista->sig != NULL; lista = lista->sig->sig)
    der = der->sig;
  der->prev->sig = NULL;
  der->prev = NULL;
  //Volvemos a "Dividir"
  izq = merge_sort(izq, comp);
  der = merge_sort(der, comp);
  //Unimos en orden
  return merge(izq, der, comp);
}


