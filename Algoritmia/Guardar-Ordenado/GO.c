#include "GO.h"
/**
* Ordenamos un area de rebalse por medio de merge-sort
* con la funcion comparacion indicada
*/GList aplicar_orden(GList lista, int orden, FuncionComparadora porApellido,
                       FuncionComparadora porNombre,
                       FuncionComparadora porEdad,
                       FuncionComparadora porTelefono) {
  if (orden == 1)
    return merge_sort(lista, porNombre);
  if (orden == 2)
    return merge_sort(lista, porApellido);
  if (orden == 3)
    return merge_sort(lista, porTelefono);
  if (orden == 4)
    return merge_sort(lista, porEdad);
  return NULL;
}

/**
* Unimos dos areas de rebalse previamente ordenadas,
* respetando el parametro preestablecido
*/GList merge_bucket(GList acumulado, GList rebalse, int orden,
                      FuncionComparadora porApellido,
                      FuncionComparadora porNombre,
                      FuncionComparadora porEdad,
                      FuncionComparadora porTelefono, int *cantidad) {
  if (orden == 1)
    return mergehash(acumulado, rebalse, porNombre, cantidad);
  if (orden == 2)
    return mergehash(acumulado, rebalse, porApellido, cantidad);
  if (orden == 3)
    return mergehash(acumulado, rebalse, porTelefono, cantidad);
  if (orden == 4)
    return mergehash(acumulado, rebalse, porEdad, cantidad);
  return NULL;
}
/**
* Ordenamos todas las areas de rebalse y las unimos por el parametro pasado
*/void ordenar_campo(TablaHash tabla, int orden,
                      FuncionComparadora porApellido,
                      FuncionComparadora porNombre,
                      FuncionComparadora porEdad,
                      FuncionComparadora porTelefono, FILE * archivo) {
  int cantidad = 0;
  GList superMerge = glist_crear();
  for (unsigned int i = 0; tabla->capacidad > i; i++) {
    //Ordenamos un area de rebalse
    tabla->elems[i].dato =
        aplicar_orden(tabla->elems[i].dato, orden, porApellido, porNombre,
                      porEdad, porTelefono);
    //Unimos areas de rebalse
    superMerge =
        merge_bucket(superMerge, tabla->elems[i].dato, orden, porApellido,
                     porNombre, porEdad, porTelefono, &cantidad);
  }
  fprintf(archivo, "nombre,apellido,edad,telefono\n");
  //Pasamos a archivo
  glist_recorrer_archivo(superMerge, escribir_archivo, archivo);
  glist_destruir(superMerge,NULL);
}/**
* Ordenamos la tabla por un parametro expreso en el enunciado
*/void ordenar_parametro(TablaHash tabla, char *parametro, FILE * archivo) {
  if (strcmp(parametro, "nombre") == 0) {
    ordenar_campo(tabla, 1, comparar_por_apellido, comparar_por_nombre,
                   comparar_por_edad, comparar_por_telefono, archivo);
    return;
  }
  if (strcmp(parametro, "apellido") == 0) {
    ordenar_campo(tabla, 2, comparar_por_apellido, comparar_por_nombre,
                   comparar_por_edad, comparar_por_telefono, archivo);
    return;
  }
  if (strcmp(parametro, "telefono") == 0) {
    ordenar_campo(tabla, 3, comparar_por_apellido, comparar_por_nombre,
                   comparar_por_edad, comparar_por_telefono, archivo);
    return;
  }
  if (strcmp(parametro, "edad") == 0) {
    ordenar_campo(tabla, 4, comparar_por_apellido, comparar_por_nombre,
                   comparar_por_edad, comparar_por_telefono, archivo);
    return;
  }
  printf("Parametro ingresado erroneo...\n");
}


