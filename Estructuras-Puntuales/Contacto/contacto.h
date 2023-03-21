#ifndef __CONTACTO_H__
#define __CONTACTO_H__
typedef struct _Contacto {
  char *nombre;
  char *apellido;
  char *tel;
  unsigned int edad;
} Contac;
typedef struct _Contacto *Contacto;

/**
 * Crea un nuevo contacto.
 */
Contacto contacto_crear();

/**
 * Crea una copia física del contacto.
 */
Contacto contacto_copia(Contacto);

/**
 * Retorna 0 si los contactos tienen el mismo nombre.
 */
int contacto_comparar(Contacto, Contacto);

/**
 * Función destructora de un contacto.
 */
void contacto_destruir(Contacto);

/**
 * Hashear un contacto por su nombre.
 */
unsigned contacto_heashear(Contacto);
/**
* Actualizamos un contacto mediante su dir de memoria
*/
void actualizar_contacto(Contacto *, void *);

/**
* Comparamos por edad dos contactos
*/int comparar_por_edad(void *, void *);

/**
* Comparamos por apellido dos contactos
*/int comparar_por_apellido(void *, void *);

/**
* Comparamos por telefono dos contactos
*/int comparar_por_telefono(void *, void *);

/**
* Comparamos por nombre dos contactos
*/int comparar_por_nombre(void *, void *);

/**
 * Imprime por pantalla un contacto.
 */
void contacto_imprimir(void *);

/**
* Creamos un contacto solo que tenga NyA
*/Contacto crear_dummy(char *, char *);

#endif  /* __CONTACTO_H__ */
