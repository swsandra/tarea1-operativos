#ifndef LECTURA_ESCRITURA_H
#define LECTURA_ESCRITURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaordenada.h"

//Si cuando lee el archivo retorna una lista NULL, he didnt make it
lista_t* leerArchivo(char *nombreArchivo){
	FILE* archivo=NULL;
	archivo=fopen(nombreArchivo,"r");
	if(archivo==NULL){
		printf("Error al abrir el archivo. \n");
		exit(1);
	}
	lista_t *lista = crearLista();
	char *nombre;
	char tempNombre[100];
	int tamano=0;
	int totaliz=0;
	nodo_t *nodo; 
	printf("Hola\n");
	while((fscanf(archivo,"%s\t%d\t%d\n",tempNombre,&tamano,&totaliz))==3){
		printf("Hola2\n");
		//Copiamos el string 
		strcpy(nombre,tempNombre);
		nodo = crearNodo(nombre,tamano,totaliz);
		agregarNodo(lista,nodo);
	}
	

	fclose(archivo);
	return lista;

}

/*char* splitStringNodo(char *linea){
	const char s[2] = "\t";
	char *token;
	token = strtok(linea, s);
	if (token[strlen(token)-1]=="\n"){
		token 

	}
	return token;
}*/

#endif