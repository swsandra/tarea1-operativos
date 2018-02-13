#ifndef SIMULACION_H
#define SIMULACION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaordenada.h"
#include "cola.h"
#include "pila.h"
#include "lectura_escritura.h"


void simulacion(int *opciones, char* archivo_entrada, char *log){
	//Estructura para elementos en espera de la banda y del embolsado
	//modalidad		nro carritos	max productos	capacidad banda transportadora	vel cajera	vel embolsado	tiem facturacion	capacidad max area embolsado	capacadidad max bolsa
	int modalidad, carritos, max_productos, cc_banda, v_cajera, v_embolsado, t_fact, cc_embolsado, cc_bolsa;
	modalidad=*(opciones);
	carritos=*(opciones+1);
	max_productos=*(opciones+2);
	cc_banda=*(opciones+3);
	v_cajera=*(opciones+4);
	v_embolsado=*(opciones+5);
	t_fact=*(opciones+6);
	cc_embolsado=*(opciones+7);
	cc_bolsa=*(opciones+8);

	//Generamos los carritos
	lista_t* total_carritos[carritos];
	//Inicializamos las listas
	int i,j;
	for(i=0;i<carritos;i++){
		total_carritos[i]=crearLista();
	}
	//Carga lista con el inventario del archivo
	lista_t *inventario = leerArchivo(archivo_entrada);

	srand(time(NULL));
	int tam_carrito, compra;
	nodo_t *nodo;
	for(i=0;i<carritos;i++){
		tam_carrito=(rand()%max_productos)+1; //Para asegurarnos que no tengamos un carrito con 0 compras
		//printf("Carrito %d\n",i);
		for(j=0;j<tam_carrito;j++){
			//Generamos un nro random del tamano del inventario para 
			compra=rand()%(inventario->num_elem);
			//Lo buscamos en la lista del inventario
			nodo=buscarNodo(inventario,compra);
			//Creamos el nodo con los mismos valores
			nodo_t *nuevo=crearNodo(nodo->elem.nombre,nodo->elem.cc,nodo->elem.total);
			//Lo agregamos a la lista del carrito
			agregarNodo(total_carritos[i],nuevo);
		}
		//imprimirLista(total_carritos[i]);
	}

	//Modalidad interactiva
	if(modalidad==1){
		for(i=0;i<carritos;i++){
			printf("Presione Enter para iniciar la simulación del carrito %d...\n",i);
			char c = getchar();
			cola_t *banda=crearCola();
			pila_t *area_embolsado=crearPila();
			bolsas_t *bolsas=crearBolsas();
			int elementos_banda=0; //en la banda
			int tiempo_cajera, tiempo_embolsador; //tiempos que han pasado mientras totalizan o abren una bolsa
			int elementos_embolsado=0; //en el area de embolsado
			//Imprimir lo pedido
			printf("Elementos en el carrito %d:\n",i);
			imprimirLista(total_carritos[i]);
			printf("Elementos en la banda transportadora:\n");
			imprimirCola(banda);
			printf("Elementos en el área de embolsado: \n");
			imprimirPila(area_embolsado);
			printf("Elementos embolsados: \n");
			imprimirBolsas(bolsas);

			//Llenamos la banda transportadora hasta su capacidad la primera vez
			nodo_t *actual=(nodo_t*)malloc(sizeof(nodo_t));
			j=0;
			while(elementos_banda<cc_banda){
				actual=buscarNodo(total_carritos[i],j);
				if((elementos_banda+actual->elem.cc) > cc_banda){//No se agregan mas elementos
					break;
				}else{
					actual=eliminarNodo(total_carritos[i]);
					encolar(banda,actual);
					elementos_banda=elementos_banda+(actual->elem.cc);
				}				
			}
			int instante=0;
			bool cajera_totaliza=false; //true si esta totalizando un elemento
			bool bolsa_abierta=false; //si se abre una bolsa
			int t_abrir_bolsa=v_embolsado;
			int capacidad_bolsa_actual=0;
			nodo_t* elem_totalizando, elem_grande, elem_bolsa;
			cola_t *espera_banda=crearCola();
			cola_t *espera_embolsado=crearCola();
			int facturacion=t_fact;
			while(c=='\n'){
				printf("Instante %d\n",i);
				//Se debe ver que todo este vacio y que no se este totalizando ni embolsando nada
				if(estaVaciaLista(total_carritos[i]) && estaVaciaCola(banda) && estaVaciaPila(area_embolsado) && !bolsa_abierta && facturacion==0){
					printf("Fin de la simulación.\n");
					break;
				}
				//Vemos si hay elementos en el carrito para colocar en la banda
				if(!estaVaciaLista(total_carritos[i])){
					j=0;
					while(elementos_banda<cc_banda){
						actual=buscarNodo(total_carritos[i],j);
						if((elementos_banda+actual->elem.cc) > cc_banda){//No se agregan mas elementos
							break;
						}else{
							actual=eliminarNodo(total_carritos[i]);
							encolar(banda,actual);
							elementos_banda=elementos_banda+(actual->elem.cc);
						}				
					}
				}

				//Cajera realiza la totalizacion
				if(cajera_totaliza){
					elem_totalizando->elem.total--;
				}

				//Si la cajera termina de totalizar, pasa al embolsado
				if(elem_totalizando->elem.total==0){
					if((elementos_embolsado+elem_totalizando->elem.cc)<=cc_embolsado){
						push(area_embolsado,elem_totalizando);
						elementos_embolsado=elementos_embolsado+elem_totalizando->elem.cc;
					}else{
						encolar(espera_embolsado,elem_totalizando);
					}
					cajera_totaliza=false;
				}

				//Si la banda no esta vacia y la cajera no esta totalizando
				//Si empieza a totalizar algo, debe eliminarlo de la banda y restarle a elementos_banda
				if(!estaVaciaCola(banda) && !cajera_totaliza){
					elem_totalizando=desencolar(banda);
					cajera_totaliza=true;
					elementos_banda=elementos_banda - elem_totalizando->elem.cc ;
				}
				
				//Si el carrito no esta vacio y la banda si
				if(!estaVaciaLista(total_carritos[i]) && estaVaciaCola(banda)){
					elem_grande=buscarNodo(total_carritos[i],0);
					if(elem_grande->elem.cc>cc_banda){//El proximo del carrito es mas grande que la banda
						//Lo coloco en espera
						elem_grande=eliminarNodo(total_carritos[i]);
						encolar(espera_banda,elem_grande);
					}
				}

				//Si la cajera no esta totalizando y hay elementos en espera
				if(!cajera_totaliza && !estaVaciaCola(espera_banda)){
					elem_totalizando=desencolar(espera_banda);
					cajera_totaliza=true;
				}
				
				//Si no hay elementos en la banda y la cajera tampoco esta totalizando->factura--
				if(estaVaciaCola(banda) && !cajera_totaliza){
					facturacion--;
				}

				//Si hay elementos para embolsar y la bolsa no esta abierta
				if(!estaVaciaPila(area_embolsado) && !bolsa_abierta){
					t_abrir_bolsa--;
				}

				//Si se puede abrir una bolsa
				if(t_abrir_bolsa==0){
					bolsa_abierta=true;
					t_abrir_bolsa=v_embolsado;
					capacidad_bolsa_actual=0;
				}

				//Si se agregan elementos a una bolsa, revisar los que estan en espera del area de embolsado
				//agregar los que se puedan
				if(bolsa_abierta){
					//Creamos una lista
					lista_t* bolsita=crearLista();
					//Creamos un nodo_lista_t para una nueva bolsa (lista)
					nodo_lista_t* bolsa_nueva=crearNodoLista();
					nodo_t *siguiente;
					while(!estaVaciaPila(area_embolsado) && capacidad_bolsa_actual<cc_bolsa){
						siguiente=peek(area_embolsado);
						//Si es asi, se agrega a una bolsa solo hasta que se encuentre un elemento de menor cc que la capacidad de la bolsa			
						if(siguiente->elem.cc>cc_bolsa){
							do{
								lista_t* bolsita_2=crearLista();
								siguiente=pop(area_embolsado);
								elementos_embolsado=elementos_embolsado-(siguiente->elem.cc);
								agregarNodo(bolsita_2,siguiente);
								nodo_lista_t *bolsa_nueva_2=crearNodoLista(bolsita_2);
								agregarNodoLista(bolsas,bolsa_nueva_2);
								siguiente=peek(area_embolsado);
							}while(siguiente->elem.cc>cc_bolsa && !estaVaciaPila(area_embolsado));
						}	//mientras que el elemento sea mas grande y la pila no este vacia
						else{//ya tengo el peek
							if((capacidad_bolsa_actual+siguiente->elem.cc)>cc_bolsa){
								break;
							}else{
								capacidad_bolsa_actual=capacidad_bolsa_actual+siguiente->elem.cc;
								siguiente=pop(area_embolsado);
								elementos_embolsado=elementos_embolsado-(siguiente->elem.cc);
								agregarNodo(bolsita,siguiente);
							}
						}
					}

					agregarNodoLista(bolsas,bolsa_nueva);
					//Cerramos la bolsa, cambiamos la bolsa actual
					bolsa_abierta=false;
					capacidad_bolsa_actual=0;
					//Actualizamos el area de embolsado con los que estaban en espera
					
					if(!estaVaciaCola(espera_embolsado)){
						nodo_t *nodo;
						while(elementos_embolsado<cc_embolsado){
							nodo=peekCola(espera_embolsado);
							if(elementos_embolsado+(nodo->elem.cc)>cc_embolsado){
								break;
							}else{
								nodo=desencolar(espera_embolsado);
								push(area_embolsado,nodo);
								elementos_embolsado=elementos_embolsado+(nodo->elem.cc);
							}
						}
					}
				}

				printf("Elementos en el carrito %d:\n",i);
				imprimirLista(total_carritos[i]);
				printf("Elementos en la banda transportadora:\n");
				imprimirCola(banda);
				printf("Elementos en el área de embolsado: \n");
				imprimirPila(area_embolsado);
				printf("Elementos embolsados: \n");
				imprimirBolsas(bolsas);
				printf("Presione Enter.\n");
				do{
					fflush(stdin);
					c=getchar();
				}while(c!='\n');
				instante++;
				if(facturacion==0){
					printf("Se ha facturado el carrito %d\n",i);
					break;
				}
			}
		}
		//!!!!!!!!!!!HAY QUE LIBERAR EL ESPACIO CADA VEZ QUE SE ELIMINA ALGO
		//!!!Ver en que parte se tiene que liberar cada cosa
		//Liberar el espacio del inventario
		//Liberar el espacio de los carritos
		//Liberar todas las colas y pilas, tambien las de espera

	}else if(modalidad==2){//automatica
		int tiempo_total;


	}


	return;
}

#endif