#include "./Core/Interprete/interprete.h"
#define CAPACIDAD_INICIAL 26 ///Cantidad de áreas de rebalse
int main() {
  ///Se inicializa la tabla hash con sus parámetros iniciales y con las
  ///funciones características de un área de rebalse.
  TablaHash tabla =
      tablahash_crear(CAPACIDAD_INICIAL, (FuncionCopiadora) contacto_copia,
                      (FuncionComparadora) contacto_comparar,
                      (FuncionBuscadoraRebalse) glist_buscar_memoria,
                      (FuncionDestructora) contacto_destruir,
                      (FuncionDestructoraRebalse) glist_destruir,
                      (FuncionIniciarRebalse) glist_crear,
                      (FuncionAggRebalse) glist_agregar_inicio,
                      (FuncionElimUnicoRebalse) glist_eliminar_nodo,
                      (FuncionActualizarDato) actualizar_contacto,
                      (FuncionComparadora) comparar_por_nombre,
                      (FuncionRehashRebalse) glist_recorrer_doble,
                      (FuncionHash) contacto_heashear);
  mostrar_prompt();
  interprete(tabla);
  tablahash_destruir(tabla);
  return 0;
}


