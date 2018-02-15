#include "listaordenada.h"
#include "cola.h"
#include "pila.h"
#include "lectura_escritura.h"
#include "modificar_simulacion.h"
//#include "simulacion.h"

int main(int argc, char *argv[]){

	//Pruebas escritura archivos
	//FILE *archivo;
	//archivo=fopen("log.txt","w");
	//escribirLinea("log.txt","Hola, me mato");
	//fclose(archivo);

	//Prueba bolsas
	/*char *n1 = "Nombre1";
	char *n2 = "Nombre2";
	char *n3 = "Nombre3";
	char *n4 = "Nombre4";
	nodo_t *nodo11=crearNodo(n1,1,1);
	nodo_t *nodo21=crearNodo(n2,2,2);
	nodo_t *nodo31=crearNodo(n3,3,3);
	nodo_t *nodo41=crearNodo(n4,4,4);

	nodo_t *nodo12=crearNodo(n1,1,1);
	nodo_t *nodo22=crearNodo(n2,2,2);
	nodo_t *nodo32=crearNodo(n3,3,3);

	nodo_t *nodo13=crearNodo(n1,1,1);
	nodo_t *nodo23=crearNodo(n2,2,2);
	nodo_t *nodo43=crearNodo(n4,4,4);
	
	printf("Creamos listas\n");
	lista_t *lista=crearLista();
	lista_t *lista1=crearLista();
	lista_t *lista2=crearLista();
	
	agregarNodo(lista,nodo11);
	agregarNodo(lista,nodo21);
	agregarNodo(lista,nodo31);
	agregarNodo(lista,nodo41);

	agregarNodo(lista1,nodo12);
	agregarNodo(lista1,nodo22);
	agregarNodo(lista1,nodo32);
	
	agregarNodo(lista2,nodo13);
	agregarNodo(lista2,nodo23);
	agregarNodo(lista2,nodo43);

	printf("Creamos nodos_listas\n");
	nodo_lista_t *nodol1 = crearNodoLista(lista);
	nodo_lista_t *nodol2 = crearNodoLista(lista1);
	nodo_lista_t *nodol3 = crearNodoLista(lista2);*/

	/*printf("lista\n");
	imprimirLista(nodol1->lista);
	printf("lista1\n");
	imprimirLista(nodol2->lista);
	printf("lista2\n");
	imprimirLista(nodol3->lista);*/

/*	printf("Creamos bolsas\n");
	bolsas_t *bolsas=crearBolsas();
	printf("Agregamos los nodos_listas\n");
	agregarBolsa(bolsas,nodol1);
	agregarBolsa(bolsas,nodol2);
	agregarBolsa(bolsas,nodol3);
	//Imprimimos
	printf("Imprimimos bolsas\n");
	imprimirBolsas(bolsas);*/


	//Prueba lectura
	//MATAME
	/*char *archivo = "Entrada2.txt";
	lista_t *lista = leerArchivo(archivo);
	imprimirLista(lista);
	printf("%d\n", lista->num_elem);
	//Buscamos cada elemento
	nodo_t *p;
	for(int i=0;i<lista->num_elem;i++){
		p=buscarNodo(lista,i);
		printf("elem %d: %s	%d	%d\n",i, p->elem.nombre,p->elem.cc,p->elem.total);
	}*/

	//Prueba pila

	/*pila_t *pila = crearPila();
	imprimirPila(pila);
	printf("push\n");
	push(pila, nodo1);
	imprimirPila(pila);
	printf("push\n");
	push(pila, nodo2);
	imprimirPila(pila);
	printf("push\n");
	push(pila, nodo3);
	imprimirPila(pila);
	printf("push\n");
	push(pila, nodo4);
	imprimirPila(pila);

	printf("Hacemos pop a todos\n");
	nodo_t *nodoEliminado=(nodo_t*)malloc(sizeof(nodo_t));
	nodoEliminado = pop(pila);
	liberarEspacioNodo(nodoEliminado);
	imprimirPila(pila);
	printf("Otro nodo\n");
	nodoEliminado = pop(pila);
	liberarEspacioNodo(nodoEliminado);
	imprimirPila(pila);
	printf("Otro nodo\n");
	nodoEliminado = pop(pila);
	liberarEspacioNodo(nodoEliminado);
	imprimirPila(pila);
	printf("Otro nodo\n");
	nodoEliminado = pop(pila);
	liberarEspacioNodo(nodoEliminado);
	imprimirPila(pila);
	nodoEliminado = pop(pila);
	liberarEspacioNodo(nodoEliminado);
	imprimirPila(pila);*/


	//Prueba lista
	
	/*lista_t *lista=crearLista();
	printf("Agregamos los nodos e imprimimos la lista\n");
	agregarNodo(lista,nodo1);
	//imprimirLista(lista);
	agregarNodo(lista,nodo2);
	//imprimirLista(lista);
	agregarNodo(lista,nodo3);
	//imprimirLista(lista);
	agregarNodo(lista,nodo4);
	imprimirLista(lista);
	printf("Eliminamos un nodo, liberamos espacio e imprimimos\n");
	nodo_t *nodoEliminado=(nodo_t*)malloc(sizeof(nodo_t));
	nodoEliminado = eliminarNodo(lista);
	liberarEspacioNodo(nodoEliminado);
	imprimirLista(lista);
	printf("Otro nodo\n");
	nodoEliminado = eliminarNodo(lista);
	liberarEspacioNodo(nodoEliminado);
	imprimirLista(lista);
	printf("Otro nodo\n");
	nodoEliminado = eliminarNodo(lista);
	liberarEspacioNodo(nodoEliminado);
	imprimirLista(lista);
	printf("Otro nodo\n");
	nodoEliminado = eliminarNodo(lista);
	liberarEspacioNodo(nodoEliminado);
	imprimirLista(lista);
	nodoEliminado = eliminarNodo(lista);*/


	//Prueba cola

	/*cola_t *cola=crearCola();
	imprimirCola(cola);
	printf("Encolamos los elementos e imprimimos la cola.\n");
	encolar(cola,nodo1);
	printf("Encolamos\n");
	imprimirCola(cola);
	encolar(cola,nodo2);
	printf("Encolamos\n");
	imprimirCola(cola);
	encolar(cola,nodo3);
	printf("Encolamos\n");
	imprimirCola(cola);
	encolar(cola,nodo4);
	printf("Encolamos\n");
	imprimirCola(cola);
	printf("Desencolamos todos\n");
	nodo_t *nodoEliminado=(nodo_t*)malloc(sizeof(nodo_t));
	nodoEliminado = desencolar(cola);
	liberarEspacioNodo(nodoEliminado);
	imprimirCola(cola);
	printf("Otro nodo\n");
	nodoEliminado = desencolar(cola);
	liberarEspacioNodo(nodoEliminado);
	imprimirCola(cola);
	printf("Otro nodo\n");
	nodoEliminado = desencolar(cola);
	liberarEspacioNodo(nodoEliminado);
	imprimirCola(cola);
	printf("Otro nodo\n");
	nodoEliminado = desencolar(cola);
	liberarEspacioNodo(nodoEliminado);
	imprimirCola(cola);
	nodoEliminado = desencolar(cola);
	liberarEspacioNodo(nodoEliminado);*/

	return 0;
}