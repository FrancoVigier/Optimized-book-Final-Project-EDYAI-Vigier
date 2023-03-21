#ifndef _GPILA_H_
#define _GPILA_H_

#include "../DList/LSE.h"       // Una Pila es una GList.
    
/**
 * Retorna una pila vacia.
 */ 
    Pila pila_crear();
 
/**
 * Destruye una pila y sus datos.
 */ 
void pila_destruir(Pila, FuncionFree);
 
/**
 * Determina el elemento que se encuentra en el tope de la pila.
 */ 
void *pila_ultimo(Pila pila);
 
/**
 * Agrega un elemento a la pila.
 */ 
    Pila pila_apilar(Pila, void *, FuncionCopiadora, int *disponibleDesapilar,
                     int *capacidadMax);
 
/**
 * Elimina un elemento de la pila.
 */ 
    Pila pila_desapilar(Pila, FuncionFree);
 
#endif  /* _GPILA_H_ */
