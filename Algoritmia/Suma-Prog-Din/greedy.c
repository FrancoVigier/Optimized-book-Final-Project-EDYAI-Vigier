#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "greedy.h"
/**
* Busqueda por suma de las edades
*/ void suma_edad(TablaHash superMerge, unsigned int nelems,
                 unsigned int sumaBuscada) {
  //Creamos la matriz que representa las posibles sumas y los sucesivos conjuntos
  bool matriz[nelems + 1][sumaBuscada + 1];
  //Por criterio inicializamos todo en False( en especial la primera fila)
  for (unsigned int i = 0; i < nelems + 1; i++)
    for (unsigned int j = 0; j < sumaBuscada + 1; j++)
      matriz[i][j] = false;
  //Primera columna True, todo conjunto da el 0 como posible suma
  for (unsigned int i = 0; i < nelems + 1; i++)
    matriz[i][0] = true;
  //Contador del conjunto que estamos analizando
  unsigned int bucket = 0;  GList fil = superMerge->elems[bucket].dato;
  Contacto resultadoArray[nelems];
  for (unsigned int fila = 1; fila < nelems + 1;) {
    if(fil != NULL){
  //Vamos en profundidad en nuestro i-esimo conjunto
      for(;fil!=NULL;fil=fil->sig, fila++){
        resultadoArray[fila - 1] = fil->dato;
  //Para cada valor de nuestro conjunto i-esimo analizo las posible sumas nuevas
  //con respecto al anterior
        for (unsigned int columna = 1; columna < sumaBuscada + 1; columna++) {
  //Toda columna que tenga indice menor al elemento diferencial, es igual a la
  //fila anterior porque el elem diferencia no influye en valores menores a él
  //porque no resta. A lo sumo tiene incluencia en la columna [elem diferencial +i]
  //con i = 0, 1, 2, ...
          if (columna < ((Contacto) fil->dato)->edad) {
            matriz[fila][columna] = matriz[fila - 1][columna];
          } else {
  //Toda fila tiene los valores TRUE de la anterior
            if (matriz[fila - 1][columna]) {
              matriz[fila][columna] = matriz[fila - 1][columna];
            } else {
              if (fil != NULL) {
  //Si una celda [fila-1] es falsa entonces mi valor es que traiga en esa fila
  //menos el elemento diferencial
                matriz[fila][columna] =
                matriz[fila - 1][columna - ((Contacto) fil->dato)->edad];
              }
            }
          }
        }
      }
    }
  //Cambio de conjunto
    if (bucket < superMerge->capacidad - 1) {
      bucket++;
      fil = superMerge->elems[bucket].dato;
    }
  }
  //Como los valores fila a fila se arrastran, si en ultimo
  //elemento no es TRUE no hay combinacion
  if (!matriz[nelems][sumaBuscada]) {
    printf("No se encontro nada\n");
    return;
  }
  printf("Hay una combinacion\n");
  //Si hay una combinacion debo iniciar una busqueda por la matriz
  //buscando el minimo conjunto que tenga un TRUE en una fila y un
  //FALSE en la fila anterior, asi sabemos que el elemento diferencial
  //entre esas 2 filas es parte del resultado.
  int col = sumaBuscada;
  int fils = nelems;
  while (col > 0 || fils > 0) {
    if (matriz[fils][col] == matriz[fils - 1][col])
      fils--;
    else {
      contacto_imprimir(resultadoArray[fils - 1]);
      col = col - resultadoArray[fils - 1]->edad;
    }
  }
}
