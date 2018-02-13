#ifndef LECTURA_ESCRITURA_H
#define LECTURA_ESCRITURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaordenada.h"

//Cuenta el numero de lineas de un archivo
/*int numeroLineas(char *nombreArchivo){
	FILE* archivo=NULL;
	archivo=fopen(nombreArchivo,"r");
	if(archivo==NULL){
		printf("Error al abrir el archivo. \n");
		exit(1);
	}

	int lineas=0;
	char temp[1000];

	while (fgets(temp, sizeof(temp), archivo) != NULL){
		lineas++;
	}

	fclose(archivo);
	return lineas;
}*/

lista_t* leerArchivo(char *nombreArchivo){
	FILE* archivo=NULL;
	archivo=fopen(nombreArchivo,"r");
	if(archivo==NULL){
		printf("Error al abrir el archivo. \n");
		exit(1);
	}
	lista_t *lista = crearLista();
	
	//Leemos por linea y hacemos split
	char linea[1000];
	while(fgets(linea,sizeof(linea),archivo)!=NULL){
		char *p = strtok(linea,"\t");
		char *val[3];
		int i=0;
		while(p!=NULL){
			val[i]=p;
			p=strtok(NULL,"\t");
			i++;
		}
		int tamano=atoi(val[1]);
		int total=atoi(val[2]);
		//Creamos un nodo
		nodo_t *nodo = crearNodo(val[0],tamano,total);
		agregarNodo(lista,nodo);
	}

	fclose(archivo);
	return lista;
}

void escribirLinea(char *nombreArchivo, char *linea){
	FILE *archivo;
	archivo=fopen(nombreArchivo,"a");
	
	if(archivo==NULL){
		printf("Error al escribir en el archivo.\n");
		exit(1);
	}
	fprintf(archivo, "%s\n",linea);
	fclose(archivo);
	return;
}

#endif