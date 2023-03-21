#include "DR.h"
/**
* rehacer_operacion: Permite realizar los cambios en la tabla hash,
* estos "cambios" son nodos encapsuladores apilados en la pila Rehacer.
* Luego de rehacer un cambio, a este último lo apilamos en la pila Deshacer.
*/
void rehacer_operacion(TablaHash tabla, Pila * Rehacer, int *pilaRehacerelems,
                       int *pilaCapacidad, Pila * Deshacer, int *pilaRelems) {
  // Si realicé todos los cambios, no puedo seguir
  if (0 >= (*pilaRehacerelems)) {
    printf("Se rehicieron todos los pasos\n");
    return;
  }
  printf("Pasos disponibles para REHACER: -%i-\n", (*pilaRehacerelems));
  NNodo op = pila_ultimo(*Rehacer);
  //Apilo en Deshacer el cambio que voy a realizar
  (*Deshacer) =
      pila_apilar((*Deshacer), op, NNodo_copia, pilaRelems, pilaCapacidad);
  //Dependiendo del tipo de op. que represente el encapsulador, la realizo
  if (op->tipoDeDato == 1) {
    Contacto aAgregar =
        contacto_crear((char *) op->nombre, (char *) op->apellido,
                       (char *) op->telViejo, op->edadVieja);
    tablahash_insertar((void **) &tabla, aAgregar);
    contacto_destruir(aAgregar);  }
  if (op->tipoDeDato == 2) {
    Contacto aEditar =
        crear_dummy((char *) op->nombre, (char *) op->apellido);
    Contacto * esta = (Contacto *) tablahash_buscar(tabla, aEditar);
    Contacto actualizo =
        contacto_crear((char *) op->nombre, (char *) op->apellido,
                       (char *) op->telNuevo, op->edadNueva);
    actualizar_contacto(esta, actualizo);
    contacto_destruir(aEditar);
    contacto_destruir(actualizo);  }
  if (op->tipoDeDato == 3) {
    Contacto aEliminar =
        crear_dummy((char *) op->nombre, (char *) op->apellido);
    tablahash_eliminar(tabla, aEliminar);
    contacto_destruir(aEliminar);
  }
  //Desapilo
  (*Rehacer) = pila_desapilar((*Rehacer),freeNNodo);
  (*pilaRehacerelems)--;
}

/**
* deshacer_operacion: Permite deshacer los cambios en la tabla hash,
* estos "cambios" son nodos encapsuladores apilados en la pila Deshacer
* Luego de deshacer un cambio( mediante su inversa),
* a este último lo apilamos en la pila Rehacer.
*/
void deshacer_operacion(TablaHash tabla, Pila * Deshacer, int *pilanelems,
                        int *pilaCap, Pila * Rehacer, int *pilaDnelems) {
  // Si realicé todos los cambios, no puedo seguir
  if (0 >= (*pilanelems)) {
    printf("Se deshicieron todos los pasos\n");
    return;
  }
  printf("Pasos disponibles para DESHACER: -%i-\n", (*pilanelems));
  NNodo op = pila_ultimo(*Deshacer);
  //Apilo en Deshacer el cambio que voy a realizar
  (*Rehacer) =
      pila_apilar((*Rehacer), op, NNodo_copia, pilaDnelems, pilaCap);
  //Dependiendo del tipo de op. que represente el encapsulador, hago su inv.
  if (op->tipoDeDato == 1) {
    Contacto aEliminar =
        crear_dummy((char *) op->nombre, (char *) op->apellido);
    tablahash_eliminar(tabla, aEliminar);
    contacto_destruir(aEliminar);
  }
  if (op->tipoDeDato == 2) {
    Contacto aEditar =
        crear_dummy((char *) op->nombre, (char *) op->apellido);
    Contacto * esta = (Contacto *) tablahash_buscar(tabla, aEditar);
    Contacto actualizo =
        contacto_crear((char *) op->nombre, (char *) op->apellido,
                       (char *) op->telViejo, op->edadVieja);
    actualizar_contacto(esta, actualizo);
    contacto_destruir(aEditar);
    contacto_destruir(actualizo);
  }
  if (op->tipoDeDato == 3) {
    Contacto aAgregar =
        contacto_crear((char *) op->nombre, (char *) op->apellido,
                       (char *) op->telViejo, op->edadVieja);
    tablahash_insertar((void **) &tabla, aAgregar);
    contacto_destruir(aAgregar);
  }
  //Desapilo
  (*Deshacer) = pila_desapilar((*Deshacer),freeNNodo);
  (*pilanelems)--;
}
