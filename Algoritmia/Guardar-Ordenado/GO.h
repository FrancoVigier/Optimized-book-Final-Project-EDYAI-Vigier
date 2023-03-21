#ifndef GO_H_INCLUDED
#define GO_H_INCLUDED

#include "../../Estructuras-Generales/DList/LSE.h"
#include "../Merge-Sort/MS.h"
#include "../../Estructuras-Generales/Hash/hash.h"
#include "../../Estructuras-Puntuales/Contacto/contacto.h"
#include "../../Core/Procesamiento/procesamiento.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
* ordenar_parametro: Ordenamos la tabla hash, por medio de un parametro
* y la volcamos al archivo
*/void ordenar_parametro(TablaHash tabla, char *parametro, FILE * archivo);

/**
* ordenar_campo: Ordena todas las areas de rebalse por un parametro
* y las une por el mismo. Vuelca todo al archivo
*/void ordenar_campo(TablaHash tabla, int orden, FuncionComparadora porApellido,
                    FuncionComparadora porNombre,
                    FuncionComparadora porEdad,
                    FuncionComparadora porTelefono, FILE * archivo);

/**
* aplicar_orden: Ordena un area de rebalse por un parametro
*/
GList aplicar_orden(GList lista, int orden, FuncionComparadora porApellido,
                     FuncionComparadora porNombre,
                     FuncionComparadora porEdad,
                     FuncionComparadora porTelefono);

/**
* merge_bucket: Mergea en una nueva lista, 2 areas de rebalse por un parametro
*/GList merge_bucket(GList acumulado, GList rebalse, int orden,
                    FuncionComparadora porApellido,
                    FuncionComparadora porNombre,
                    FuncionComparadora porEdad,
                    FuncionComparadora porTelefono, int *cantidad);

#endif                          // GO_H_INCLUDED
