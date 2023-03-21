#ifndef PROCESAMIENTO_H_INCLUDED
#define PROCESAMIENTO_H_INCLUDED

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../../Estructuras-Generales/Hash/hash.h"
#include "../../Estructuras-Generales/DList/LSE.h"
#include "../../Estructuras-Puntuales/Contacto/contacto.h"
#include "../../Estructuras-Puntuales/Encapsulador/nthnodo.h"
#include "../../Estructuras-Generales/Pila/pila.h"
#include <fcntl.h>
#include <sys/stat.h>
/**
* Funcion que se encarga de obtener los argumentos de entrada del
* interprete( hace discriminacion de errores)
*/
int obtencion_datos(char *, int, char **);

/**
* Funcion que Crea el directorio
*/void rek_mkdir(char *);

/**
* Funcion que llama a rekmkdir para crear el directorio
* y crea/escribe o lee el archivo existente o a crear
* gracias a una string que es el modo
*/FILE * fopen_mkdir(char *, char *);

/**
* Vuelca el contenido de la tabla a un archivo
*/void guardar_tabla(FILE * , TablaHash );

/**
* Vuelca el contenido de cada area de rebalse al archivo
*/void escribir_archivo(void *, FILE * );

/**
* Carga un archivo a la tabla
*/void cargar_tabla(FILE *, TablaHash, Pila *,
                   int *, int *);

/**
* Funcion que nos permite avanzar en las lineas del archivo
*/void comer_finales_de_linea(FILE *);

/**
* Funcion que nos permite saber si una linea del .csv es
* bien formulada
*/int correcion_Linea(char *, char **, char **,
                     char **, char **);

#endif                          // PROCESAMIENTO_H_INCLUDED
