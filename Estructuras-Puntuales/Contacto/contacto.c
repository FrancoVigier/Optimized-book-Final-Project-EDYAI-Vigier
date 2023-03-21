#include "contacto.h"
#include "../../Estructuras-Generales/Anexo/utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/**
 * Crea un nuevo contacto.
 */
Contacto contacto_crear(char *nombre, char *apellido, char *telefono,
                            unsigned int edad) {
  Contacto nuevo = malloc(sizeof(struct _Contacto));
  assert(nuevo != NULL);
  nuevo->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
  assert(nuevo->nombre != NULL);
  strcpy(nuevo->nombre, nombre);
  nuevo->apellido = malloc(sizeof(char) * (strlen(apellido) + 1));
  strcpy(nuevo->apellido, apellido);
  nuevo->tel = malloc(sizeof(char) * (strlen(telefono) + 1));
  strcpy(nuevo->tel, telefono);
  nuevo->edad = edad;
  return nuevo;
}

/**
 * Crea una copia física del contacto.
 */
Contacto contacto_copia(Contacto contacto) {
  Contacto copia =
      contacto_crear(contacto->nombre, contacto->apellido, contacto->tel,
                      contacto->edad);
  return copia;
}

/**
 * Retorna 0 si los contactos tienen el mismo nombre y apellido.
 */
int contacto_comparar(Contacto c1, Contacto c2) {
  return (strcmp(c1->nombre, c2->nombre) == 0
           && strcmp(c1->apellido, c2->apellido) == 0) ? 0 : 1;
}
/**
 * Solo se comparan las edades.
 */int comparar_por_edad(void *p1, void *p2) {
  int a = ((Contacto) p1)->edad;
  int b = ((Contacto) p2)->edad;
  return a < b ? -1 : a == b ? 0 : 1;
}
/**
 * Solo se comparan los nombres.
 */int comparar_por_nombre(void *p1, void *p2) {
  return strcmp(((Contacto) p1)->nombre, ((Contacto) p2)->nombre);
}
/**
 * Solo se comparan los apellidos.
 */int comparar_por_apellido(void *p1, void *p2) {
  return strcmp(((Contacto) p1)->apellido, ((Contacto) p2)->apellido);
}
/**
 * Solo se comparan los telefonos.
 */int comparar_por_telefono(void *p1, void *p2) {
  return strcmp(((Contacto) p1)->tel, ((Contacto) p2)->tel);
}
/**
* Se actualiza un Contacto dado su dir de mem
*/void actualizar_contacto(Contacto * contacto, void *dato) {
  ((Contacto) * contacto)->tel =
      realloc(((Contacto) * contacto)->tel,
              (strlen(((Contacto) dato)->tel) + 1) * sizeof(char));
  strcpy(((Contacto) * contacto)->tel, ((Contacto) dato)->tel);
  ((Contacto) * contacto)->edad = ((Contacto) dato)->edad;
}
/**
 * Función destructora de un contacto.
 */
void contacto_destruir(Contacto contacto) {
  free(contacto->nombre);
  free(contacto->tel);
  free(contacto->apellido);
  free(contacto);
}

/**
 * Hashear un contacto por su nombre.
 */
unsigned contacto_heashear(Contacto contacto) {
  return KRHash(contacto->nombre);
}

/**
 * Imprime por pantalla un contacto.
 */
void contacto_imprimir(void *contacto) {
  printf("{%s, %s, %s, %d}\n", ((Contacto) contacto)->nombre,
          ((Contacto) contacto)->apellido, ((Contacto) contacto)->tel,
          ((Contacto) contacto)->edad);
}
/**
* Crea un contacto solo con nombre y apellido,
* provechoso para hacer eliminacion o busqueda
*/Contacto crear_dummy(char *nombre, char *apellido) {
  return contacto_crear(nombre, apellido, "0", 0);
}
