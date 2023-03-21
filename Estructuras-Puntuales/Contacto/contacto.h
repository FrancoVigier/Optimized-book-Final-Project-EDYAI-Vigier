#ifndef __CONTACTO_H__
#define __CONTACTO_H__

  char *nombre;
  char *apellido;
  char *tel;
  unsigned int edad;
} Contac;


/**
 * Crea un nuevo contacto.
 */
Contacto contacto_crear();

/**
 * Crea una copia f�sica del contacto.
 */
Contacto contacto_copia(Contacto);

/**
 * Retorna 0 si los contactos tienen el mismo nombre.
 */
int contacto_comparar(Contacto, Contacto);

/**
 * Funci�n destructora de un contacto.
 */
void contacto_destruir(Contacto);

/**
 * Hashear un contacto por su nombre.
 */
unsigned contacto_heashear(Contacto);

* Actualizamos un contacto mediante su dir de memoria
*/
void actualizar_contacto(Contacto *, void *);

/**
* Comparamos por edad dos contactos
*/

/**
* Comparamos por apellido dos contactos
*/

/**
* Comparamos por telefono dos contactos
*/

/**
* Comparamos por nombre dos contactos
*/

/**
 * Imprime por pantalla un contacto.
 */
void contacto_imprimir(void *);

/**
* Creamos un contacto solo que tenga NyA
*/

#endif  /* __CONTACTO_H__ */