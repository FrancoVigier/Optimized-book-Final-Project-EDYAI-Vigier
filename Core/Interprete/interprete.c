#include "interprete.h"

/**
* Menu de opciones
*/void mostrar_prompt() {
  printf("\nMenu de acciones:\n");
  printf("1. Buscar\n");
  printf("2. Agregar\n");
  printf("3. Eliminar\n");
  printf("4. Editar\n");
  printf("5. Guardar\n");
  printf("6. Cargar\n");
  printf("7. Deshacer\n");
  printf("8. Rehacer\n");
  printf("9. AND\n");
  printf("10. OR\n");
  printf("11. Guardar ordenado\n");
  printf("12. Buscar por suma de edades\n");
  printf("13. Salir\n");
}
/**
* Interprete del programa
*/void interprete(TablaHash tabla) {
  char com[100] = { };
  char directorio[100] = { };
  char nombre[100] = { };
  char apellido[100] = { };
  char telefono[100] = { };
  char edadC[10] = { };
  char ordenar[100] = { };
  unsigned int edad = 0;

/// Inicializamos las Pilas de D/R
  int pilaCapacidad = N_PILA;
  int pilaDeshacerelems = 0;
  int pilaRehacerelems = 0;
  Pila Deshacer = pila_crear();
  Pila Rehacer = pila_crear();
///
  while (strcmp(com, "13") != 0) {
    int instruccion = 0;
    setbuf(stdin, NULL);       // Limpiamos el buffer para no tener basura.
    printf(">");
    strcpy(com, "");
    scanf("%[^\n]", com);
    instruccion = atoi(com);
    switch (instruccion) {
      case 1:
        printf("Buscar...\n");
        int okay = obtencion_datos(nombre, 1, NULL);
        int okay2 = obtencion_datos(apellido, 2, NULL);
        if (okay2 + okay != 0)
          printf("CADENAS VACIAS\n");
        else {
          Contacto aBuscar = crear_dummy(nombre, apellido);
          Contacto * resultado = (Contacto *) tablahash_buscar(tabla, aBuscar);
          if (resultado == NULL)
          printf("No esta el Contacto solicitado\n");
          else
            contacto_imprimir(*resultado);
          contacto_destruir(aBuscar);
        }
        break;
    case 2:
      printf("Agregar...\n");
      int ok1 = obtencion_datos(nombre, 1, NULL);
      int ok2 = obtencion_datos(apellido, 2, NULL);
      int ok3 = obtencion_datos(telefono, 3, NULL);
      int ok4 = obtencion_datos(edadC, 4, NULL);
      if (ok1 + ok2 + ok3 + ok4 != 0)
        printf("Error en los parametros de entrada\n");
      else {
        edad = atoi(edadC);
        Contacto aAgendar = contacto_crear(nombre, apellido, telefono, edad);
        tablahash_insertar((void **) &tabla, (Contacto) aAgendar);

        NNodo operacion =
        crear_NNodo(1, nombre, apellido, telefono, "", edad, 0);
        Deshacer =
            pila_apilar(Deshacer, operacion, NNodo_copia, &pilaDeshacerelems,
                        &pilaCapacidad);

        contacto_destruir(aAgendar);
        freeNNodo(operacion);
      }      break;
    case 3:
      printf("Eliminar...\n");
      int okEN = obtencion_datos(nombre, 1, NULL);
      int okEA = obtencion_datos(apellido, 2, NULL);
      if (okEN + okEA != 0)
        printf("Cadenas Vacias...\n");
      else {
        Contacto aEliminar = crear_dummy(nombre, apellido);
        Contacto * estaElim = (Contacto *) tablahash_buscar(tabla, aEliminar);
        if (estaElim != NULL) {

          NNodo operacionElim =
              crear_NNodo(3, nombre, apellido, (*estaElim)->tel, "",
                          (*estaElim)->edad, 0);
          Deshacer =
              pila_apilar(Deshacer, operacionElim, NNodo_copia,
                          &pilaDeshacerelems, &pilaCapacidad);

          tablahash_eliminar(tabla, (Contacto) aEliminar);
          printf("Se elimino la persona pedida...\n");
          freeNNodo(operacionElim);
        } else {
          printf("No esta el nodo a eliminar...\n");
        }
        contacto_destruir(aEliminar);
      }
      break;
    case 4:
      printf("Editar...\n");
      int okEdN = obtencion_datos(nombre, 1, NULL);
      int okEdA = obtencion_datos(apellido, 2, NULL);
      if (okEdA + okEdN != 0)
        printf("Cadena vacia...\n");
      else {
        Contacto aEditar = crear_dummy(nombre, apellido);
        Contacto * esta = (Contacto *) tablahash_buscar(tabla, aEditar);
        if (esta != NULL) {
          int okEdT = obtencion_datos(telefono, 3, NULL);
          int okEdE = obtencion_datos(edadC, 4, NULL);
          if (okEdT + okEdE != 0)
            printf("Argumentos invalidos...\n");
          else {
            int editEdad = atoi(edadC);

            NNodo operacionElim =
                crear_NNodo(2, nombre, apellido, (*esta)->tel, telefono,
                            (*esta)->edad, editEdad);
            Deshacer =
                pila_apilar(Deshacer, operacionElim, NNodo_copia,
                            &pilaDeshacerelems, &pilaCapacidad);

            Contacto actualizo =
                contacto_crear(nombre, apellido, telefono, editEdad);
            actualizar_contacto(esta, actualizo);
            freeNNodo(operacionElim);
            contacto_destruir(actualizo);
        }
      } else {
        printf("No esta el nodo a actualizar\n");
      }
        contacto_destruir(aEditar);
      }
      break;
    case 5:
      printf("Guardar...\n");
      int dirOk = obtencion_datos(directorio, 5, NULL);
      if (dirOk != 0)
        printf("Error al crear el directorio...\n");
      else {
        char *mode = "w";
        FILE * archivo = fopen_mkdir(directorio, mode);
        if (archivo == NULL)
          printf("Error en la creacion del directorio y archivo...\n");
        else {
          guardar_tabla(archivo, tabla);
          printf("Guardado\n");
          fclose(archivo);
        }
      }
      break;
    case 6:
      printf("Cargar...\n");
      int dirCOk = obtencion_datos(directorio, 5, NULL);
      if (dirCOk != 0)
        printf("Error al leer el directorio...\n");
      else {
        char *mode = "r";
        FILE * archivo = fopen_mkdir(directorio, mode);
        if (archivo == NULL)
          printf("Error en la lectura del directorio y archivo...\n");
        else {
          cargar_tabla(archivo, tabla, &Deshacer, &pilaDeshacerelems,
                        &pilaCapacidad);
          fclose(archivo);
        }
      }
      break;
    case 7:
      printf("Deshacer...\n");
      deshacer_operacion(tabla, &Deshacer, &pilaDeshacerelems, &pilaCapacidad,
                          &Rehacer, &pilaRehacerelems);
      break;
    case 8:
      printf("Rehacer...\n");
      rehacer_operacion(tabla, &Rehacer, &pilaRehacerelems, &pilaCapacidad,
                         &Deshacer, &pilaDeshacerelems);
      break;
    case 9:
      printf("AND\n");
      char *campo1 = NULL;
      char *campo2 = NULL;
      char *campo3 = NULL;
      unsigned int campo4 = 0;
      int okAN = obtencion_datos(nombre, 1, &campo1);
      int okAA = obtencion_datos(apellido, 2, &campo2);
      int okAT = obtencion_datos(telefono, 3, &campo3);
      int okAE = obtencion_datos(edadC, 4, NULL);
      if (okAN + okAA + okAT + okAE != 0)
        printf
            ("Hay una cadena erronea ingresada, sera tomada como NULL/Vacio...\n");
      if (okAE == 0) {
        campo4 = atoi(edadC);
        printf("-%s-%s-%s-%u\n", campo1, campo2, campo3, campo4);
        AND_OR(tabla, 0, campo1, campo2, campo3, &campo4);
      }
      else {
        printf("-%s-%s-%s-%u\n", campo1, campo2, campo3, campo4);
        AND_OR(tabla, 0, campo1, campo2, campo3, NULL);
      }
      break;
    case 10:
      printf("OR\n");
      char *campoO1 = NULL;
      char *campoO2 = NULL;
      char *campoO3 = NULL;
      unsigned int campoO4 = 0;
      int okON = obtencion_datos(nombre, 1, &campoO1);
      int okOA = obtencion_datos(apellido, 2, &campoO2);
      int okOT = obtencion_datos(telefono, 3, &campoO3);
      int okOE = obtencion_datos(edadC, 4, NULL);
      if (okON + okOA + okOT + okOE != 0)
        printf
            ("Hay una cadena erronea ingresada, sera tomada como NULL/Vacio...\n");
      if (okOE == 0) {
        campoO4 = atoi(edadC);
        printf("-%s-%s-%s-%u\n", campoO1, campoO2, campoO3, campoO4);
        AND_OR(tabla, 1, campoO1, campoO2, campoO3, &campoO4);
      }
      else {
        printf("-%s-%s-%s-%u\n", campoO1, campoO2, campoO3, campoO4);
        AND_OR(tabla, 1, campoO1, campoO2, campoO3, NULL);
      }
      break;
    case 11:
      printf("Guardar Ordenado...\n");
      int gOP = obtencion_datos(ordenar, 6, NULL);
      int dirOkG = obtencion_datos(directorio, 5, NULL);
      if (gOP + dirOkG != 0)
        printf("Parametro Erroneo o error en el path de salida...\n");
      else {
        char *mode = "w";
        FILE * archivo = fopen_mkdir(directorio, mode);
        if (archivo == NULL)
          printf("Error en la creacion del directorio y archivo...\n");
        else {
          ordenar_parametro(tabla, ordenar, archivo);
          printf("Guardado\n");
          fclose(archivo);
        }
      }
      break;
    case 12:
      printf("Problema de la suma...\n");
      int sumaEdad = 0;
      printf("Insertar un numero para buscar edad como suma:\n");
      int okDP = obtencion_datos(edadC, 4, NULL);
      if (okDP == 0 && sscanf(edadC, "%i", &sumaEdad) == 1) {
        suma_edad(tabla,tabla->numElems, sumaEdad);
      }
      else
        printf("No ingreso un numero\n");
      break;
    case 13:
      printf("Saliendo...\n");
      break;
    default:
      printf("ERROR\n");
    }
  }
  pila_destruir(Deshacer, freeNNodo);
  pila_destruir(Rehacer, freeNNodo);
}


