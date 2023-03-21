#include "nthnodo.h"
/**
 * Crea un nuevo encapsulador.
 */ NNodo crear_NNodo(int tipoDato, char *nombre, char *apellido, char *telViejo,
                    char *telNuevo, int edadVieja, int edadNueva) {
  NNodo nodo = malloc(sizeof(struct _NodoNTipo));
  nodo->tipoDeDato = tipoDato;
  nodo->edadNueva = edadNueva;
  nodo->edadVieja = edadVieja;
  nodo->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
  strcpy(nodo->nombre, nombre);
  nodo->apellido = malloc(sizeof(char) * (strlen(apellido) + 1));
  strcpy(nodo->apellido, apellido);
  nodo->telNuevo = malloc(sizeof(char) * (strlen(telNuevo) + 1));
  strcpy(nodo->telNuevo, telNuevo);
  nodo->telViejo = malloc(sizeof(char) * (strlen(telViejo) + 1));
  strcpy(nodo->telViejo, telViejo);
  return nodo;
}
/**
 * Crea una copia física del encapsulador.
 */void *NNodo_copia(void *nodo) {
  NNodo copia =
      crear_NNodo(((NNodo) nodo)->tipoDeDato, ((NNodo) nodo)->nombre,
                   ((NNodo) nodo)->apellido, ((NNodo) nodo)->telViejo,
                   ((NNodo) nodo)->telNuevo, ((NNodo) nodo)->edadVieja,
                   ((NNodo) nodo)->edadNueva);
  return copia;
}
/**
 * Función destructora de un encapsulador.
 */void freeNNodo(void *dato) {
  free(((NNodo) dato)->nombre);
  free(((NNodo) dato)->apellido);
  free(((NNodo) dato)->telNuevo);
  free(((NNodo) dato)->telViejo);
  free(dato);
}
