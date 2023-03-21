#ifndef __HASH_H__
#define __HASH_H__
#include <stdbool.h>
#include <stdio.h>
#define LARGOBUCKET 100.0f

/** Retorna una copia fisica del dato */
typedef void *(*FuncionCopiadora)(void *dato);

/** Retorna un valor de comparacion de los datos*/
typedef int (*FuncionComparadora)(void *dato1, void *dato2);

/** Retorna un valor de recibe una direcciond de mem y actualiza
    el contenido*/typedef void (*FuncionActualizarDato)(void **datoActualizar, void *dato);

/** Funcion que agrega un dato a la una estructura dada*/typedef void *(*FuncionAgregadora)(void *tabla, void *datoB);

/** Funcion que agrega un dato a la estructura elegida como
    area de rebalse */typedef void *(*FuncionAggRebalse)(void *area, void *dato, FuncionCopiadora,
                                    FuncionComparadora);

/** Retorna un entero negativo si dato1 < dato2, 0 si son iguales y un entero
 * positivo si dato1 > dato2  */
typedef void *(*FuncionBuscadoraRebalse)(void *dato1, void *dato2,
                                         FuncionComparadora);
/** Funcion que destruye la data que contenemos en cualquier nodo */typedef void (*FuncionDestructora)(void *dato);

/** Funcion que elimina de nuestra area de rebalse un dato especifico */typedef void *(*FuncionElimUnicoRebalse)(void *area, void *dato,
                                          FuncionComparadora,
                                          FuncionDestructora, int *bandera);

/** Funcion que destruye el área de rebalse elegida */
typedef void (*FuncionDestructoraRebalse)(void *dato, FuncionDestructora);

/** Funcion que inserta en una direccion de mem un dato*/typedef void (*FuncionVisitanteDoble)(void **dato, void *datoB);

/** Funcion que nos permite rehashear nuestra area de rebalse*/typedef void (*FuncionRehashRebalse)(void *dato, FuncionVisitanteDoble,
                                      void *datoB);

/** Funcion inicializadora de nuestra area de rebalse*/typedef void *(*FuncionIniciarRebalse)();
/** Funcion hash*/typedef unsigned (*FuncionHash)(void *dato);

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
  int elementos;
  float factorCarga;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash * elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;     ///Copia un nodo-Dato
  FuncionComparadora comp;    ///Compara nodos(igualdad)
  FuncionBuscadoraRebalse buscarRebalse;      ///glist_buscar
  FuncionDestructora destr;    ///Libera un nodo Contacto
  FuncionDestructoraRebalse destrRebalse;     ///glist_destruir
  FuncionIniciarRebalse initRebalse;   ///glist_crear
  FuncionAggRebalse aggRebalse;       ///glist_agregar_inicio
  FuncionComparadora aggBucket;   ///Comparacion por nombre de los Contactos
  FuncionElimUnicoRebalse eliminarUnicoRebalse;     ///eliminar especifico de glist
  FuncionActualizarDato actDato;  ///actualizar_contacto
  FuncionRehashRebalse rehashRebalse;
  FuncionHash hash; ///KR hash
};
typedef struct _TablaHash *TablaHash;

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned, FuncionCopiadora,
                              FuncionComparadora,
                              FuncionBuscadoraRebalse,
                              FuncionDestructora,
                              FuncionDestructoraRebalse,
                              FuncionIniciarRebalse,
                              FuncionAggRebalse,
                              FuncionElimUnicoRebalse,
                              FuncionActualizarDato,
                              FuncionComparadora,
                              FuncionRehashRebalse,
                              FuncionHash);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash);

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(void **, void *);

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void **tablahash_buscar(TablaHash , void *);

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
int tablahash_eliminar(TablaHash, void *);

/**
 * Calcula el factor de carga de la tabla.
 */float calcular_factor_carga_Tabla(TablaHash);

/**
* A implementar: Rehash de la tabla
*/void rehashing(void **, TablaHash*);

#endif  /* __TABLAHASH_H__ */
