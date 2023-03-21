#include "hash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../Estructuras-Generales/DList/LSE.h"
#include "../../Estructuras-Puntuales/Contacto/contacto.h"
/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                              FuncionComparadora comp,
                              FuncionBuscadoraRebalse buscarRebalse,
                              FuncionDestructora destr,
                              FuncionDestructoraRebalse destrRebalse,
                              FuncionIniciarRebalse initRebalse,
                              FuncionAggRebalse aggRebalse,
                              FuncionElimUnicoRebalse eliminarUnicoRebalse,
                              FuncionActualizarDato actDato,
                              FuncionComparadora aggBucket,
                              FuncionRehashRebalse rehashRebalse,
                              FuncionHash hash) {
  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  for (unsigned int i = 0; i < tabla->capacidad; i++) {
    tabla->elems[i].elementos = 0;
    tabla->elems[i].factorCarga = 0.0;
  }  tabla->copia = copia;
  tabla->comp = comp;
  tabla->buscarRebalse = buscarRebalse;
  tabla->destr = destr;
  tabla->destrRebalse = destrRebalse;
  tabla->initRebalse = initRebalse;
  tabla->aggRebalse = aggRebalse;
  tabla->aggBucket = aggBucket;
  tabla->eliminarUnicoRebalse = eliminarUnicoRebalse;
  tabla->actDato = actDato;
  tabla->rehashRebalse = rehashRebalse;
  tabla->hash = hash;
// Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; idx++) {
    tabla->elems[idx].dato = NULL;
  }  return tabla;
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {
  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; idx++) {
    if (tabla->elems[idx].dato != NULL) {
      tabla->destrRebalse(tabla->elems[idx].dato, tabla->destr);
    }
  }
  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}
/** Calcula el factor de carga de la tabla como el
    promedio de las cargas de cada área de rebalse*/float calcular_factor_carga_Tabla(TablaHash tabla) {
  float carry = 0.0F;
  for (unsigned idx = 0; idx < tabla->capacidad; idx++)
    if (tabla->elems[idx].dato != NULL)
      carry += tabla->elems[idx].factorCarga;
  return carry / tabla->capacidad;
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(void **tablaA, void *dato) {
  TablaHash tabla = ((TablaHash) * tablaA);
 /**
  float loadFHash = 0.0;
  loadFHash = calcular_factor_carga_Tabla(tabla);
  */
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[idx].dato == NULL) {
    tabla->numElems++;
    tabla->elems[idx].dato =
        tabla->aggRebalse(tabla->elems[idx].dato, dato, tabla->copia,
                          tabla->aggBucket);
    tabla->elems[idx].elementos = 1;
    tabla->elems[idx].factorCarga = tabla->elems[idx].elementos / LARGOBUCKET;

    return;
  }
  //Si esta el insertado, lo reemplazo. Si no esta lo agrego
  void **rebalseDato =
      tabla->buscarRebalse(tabla->elems[idx].dato, dato, tabla->comp);
  if (rebalseDato != NULL) {
    tabla->actDato(rebalseDato, dato);
  }
  else {
    tabla->numElems++;
    tabla->elems[idx].dato =
        tabla->aggRebalse(tabla->elems[idx].dato, dato, tabla->copia,
                          tabla->aggBucket);
    tabla->elems[idx].elementos++;
    tabla->elems[idx].factorCarga = tabla->elems[idx].elementos / LARGOBUCKET;
  }
}


/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void **tablahash_buscar(TablaHash tabla, void *dato) {
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  // Retornar NULL si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return NULL;
  void **rebalseDato =
      tabla->buscarRebalse(tabla->elems[idx].dato, dato, tabla->comp);
  if (rebalseDato != NULL) {
    return (rebalseDato);      ///NNODO el dato es NNODO-DATA
  }
  else
    return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
int tablahash_eliminar(TablaHash tabla, void *dato) {
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  // Retornar si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return 0;
  // Vaciar la casilla si hay coincidencia.
  int bandera = 0;
  tabla->elems[idx].dato =
      tabla->eliminarUnicoRebalse(tabla->elems[idx].dato, dato, tabla->comp,
                                  tabla->destr, &bandera);
  //Si hubo exito en la eliminación, disminuyo contadores
  if (bandera == 1) {
    tabla->numElems--;
    tabla->elems[idx].elementos--;
    tabla->elems[idx].factorCarga = tabla->elems[idx].elementos / LARGOBUCKET;
    return 1;
  }
  return 0;
}


