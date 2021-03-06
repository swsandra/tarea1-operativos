#ifndef COLA_H
#define COLA_H
#include <stdio.h>
#include <stdlib.h>

//Estructuras
typedef struct cola{
	nodo_t *cabeza;
	nodo_t *cola;
}cola_t;

//Funciones
cola_t* crearCola(){
	cola_t *colaNueva = (cola_t*)malloc(sizeof(cola_t));
	colaNueva->cabeza=NULL;
	colaNueva->cola=NULL; 
	return colaNueva;
}

void liberarEspacioCola(cola_t* cola){
	free(cola);
	return;
}

bool estaVaciaCola(cola_t *cola){
	if(cola->cabeza==NULL) return true;
	else return false;
}

void encolar(cola_t *colaActual, nodo_t *nodo){ //al final
	nodo_t *p = colaActual->cola;
	//printf("Hola\n");
	if(estaVaciaCola(colaActual)){//Si la cola inicialmente esta vacia
		colaActual->cabeza=nodo;
		colaActual->cola=nodo;
	}else{
		p->next=nodo;
		colaActual->cola=nodo;
	}
	return;
}

nodo_t* desencolar(cola_t *colaActual){ //quito el primero
	if(estaVaciaCola(colaActual)==false){
		nodo_t *p = colaActual->cabeza;
		colaActual->cabeza=p->next;
		p->next=NULL;
		return p;
	}else{
		return NULL;
	}
}

nodo_t* peekCola(cola_t *cola){
	return cola->cabeza;
}

void imprimirCola(cola_t *cola){
	nodo_t *p = cola->cabeza;
	if(estaVaciaCola(cola)) printf("La cola está vacía.\n");
	else{
		do{	
			//printf("%s	%d	%d\n", p->elem.nombre,p->elem.cc,p->elem.total);
			printf("%s\n", p->elem.nombre);
			p=p->next;
		}while(p!=NULL);
	}
	return;
}

#endif 