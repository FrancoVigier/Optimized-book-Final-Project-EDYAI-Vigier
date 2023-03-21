#ifndef INTERPRETE_H_INCLUDED
#define INTERPRETE_H_INCLUDED
#include "../../Estructuras-Generales/Hash/hash.h"
#include "../../Estructuras-Puntuales/Contacto/contacto.h"
#include "../../Estructuras-Puntuales/Encapsulador/nthnodo.h"
#include "../../Estructuras-Generales/Anexo/utils.h"
#include "../../Estructuras-Generales/DList/LSE.h"
#include "../../Estructuras-Generales/Pila/pila.h"

#include "../../Algoritmia/AND-OR/AO.h"
#include "../../Algoritmia/Guardar-Ordenado/GO.h"
#include "../../Algoritmia/Suma-Prog-Din/greedy.h"
#include "../../Algoritmia/Deshacer-Rehacer/DR.h"
#include "../../Core/Procesamiento/procesamiento.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/stat.h>

#define N_PILA 5  /// TOPE DE D/R OPERACIONES

/// Funcion que desarrolla el interprete
void interprete(TablaHash);

/// Menu de opcionesvoid mostrar_prompt();
#endif                          // INTERPRETE_H_INCLUDED
