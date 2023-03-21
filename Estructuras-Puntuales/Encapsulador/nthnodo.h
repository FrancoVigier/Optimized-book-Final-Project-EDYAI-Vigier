#ifndef NTHNODO_H_INCLUDED
#define NTHNODO_H_INCLUDED

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _NodoNTipo {
  int tipoDeDato;              // Bandera para castear
  // 1 = agregar
  // 2 = editar
  // 3 = eliminar
  char *nombre;
  char *apellido;
  char *telViejo;
  char *telNuevo;
  int edadVieja;
  int edadNueva;
} NTNodo;

/// Creamos un encapsulador
                     char *, int , int);

/// Copiamos un encapsulador

/// Liberamos un encapsulador

#endif                          // NTHNODO_H_INCLUDED