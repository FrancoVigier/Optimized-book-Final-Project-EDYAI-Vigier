#ifndef DR_H_INCLUDED
#define DR_H_INCLUDED
#include "../../Estructuras-Generales/Pila/pila.h"
#include "../../Estructuras-Generales/Hash/hash.h"
#include "../../Estructuras-Puntuales/Encapsulador/nthnodo.h"
#include "../../Estructuras-Puntuales/Contacto/contacto.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
* Primitiva que rehace la ultima modificacion deshecha por su primitiva
* inversa
*/void rehacer_operacion(TablaHash tabla, Pila * Rehacer, int *pilaRehacerelems,
                         int *pilaCapacidad, Pila * Deshacer, int *pilaRelems);

/**
* Primitiva que deshace la ultima modificacion en la agenda, ya sea
* por accion de Agregar, Editar, Eliminar, Cargar, Rehacer
*/void deshacer_operacion(TablaHash tabla, Pila * Deshacer, int *pilanelems,
                         int *pilaCap, Pila * Rehacer, int *pilaDnelems);

#endif                          // DR_H_INCLUDED
