#ifndef LISTAORDENADA_H
#define LISTAORDENADA_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Estructuras

typedef struct elemento{

	int cc;
	int total;
	char nombre[1000];

}elem_t;

typedef struct nodo{

	elem_t elem;
	struct nodo *next;

}nodo_t;

typedef struct listaordenada{
	
	nodo_t *cabeza;
	int num_elem;

}lista_t;

//Funciones
//Crear un nodo
nodo_t* crearNodo(char nombre[], int tamano, int total){
	nodo_t *nodoNuevo=(nodo_t*)malloc(sizeof(nodo_t));
	if(!nodoNuevo) return NULL;
	//char *nom = nombre;
	strcpy(nodoNuevo->elem.nombre,nombre);
	//printf("%s\n", nom);
	//nodoNuevo->elem.nombre=nom;
	nodoNuevo->elem.cc=tamano;
	nodoNuevo->elem.total=total;
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


//Imprimir de lista
void imprimirLista(lista_t *lista){
	nodo_t *p = lista->cabeza;
	if(estaVaciaLista(lista)) printf("La lista está vacía.\n");
	else{
		do{
			printf("%s	%d	%d\n", p->elem.nombre,p->elem.cc,p->elem.total);
			p=p->next;
		}while(p!=NULL);
	}
	return;
}

//Agregar en orden
void agregarNodo(lista_t *lista, nodo_t *nuevo){
	nodo_t *p = lista->cabeza;
	nodo_t *anterior=NULL;
	lista->num_elem++;
	//printf("%s %d %d\n", nuevo->nombre, nuevo->tamano, nuevo->total);
	if(estaVaciaLista(lista)){ //Si la lista esta vacia
		lista->cabeza=nuevo;
	}else{
		if(p->elem.cc > nuevo->elem.cc){//Si es mas pequeno que el primero
			nuevo->next=p;
			lista->cabeza=nuevo;
		}else if(p->elem.cc <= nuevo->elem.cc){
			do{
				//printf("comp\n");
				//printf("%s %d %d\n", nuevo->nombre, nuevo->tamano, nuevo->total);
				if(nuevo->elem.cc > p->elem.cc){
					if(p->next!=NULL) nuevo->next=p->next;
					else nuevo->next=NULL;
					p->next=nuevo;
					if(anterior!=NULL) anterior->next=p;
					anterior=p;
					if(nuevo->next!=NULL) p=nuevo->next;
					else return;
				}else if(nuevo->elem.cc == p->elem.cc){
					if(anterior!=NULL) anterior->next=p;
					nuevo->next=p->next;
					p->next=nuevo;
					return;
				}
				else{
					p=p->next;
				}
			}while (p!=NULL);
		}
	}

	return;
}

//Eliminar el primero. Aqui hay que asegurarse que la lista no este vacia
nodo_t* eliminarNodo(lista_t *lista){
	lista->num_elem--;
	if(estaVaciaLista(lista)==false){
		nodo_t *p = lista->cabeza;
		lista->cabeza=p->next;
		return p; //retorna NULL si la lista es vacia
	}else return NULL;
}


#endif