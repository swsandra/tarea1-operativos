#ifndef LISTAORDENADA_H
#define LISTAORDENADA_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Estructuras
typedef struct nodo{

	char *nombre;
	int tamano;
	int totalizacion;
	struct nodo *next;

}nodo_t;

typedef struct listaordenada{
	nodo_t *cabeza;
}lista_t;

//Funciones
//Crear un nodo
nodo_t* crearNodo(char* nombre, int tamano, int totalizacion){
	nodo_t *nodoNuevo=(nodo_t*)malloc(sizeof(nodo_t));
	if(!nodoNuevo) return NULL;

	nodoNuevo->nombre=nombre;
	nodoNuevo->tamano=tamano;
	nodoNuevo->totalizacion=totalizacion;
	nodoNuevo->next=NULL;
	return nodoNuevo;
}

//Eliminar un nodo
//!!!!!!!!!!!! chama queria hacer un assert de esto pero no se como hacerlo :(
void liberarEspacioNodo(nodo_t *nodo){
	free(nodo);
	return;
}

bool estaVaciaLista(lista_t *lista){
	if(lista->cabeza==NULL) return true;
	else return false;
}

lista_t* crearLista(){
	lista_t *lista=(lista_t*)malloc(sizeof(lista_t));
	if(!lista) return NULL;
	lista->cabeza=(nodo_t*)malloc(sizeof(nodo_t));
	lista->cabeza=NULL;
	return lista;
}


//Agregar en orden
void agregarNodo(lista_t *lista, nodo_t *nuevo){
	nodo_t *p = lista->cabeza;
	nodo_t *anterior=NULL;
	//if(p!=NULL) printf("cabeza %d\n", p->tamano);
	if(estaVaciaLista(lista)){ //Si la lista esta vacia
		lista->cabeza=nuevo;
	}else{
		if(p->tamano > nuevo->tamano){//Si es mas pequeno que el primero
			nuevo->next=p;
			lista->cabeza=nuevo;
		}else if(p->tamano <= nuevo->tamano){
			do{
				if(nuevo->tamano > p->tamano){
					//if(anterior!=NULL) printf("%d\n", anterior->tamano);
					//if(nuevo->next!=NULL)printf("1nuevo->next %d\n", nuevo->next->tamano);
					if(p->next!=NULL) nuevo->next=p->next;
					else nuevo->next=NULL;
					//printf("2nuevo->next %d\n", nuevo->next->tamano);
					//printf("1p->next %d\n", p->next->tamano);
					p->next=nuevo;
					//printf("2p->next %d\n", p->next->tamano);
					if(anterior!=NULL) anterior->next=p;
					anterior=p;
					//p=p->next;
					if(nuevo->next!=NULL) p=nuevo->next;
					else return;
					//printf("anterior %d nuevo %d siguiente/comparador %d\n", anterior->tamano, nuevo->tamano, p->tamano);
				}else if(nuevo->tamano == p->tamano){
					//printf("nuevo %d\n", nuevo->tamano);
					//printf("p %d\n", p->tamano);
					//printf("Hola\n");
					if(anterior!=NULL) anterior->next=p;
					nuevo->next=p->next;
					p->next=nuevo;
					return;
				}
				else{
					p=p->next;
				}
				//printf("p %d\n", p->tamano);
				//printf("nuevo %d\n", nuevo->tamano);
			}while (p!=NULL);
		}
	}
	return;
}

//Eliminar el primero. Aqui hay que asegurarse que la lista no este vacia
nodo_t* eliminarNodo(lista_t *lista){
	if(estaVaciaLista(lista)==false){
		nodo_t *p = lista->cabeza;
		lista->cabeza=p->next;
		return p; //retorna NULL si la lista es vacia
	}else return NULL;
}

//Imprimir de lista
void imprimirLista(lista_t *lista){
	nodo_t *p = lista->cabeza;
	if(estaVaciaLista(lista)) printf("La lista está vacía.\n");
	else{
		do{	
			printf("%s	%d	%d\n", p->nombre,p->tamano,p->totalizacion);
			p=p->next;
		}while(p!=NULL);
	}
	return;
}

#endif