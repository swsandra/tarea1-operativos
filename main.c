#include "listaordenada.h"
#include "cola.h"
#include "lectura_escritura.h"

int main(){

	/*char *n1 = "Nombre1";
	char *n2 = "Nombre2";
	char *n3 = "Nombre3";
	char *n4 = "Nombre4";
	int x,y;
	x=0;
	y=0;
	nodo_t *nodo1=crearNodo(n1,1,1);
	nodo_t *nodo2=crearNodo(n2,2,2);
	nodo_t *nodo3=crearNodo(n3,3,3);
	nodo_t *nodo4=crearNodo(n4,4,4);*/
	
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

	//Prueba lectura
	char *archivo = "Entrada1.txt";
	lista_t *lista = leerArchivo(archivo);
	imprimirLista(lista);

	return 0;
}