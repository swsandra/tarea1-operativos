#ifndef LECTURA_ESCRITURA_H
#define LECTURA_ESCRITURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaordenada.h"

//Cuenta el numero de lineas de un archivo
int numeroLineas(char *nombreArchivo){
	FILE* archivo=NULL;
	archivo=fopen(nombreArchivo,"r");
	if(archivo==NULL){
		printf("Error al abrir el archivo. \n");
		exit(1);
	}

	int lineas=0;
	char temp[100];

	while (fgets(temp, sizeof(temp), archivo) != NULL){
		lineas++;
	}

	fclose(archivo);
	return lineas;
}

lista_t* leerArchivo(char *nombreArchivo){
	FILE* archivo=NULL;
	archivo=fopen(nombreArchivo,"r");
	if(archivo==NULL){
		printf("Error al abrir el archivo. \n");
		exit(1);
	}
	lista_t *lista = crearLista();
	
	//Leemos por linea y hacemos split
	char linea[100];
	while(fgets(linea,sizeof(linea),archivo)!=NULL){
		char *p = strtok(linea,"\t");
		char *val[3];
		int i=0;
		while(p!=NULL){
			val[i]=p;
			p=strtok(NULL,"\t");
			i++;
		}
		char *nombre=val[0];
		int tamano=atoi(val[1]);
		int total=atoi(val[2]);
		//Creamos un nodo
		nodo_t *nodo = crearNodo(nombre,tamano,total);
		//printf("%s %d %d\n", nodo->nombre, nodo->tamano, nodo->total);
		//Lo agregamos
		agregarNodo(lista,nodo);
		//imprimirLista(lista);
		/*printf("Nuevo\n");
		for (i = 0; i < 3; i++){
			printf("%s\n", val[i]);
		}*/
	}

	fclose(archivo);
	return lista;

}


/*lista_t* leerArchivo(char *nombreArchivo){
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
	int x=numeroLineas(nombreArchivo);
	//printf("Hola1\n");
	for(int i=0;i<x;i++){
		fscanf(archivo,"%s\t%d\t%d\n",tempNombre,&tamano,&totaliz);
		//Copiamos el string 
		//printf("fscanf		%s  %d  %d\n", tempNombre,tamano,totaliz);
		strcpy(nombre,tempNombre);
		//printf("1\n");
		nodo = crearNodo(nombre,tamano,totaliz);
		//printf("2\n");
		agregarNodo(lista,nodo);
		//printf("3\n");
		//printf("nodo		%s  %d  %d\n", nodo->nombre,nodo->tamano,nodo->total);

	}
	//printf("salio for\n");
	//imprimirLista(lista);
	fclose(archivo);
	return lista;

}

*/


#endif