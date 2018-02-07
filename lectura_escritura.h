#ifndef LECTURA_ESCRITURA_H
#define LECTURA_ESCRITURA_H

#include <stdio.h>
#include <stdlib.h>
#include "listaordenada.h"

//Si cuando lee el archivo retorna una lista NULL, he didnt make it
lista_t* leerArchivo(char *nombreArchivo){
	FILE* archivo=NULL;
	archivo=fopen(nombreArchivo,"r");
	if(archivo==NULL) return NULL;
	//Lee linea por linea y divide en 3 el string
	char *linea=(char*)malloc(100*sizeof(char));
	char *nombre;
	int tamano;
	int totaliz;
	//int termino=0;
	lista_t *lista = crearLista();
	//nodo_t *nodoNuevo=(nodo_t*)malloc(sizeof(nodo_t));
	//termino=fgets(archivo,60,linea);
	linea=fgets(linea, 100, archivo);

	while(linea!=NULL){
		//printf("%s %d %d \n", nombre,*tamano,*totaliz);
		//Creamos el nodo y lo agregamos a la lista
		//nodo_t *nodoNuevo = crearNodo(nombre,(int)tamano,(int)totaliz);
		//agregarNodo(lista,nodoNuevo);
		printf("%s\n", linea);
		linea=fgets(linea, 100, archivo);
		
	}

	fclose(archivo);
	return lista;

}

char* splitStringNodo(char *linea){
	const char s[2] = "\t";
	char *token;
	token = strtok(linea, s);
	if (token[strlen(token)-1]=="\n"){

	}
	return token;
}

#endif