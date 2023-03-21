#include "procesamiento.h"
/**
* Obtencion sencilla de datos con deteccion de errores
*/ int obtencion_datos(char *aGuardar, int argumento, char **asignacion) {
  setbuf(stdin, NULL);
  switch (argumento) {
    case 1:
      printf("Inserte Nombre:\n");
      if (scanf("%[^\n]", (aGuardar)) == 0)
        return 2;
      if (asignacion != NULL)
        (*asignacion) = aGuardar;
      return 0;
      break;
    case 2:
      printf("Inserte Apellido:\n");
      if (scanf("%[^\n]", (aGuardar)) == 0)
        return 2;
      if (asignacion != NULL)
        (*asignacion) = aGuardar;
      return 0;
      break;
    case 3:
      printf("Inserte Telefono:\n");
      if (scanf("%[^\n]", (aGuardar)) == 0)
        return 2;
      if (aGuardar[0] == '-')
        return 3;
      if (sscanf(aGuardar, "%[^a-z, ^A-Z]", aGuardar) != 1) {
        printf("Telefono no puramente numerico\n");
        return 1;
      }
      if (asignacion != NULL)
        (*asignacion) = aGuardar;
      return 0;
      break;
    case 4:
      printf("Inserte Edad:\n");
      if (scanf("%[^\n]", (aGuardar)) == 0)
        return 2;
      if (aGuardar[0] == '-')
        return 3;
      if (sscanf(aGuardar, "%[^a-z, ^A-Z]", aGuardar) != 1) {
        printf("Edad no puramente numerico\n");
        return 1;
      }
      return 0;
      break;
    case 5:
      printf("Inserte Path:\n");
      if (scanf("%[^\n]", (aGuardar)) == 0)
        return 2;
      if (strrchr(aGuardar, '.') != NULL
           && strcmp(strrchr(aGuardar, '.'), ".csv") == 0)
        return 0;
      printf("No es ruta de un archivo .csv...\n");
      return 1;
      break;
    case 6:
      printf
        ("Elija parametro para ordenar: 'nombre' 'apellido' 'telefono' 'edad'\n");
      if (scanf("%[^\n]", (aGuardar)) == 0)
        return 2;
      if (strcmp(aGuardar, "nombre") == 0 || strcmp(aGuardar, "apellido") == 0
           || strcmp(aGuardar, "telefono") == 0
           || strcmp(aGuardar, "edad") == 0)
        return 0;
      return 1;
      break;
    case 7:                     ///Control nombre archivo
      if (aGuardar == NULL || strcmp(aGuardar, "") == 0)
        return 2;
      if (asignacion != NULL)
        strcpy((*asignacion), aGuardar);
      return 0;
      break;
    case 8:                     ///Control apellido archivo
      if (aGuardar == NULL || strcmp(aGuardar, "") == 0)
        return 2;
      if (asignacion != NULL)
        strcpy((*asignacion), aGuardar);
      return 0;
      break;
    case 9:                     ///Control edad archivo
      if (aGuardar == NULL || strcmp(aGuardar, "") == 0)
        return 2;
      if (aGuardar[0] == '-')
        return 3;
      if (sscanf(aGuardar, "%[^a-z, ^A-Z]", aGuardar) != 1) {
        printf("Edad no puramente numerico\n");
        return 1;
      }
      if (asignacion != NULL)
        strcpy((*asignacion), aGuardar);
      return 0;
      break;
    case 10:
      if (aGuardar == NULL || strcmp(aGuardar, "") == 0)
        return 2;
      if (aGuardar[0] == '-')
        return 3;
      if (sscanf(aGuardar, "%[^a-z, ^A-Z]", aGuardar) != 1) {
        printf("Telefono no puramente numerico\n");
        return 1;
      }
      if (asignacion != NULL)
        strcpy((*asignacion), aGuardar);
      return 0;
      break;
  }
  return 0;
}
/**
* Creamos el directorio del archivo
*/void rek_mkdir(char *path) {
  char *sep = strrchr(path, '/');
  if (sep != NULL) {
    *sep = 0;
    rek_mkdir(path);
    *sep = '/';
  }
  if (mkdir(path, 0777) && errno != EEXIST)
    printf("Error al  crear el path...\n");
}

/**
* Creamos/Revisamos el directorio con rek_mkdir y
* si es posible la ruta creamos/leemos el archivo
*/FILE * fopen_mkdir(char *path, char *mode) {
  char *sep = strrchr(path, '/');
  if (sep) {
    char *path0 = malloc(sizeof(char) * (strlen(path) + 1));
    strcpy(path0, path);
    path0[sep - path] = 0;
    rek_mkdir(path0);
    free(path0);
  }
  return fopen(path, mode);
}
/**
* Volcamos el contenido de un Contacto al archivo
*/void escribir_archivo(void *dato, FILE * archivo) {
  fprintf(archivo, "%s,%s,%i,%s\n", ((Contacto) dato)->nombre,
           ((Contacto) dato)->apellido, ((Contacto) dato)->edad,
           ((Contacto) dato)->tel);
}
/**
* Volcamos el contenido de cada area de rebalse a la tabla, por ende
* volcamos la tabla al archivo
*/void guardar_tabla(FILE * archivo, TablaHash tabla) {
  fprintf(archivo, "nombre,apellido,edad,telefono\n");
  for (unsigned int i = 0; tabla->capacidad > i; i++)
    glist_recorrer_archivo(tabla->elems[i].dato, escribir_archivo, archivo);
}
/**
* Verificamos si la linea de un .csv es correcta
*/
int correcion_Linea(char *linea, char **nombre, char **apellido,
                             char **telefono, char **edad) {
  char nombreL[100] = { };
  char apellidoL[100] = { };
  char edadL[100] = { };
  char telefonoL[100] = { };
  if (sscanf
         (linea, "%[^','],%[^','],%[^','],%[^',']", nombreL, apellidoL, edadL,
          telefonoL) == 4) {
    int okN = obtencion_datos(nombreL, 7, nombre);
    int okA = obtencion_datos(apellidoL, 8, apellido);
    int okT = obtencion_datos(telefonoL, 10, telefono);
    int okE = obtencion_datos(edadL, 9, edad);
    if (okN + okA + okT + okE != 0) {
      printf("Linea de csv mal formada...\n");
      return 1;
    }
    else
      return 0;
  }
  else {
    printf("Linea de csv mal formada...\n");
    return 1;
  }
}
void comer_finales_de_linea(FILE * archivo) {
  int car;
  while ((car = fgetc(archivo)) == '\r' || car == '\n')
    if (car == '\r')
      fgetc(archivo);
  if (car != EOF)
    ungetc(car, archivo);
}
void cargar_tabla(FILE * archivo, TablaHash tabla, Pila * Deshacer,
                       int *pilaDeshacerelems, int *pilaCapacidad) {
  int primeraLinea = 0;
  int error = 0;
  char *nombre = malloc(sizeof(char) * 100);
  char *apellido = malloc(sizeof(char) * 100);
  char *telefono = malloc(sizeof(char) * 100);
  char *edad = malloc(sizeof(char) * 100);
  while (!feof(archivo) || error != 0) {
    char *linea = malloc(sizeof(char) * 1024);
    if (fscanf(archivo, "%1023[^\n\r]", linea) != 0) {
      if (primeraLinea != 0) {
        if (correcion_Linea(linea, &nombre, &apellido, &telefono, &edad) == 0) {
          unsigned int aos = atoi(edad);
          Contacto aGuardar = contacto_crear(nombre, apellido, telefono, aos);
          tablahash_insertar((void **) &tabla, aGuardar);
          NNodo operacion =
              crear_NNodo(1, nombre, apellido, telefono, "", aos, 0);
          (*Deshacer) =
              pila_apilar( (*Deshacer), operacion, NNodo_copia,
                          pilaDeshacerelems, pilaCapacidad);
          freeNNodo(operacion);
          contacto_destruir(aGuardar);
        }
        else {
          printf("Error en los campos del .csv...\n");
          error = 1;
        }
      }
      else
        primeraLinea = 1;
    }
    else {
      printf("Linea nula en el .csv\n");
      error = 1;
    }
    free(linea);
    comer_finales_de_linea(archivo);
  }
  free(nombre);
  free(apellido);
  free(edad);
  free(telefono);
}


