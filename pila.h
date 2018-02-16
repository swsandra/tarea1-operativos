#ifndef PILA_H
#define PILA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct pila{

	nodo_t *top;

}pila_t;

pila_t* crearPila(){
	pila_t *pilaNueva = (pila_t*)malloc(sizeof(pila_t));
	pilaNueva->top=NULL;
	return pilaNueva;
}

void liberarEspacioPila(pila_t *pila){
	free(pila);
	return;
}

bool estaVaciaPila(pila_t *pila){
	if(pila->top==NULL) return true;
	else return false;
}

//Agrega y elimina al principio
void push(pila_t *pilaActual, nodo_t *nodo){
	nodo_t *p = pilaActual->top;
	if(estaVaciaPila(pilaActual)){//Si la pila inicialmente esta vacia
		pilaActual->top=nodo;
	}else{
		nodo->next=p;
		pilaActual->top=nodo;
	}
	return;
}

nodo_t* pop(pila_t *pilaActual){
	if(estaVaciaPila(pilaActual)==false){
		nodo_t *p = pilaActual->top;
		pilaActual->top=p->next;
		p->next=NULL;
		return p;
	}else{
		return NULL;
	}
}

//Para ver el top de la pila
nodo_t* peek(pila_t *pilaActual){
	return pilaActual->top;
}

//Imprime la pila desde el top hasta el fondo
void imprimirPila(pila_t *pila){
	nodo_t *p = pila->top;
	if(estaVaciaPila(pila)) printf("La pila está vacía.\n");
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