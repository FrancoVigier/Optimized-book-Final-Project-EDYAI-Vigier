#ifndef AO_H_INCLUDED
#define AO_H_INCLUDED
#include "../../Estructuras-Generales/DList/LSE.h"
#include "../../Estructuras-Generales/Hash/hash.h"
#include "../../Estructuras-Puntuales/Contacto/contacto.h"
#include "../../Estructuras-Generales/Anexo/utils.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/// Funcion que busca parametricamente con AND/OR en la tabla hash
void AND_OR(TablaHash tabla, int AoO, char *nombre, char *apellido,
             char *telefono, unsigned int *edad);

/// Funcion que busca parametricamente con AND/OR en el área de rebalse
void glist_AND_OR(GList lista, int AoO, char *nombre, char *apellido,
                   char *telefono, unsigned int *edad);

/// Funcion que busca parametricamente con AND/OR si un contacto cumple
/// o no con los parametros
int comparar_parametrico_AND_OR(int AoO, void *contacto, char *nombre,
                                  char *apellido, char *telefono,
                                  unsigned int *edad);



#endif                          // AO_H_INCLUDED
