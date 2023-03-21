#include "AO.h"
/**
* Comparamos un nodo con los parametros ingresados
*/int comparar_parametrico_AND_OR(int AoO, void *contacto, char *nombre,
                                   char *apellido, char *telefono,
                                   unsigned int *edad) {
  ///AoO = 0-----AND
  ///AoO = 1 -----OR
  //Si el contacto tiene igual todos los campos pasados, indistintamente de AND/OR
  //el contacto está
  if ((nombre == NULL
            || strcmp(((Contacto) contacto)->nombre, nombre) == 0)
           && (apellido == NULL
               || strcmp(((Contacto) contacto)->apellido,
                         apellido) == 0) &&(telefono == NULL
                                              || strcmp(((Contacto) contacto)->
                                                        tel, telefono) == 0)
           && (edad == NULL || (*edad) == ((Contacto) contacto)->edad))
    return 0;
  if (AoO == 0) //Si no es igual y estamos en un AND el nodo no esta
   return 1;
  //Estamos en OR. Si el nodo cumple con al menos uno de los parametros
  // el nodo es correcto
  if ((nombre != NULL && strcmp(((Contacto) contacto)->nombre, nombre) == 0)
         || (apellido != NULL
             && strcmp(((Contacto) contacto)->apellido,
                       apellido) == 0) ||(telefono != NULL
                                            && strcmp(((Contacto) contacto)->
                                                      tel, telefono) == 0)
         || (edad != NULL && (*edad) == ((Contacto) contacto)->edad))
    return 0;
  return 1;
}
/**
* Busqueda por parametros en una area de rebalse
*/void glist_AND_OR(GList lista, int AoO, char *nombre, char *apellido,
                     char *telefono, unsigned int *edad) {
  for (GNodo * nodo = lista; nodo != NULL; nodo = nodo->sig)
    if (comparar_parametrico_AND_OR
         (AoO, nodo->dato, nombre, apellido, telefono, edad) == 0)
      contacto_imprimir(nodo->dato);
}
/**
* Funcion de Busqueda AND/OR
*/void AND_OR(TablaHash tabla, int AoO, char *nombre, char *apellido,
               char *telefono, unsigned int *edad) {
  //Si estamos en AND y todos los campos son nulos salgo
  if (AoO == 0 && nombre == NULL && apellido == NULL && telefono == NULL
         && edad == NULL)
    return;
  //Si estamos en AND/OR y solo hago busqueda por nombre, oriento la busqueda
  if (AoO == 0 || (AoO == 1 && apellido == NULL && telefono == NULL && edad == NULL)) {        // SI ESTAMOS EN AND y tenemos el nombre ORIENTO, Y SI ESTAMOS EN OR Y TENGO SOLAMENTE EL NOMBRE ORIENTO
    if (nombre != NULL) {
      printf("NOMBRE A BUSCAR EN AND: -%s-\n", nombre);
      ///Oriento la busqueda
      unsigned idx = KRHash(nombre) % tabla->capacidad;
      glist_AND_OR(tabla->elems[idx].dato, AoO, nombre, apellido, telefono,
                    edad);
      printf("SE TERMINO LA BUSQUEDA\n");
      return;
    }
  }
  //Busqueda normal
  for (unsigned int i = 0; tabla->capacidad > i; i++)
    glist_AND_OR(tabla->elems[i].dato, AoO, nombre, apellido, telefono, edad);

  printf("SE TERMINO LA BUSQUEDA\n");
}
