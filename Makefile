OBJS = main.o LSE.o pila.o hash.o utils.o contacto.o nthnodo.o AO.o DR.o GO.o MS.o greedy.o procesamiento.o interprete.o
SOURCE = main.c ./Estructuras-Generales/DList/LSE.c ./Estructuras-Generales/Pila/pila.c ./Estructuras-Generales/Hash/hash.c ./Estructuras-Generales/Anexo/utils.c ./Estructuras-Puntuales/Contacto/contacto.c ./Estructuras-Puntuales/Encapsulador/nthnodo.c ./Algoritmia/AND-OR/AO.c ./Algoritmia/Deshacer-Rehacer/DR.c ./Algoritmia/Guardar-Ordenado/GO.c ./Algoritmia/Merge-Sort/MS.c ./Algoritmia/Suma-Prog-Din/greedy.c ./Core/Procesamiento/procesamiento.c ./Core/Interprete/interprete.c
HEADER = ./Estructuras-Generales/DList/LSE.h ./Estructuras-Generales/Pila/pila.h ./Estructuras-Generales/Hash/hash.h ./Estructuras-Generales/Anexo/utils.h ./Estructuras-Puntuales/Contacto/contacto.h ./Estructuras-Puntuales/Encapsulador/nthnodo.h ./Algoritmia/AND-OR/AO.h ./Algoritmia/Deshacer-Rehacer/DR.h ./Algoritmia/Guardar-Ordenado/GO.h ./Algoritmia/Merge-Sort/MS.h ./Algoritmia/Suma-Prog-Din/greedy.h ./Core/Procesamiento/procesamiento.h ./Core/Interprete/interprete.h
CC = gcc
FLAGS = -c -Wall -Wextra -Werror -std=c99 -g
OUT	= Interprete

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.c
	$(CC) $(FLAGS) main.c 

LSE.o: ./Estructuras-Generales/DList/LSE.c
	$(CC) $(FLAGS) ./Estructuras-Generales/DList/LSE.c

pila.o: ./Estructuras-Generales/Pila/pila.c
	$(CC) $(FLAGS) ./Estructuras-Generales/Pila/pila.c

hash.o: ./Estructuras-Generales/Hash/hash.c 
	$(CC) $(FLAGS) ./Estructuras-Generales/Hash/hash.c 

utils.o: ./Estructuras-Generales/Anexo/utils.c 
	$(CC) $(FLAGS) ./Estructuras-Generales/Anexo/utils.c 

contacto.o: ./Estructuras-Puntuales/Contacto/contacto.c
	$(CC) $(FLAGS) ./Estructuras-Puntuales/Contacto/contacto.c

nthnodo.o: ./Estructuras-Puntuales/Encapsulador/nthnodo.c
	$(CC) $(FLAGS) ./Estructuras-Puntuales/Encapsulador/nthnodo.c 

AO.o: ./Algoritmia/AND-OR/AO.c
	$(CC) $(FLAGS) ./Algoritmia/AND-OR/AO.c

DR.o: ./Algoritmia/Deshacer-Rehacer/DR.c
	$(CC) $(FLAGS) ./Algoritmia/Deshacer-Rehacer/DR.c

GO.o: ./Algoritmia/Guardar-Ordenado/GO.c 
	$(CC) $(FLAGS) ./Algoritmia/Guardar-Ordenado/GO.c 

MS.o: ./Algoritmia/Merge-Sort/MS.c
	$(CC) $(FLAGS) ./Algoritmia/Merge-Sort/MS.c

greedy.o: ./Algoritmia/Suma-Prog-Din/greedy.c
	$(CC) $(FLAGS) ./Algoritmia/Suma-Prog-Din/greedy.c

procesamiento.o: ./Core/Procesamiento/procesamiento.c
	$(CC) $(FLAGS) ./Core/Procesamiento/procesamiento.c 

interprete.o: ./Core/Interprete/interprete.c
	$(CC) $(FLAGS) ./Core/Interprete/interprete.c 

clean:
	rm -f $(OBJS) $(OUT)