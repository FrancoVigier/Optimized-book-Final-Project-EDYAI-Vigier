#ifndef MS_H_INCLUDED
#define MS_H_INCLUDED
#include "../../Estructuras-Generales/DList/LSE.h"
#include <stdlib.h>

/**
* Unimos dos listas por referencia, usando una funcion
* comparadora
*/GList merge(GList izq, GList der, FuncionComparadora comp);

/**
* Algoritmo recursivo Merge-Sort
*/GList merge_sort(GList lista, FuncionComparadora comp);

#endif                          // MS_H_INCLUDED
