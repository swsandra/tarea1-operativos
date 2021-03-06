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
	int compras_por_carrito[carritos];
	for(i=0;i<carritos;i++){
		tam_carrito=(rand()%max_productos)+1; //Para asegurarnos que no tengamos un carrito con 0 compras
		compras_por_carrito[i]=tam_carrito;
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
	}

	//Modalidad interactiva
	if(modalidad==1){
		int tiempo_cliente[carritos];
		char c='\n';
		cola_t *banda=crearCola();
		pila_t *area_embolsado=crearPila();
		//bolsas_t *bolsas=crearBolsas();
		int elementos_banda=0; //en la banda
		int tiempo_cajera, tiempo_embolsador; //tiempos que han pasado mientras totalizan o abren una bolsa
		int elementos_embolsado=0; //en el area de embolsado
		cola_t *espera_banda=crearCola();
		cola_t *espera_embolsado=crearCola();
		pila_t *elementos_grandes_embolsado=crearPila();
		nodo_t *elem_totalizando=NULL;
		nodo_t *elem_grande=NULL;
		nodo_t *elem_bolsa=NULL;
		nodo_t *actual=NULL;
		nodo_t *grande=NULL;
		for(i=0;i<carritos;i++){
			bolsas_t *bolsas=crearBolsas();
			printf("Estado del carrito %d, banda transportadora y área de embolsado...\n",i);
			//Imprimir lo pedido
			printf("Elementos en el carrito %d:\n",i);
			imprimirLista(total_carritos[i]);
			printf("Elementos en la banda transportadora:\n");
			imprimirCola(banda);
			printf("Elementos en el área de embolsado: \n");
			imprimirPila(area_embolsado);

			int instante=1;
			bool cajera_totaliza=false; //true si esta totalizando un elemento
			bool bolsa_abierta=false; //si se abre una bolsa
			int t_abrir_bolsa=v_embolsado;
			int capacidad_bolsa_actual=0;
			/*cola_t *espera_banda=crearCola();
			cola_t *espera_embolsado=crearCola();
			pila_t *elementos_grandes_embolsado=crearPila();*/
			int facturacion=t_fact;
			elem_totalizando=NULL;
			elem_grande=NULL;
			elem_bolsa=NULL;
			actual=NULL;
			grande=NULL;
			while(c=='\n'){
				printf("\n");
				printf("Instante %d\n",instante);
				//printf("LLENA LA BANDA\n");
				while(elementos_banda<cc_banda && estaVaciaLista(total_carritos[i])==false){// && actual!=NULL){
					//printf("LLENA LA BANDA\n");
					actual=buscarNodo(total_carritos[i],0);
					if(estaVaciaCola(banda) && (elementos_banda+actual->elem.cc) > cc_banda){//No se agregan mas elementos
						actual=eliminarNodo(total_carritos[i]);
						encolar(espera_banda,actual);
						break;
					}else if(estaVaciaCola(banda)==false && (elementos_banda+actual->elem.cc) > cc_banda){
						break;
					}else{
						actual=eliminarNodo(total_carritos[i]);
						encolar(banda,actual);
						elementos_banda=elementos_banda+(actual->elem.cc);
					}
				}

				//Si el carrito no esta vacio y la banda si
				//printf("VE SI EL ELEMENTO ES GRANDE\n");
				if(estaVaciaLista(total_carritos[i])==false && estaVaciaCola(banda)){
					//printf("VE SI EL ELEMENTO ES GRANDE\n");
					elem_grande=buscarNodo(total_carritos[i],0);
					if(elem_grande->elem.cc>cc_banda){//El proximo del carrito es mas grande que la banda
						//Lo coloco en espera
						elem_grande=eliminarNodo(total_carritos[i]);
						encolar(espera_banda,elem_grande);
					}
				}

				//Inicialmente se debe ver si se puede totalizar algo
				//Si la banda no esta vacia y la cajera no esta totalizando
				//Si empieza a totalizar algo, debe eliminarlo de la banda y restarle a elementos_banda
				//printf("CAJERA TOMA NUEVO PRODUCTO\n");
				if((estaVaciaCola(banda)==false) && (cajera_totaliza==false)){
					//printf("CAJERA TOMA NUEVO PRODUCTO\n");
					elem_totalizando=desencolar(banda);
					cajera_totaliza=true;
					elementos_banda=elementos_banda-(elem_totalizando->elem.cc);
				}

				//Cajera realiza la totalizacion
				//printf("CAJERA TOTALIZA\n");
				if(cajera_totaliza==true){
					//printf("CAJERA TOTALIZA\n");
					//Si la cajera termina de totalizar, pasa al embolsado
					//printf("CAJERA PASA EMBOLSADO\n");
					if(((elem_totalizando->elem.total)<=0)){
						//printf("CAJERA PASA EMBOLSADO\n");
						if((elementos_embolsado+elem_totalizando->elem.cc)<=cc_embolsado){
							push(area_embolsado,elem_totalizando);
							elementos_embolsado=elementos_embolsado+(elem_totalizando->elem.cc);
						}else{
							encolar(espera_embolsado,elem_totalizando);
						}
						cajera_totaliza=false;
					}else{
						printf("La cajera está totalizando: %s.\n", elem_totalizando->elem.nombre);
						(elem_totalizando->elem.total)=(elem_totalizando->elem.total)-v_cajera;
					}
				}

				//Si en la cola de espera del embolsado se tienen elementos mas grandes, se colocan en una
				//pila de embolsado de elementos grandes y se totalizan al abrir una bolsa
				//printf("EMBOLSADO ESPERA\n");
				if(estaVaciaCola(espera_embolsado)==false){
					//printf("EMBOLSADO ESPERA\n");
					//nodo_t *grande;
					grande=peekCola(espera_embolsado);
					while(estaVaciaCola(espera_embolsado)==false){// && grande!=NULL (grande->elem.cc)>cc_bolsa && 
						if((grande->elem.cc)>cc_bolsa){
							grande=desencolar(espera_embolsado);
							push(elementos_grandes_embolsado,grande);
							grande=peekCola(espera_embolsado);
						}else{
							break;
						}
					}

				}


				//Si la cajera no esta totalizando y hay elementos en espera
				//printf("CAJERA TOTALIZA ELEMENTO EN ESPERA\n");
				if(cajera_totaliza==false && estaVaciaCola(espera_banda)==false){
					//printf("CAJERA TOTALIZA ELEMENTO EN ESPERA\n");
					elem_totalizando=desencolar(espera_banda);
					cajera_totaliza=true;
				}
				
				//Si no hay elementos en la banda y la cajera tampoco esta totalizando->factura--
				//printf("FACTURACION\n");
				if(estaVaciaCola(banda) && estaVaciaCola(espera_banda) && cajera_totaliza==false){
					//printf("FACTURACION\n");
					facturacion--;
				}

				//Si hay elementos para embolsar y la bolsa no esta abierta
				//printf("TIEMPO PARA ABRIR BOLSA\n");
				if((estaVaciaPila(area_embolsado)==false || estaVaciaPila(elementos_grandes_embolsado)==false) && bolsa_abierta==false){
					//printf("TIEMPO PARA ABRIR BOLSA\n");
					printf("La cajera está facturando.\n");
					t_abrir_bolsa--;
				}

				//Si se puede abrir una bolsa
				//printf("SE PUEDE ABRIR BOLSA\n");
				if(t_abrir_bolsa==0){
					//printf("SE PUEDE ABRIR BOLSA\n");
					bolsa_abierta=true;
					t_abrir_bolsa=v_embolsado;
					capacidad_bolsa_actual=0;
				}

				//Si se agregan elementos a una bolsa, revisar los que estan en espera del area de embolsado
				//agregar los que se puedan
				//printf("ABRE BOLSA\n");
				if(bolsa_abierta){
					//printf("ABRE BOLSA\n");
					//Creamos una lista
					lista_t* bolsita=crearLista();
					//Creamos un nodo_lista_t para una nueva bolsa (lista)
					nodo_lista_t* bolsa_nueva=crearNodoLista(bolsita);
					nodo_t *siguiente;
					while(estaVaciaPila(area_embolsado)==false && capacidad_bolsa_actual<cc_bolsa){
						siguiente=peek(area_embolsado);		
						//Si es asi, se agrega a una bolsa solo hasta que se encuentre un elemento de menor cc que la capacidad de la bolsa			
						if((siguiente->elem.cc)>cc_bolsa){
							do{
								lista_t* bolsita_2=crearLista();
								siguiente=pop(area_embolsado);
								elementos_embolsado=elementos_embolsado-(siguiente->elem.cc);
								agregarNodo(bolsita_2,siguiente);
								nodo_lista_t *bolsa_nueva_2=crearNodoLista(bolsita_2);
								agregarBolsa(bolsas,bolsa_nueva_2);
								siguiente=peek(area_embolsado);
							}while(estaVaciaPila(area_embolsado)==false);
						}	//mientras que el elemento sea mas grande y la pila no este vacia
						else{//ya tengo el peek
							if((capacidad_bolsa_actual+(siguiente->elem.cc))>cc_bolsa){
								break;
							}else{
								capacidad_bolsa_actual=capacidad_bolsa_actual+(siguiente->elem.cc);
								siguiente=pop(area_embolsado);
								elementos_embolsado=elementos_embolsado-(siguiente->elem.cc);
								agregarNodo(bolsita,siguiente);
							}
						}
						//printf("Elemento grande\n");
						if(estaVaciaPila(elementos_grandes_embolsado)==false){
							do{
								lista_t* bolsita_2=crearLista();
								siguiente=pop(elementos_grandes_embolsado);
								//elementos_embolsado=elementos_embolsado-(siguiente->elem.cc);
								agregarNodo(bolsita_2,siguiente);
								nodo_lista_t *bolsa_nueva_2=crearNodoLista(bolsita_2);
								agregarBolsa(bolsas,bolsa_nueva_2);
								siguiente=peek(elementos_grandes_embolsado);
							}while(estaVaciaPila(elementos_grandes_embolsado)==false);
						}
					}

					//Chequear los elementos grandes para agregarlos a bolsas
					while(estaVaciaPila(elementos_grandes_embolsado)==false){
						siguiente=peek(elementos_grandes_embolsado);
						lista_t* bolsita_3=crearLista();
						siguiente=pop(elementos_grandes_embolsado);
						agregarNodo(bolsita_3,siguiente);
						nodo_lista_t *bolsa_nueva_3=crearNodoLista(bolsita_3);
						agregarBolsa(bolsas,bolsa_nueva_3);
						siguiente=peek(area_embolsado);
					}

					if(estaVaciaLista(bolsita)==false){
						agregarBolsa(bolsas,bolsa_nueva);
					}
					//Cerramos la bolsa, cambiamos la bolsa actual
					bolsa_abierta=false;
					capacidad_bolsa_actual=0;
					//Actualizamos el area de embolsado con los que estaban en espera
					
					if(estaVaciaCola(espera_embolsado)==false){
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
				//printf("Elementos en espera en la banda transportadora:\n");
				//imprimirCola(espera_banda);
				printf("Elementos en el área de embolsado: \n");
				imprimirPila(area_embolsado);
				//printf("Elementos en espera en el área de embolsado: \n");
				//imprimirCola(espera_embolsado);
				printf("Elementos embolsados: \n");
				imprimirBolsas(bolsas);
				printf("Presione Enter.\n");
				do{
					fflush(stdin);
					c=getchar();
				}while(c!='\n');
				instante++;
				//Se debe ver que todo este vacio y que no se este totalizando ni embolsando nada
				if(estaVaciaLista(total_carritos[i]) && estaVaciaCola(banda) && estaVaciaCola(espera_banda) && estaVaciaPila(area_embolsado) && estaVaciaCola(espera_embolsado) && bolsa_abierta==false && facturacion<=0){
					printf("Se ha facturado el carrito %d\n",i);
					tiempo_cliente[i]=instante;
					printf("\n");
					//Liberar bolsas
					liberarEspacioBolsas(bolsas);
					break;
				}
			}
		}


		//Para la escritura en el log
		char str[100];
		strcpy(str,archivo_entrada);
		strcat(str,"\t"); //destination source. archivo entrada
		char num[10];
		sprintf(num,"%d\t",carritos);
		strcat(str,num);//cantidad de carritos
		for(i=0;i<carritos;i++){//numero de productos por carrito
			sprintf(num,"%d\t",compras_por_carrito[i]);
			strcat(str,num);
		}
		sprintf(num,"%d\t",cc_banda);
		strcat(str,num); //capacidad banda transportadora
		sprintf(num,"%d\t",v_cajera);
		strcat(str,num);//velocidad cajera
		sprintf(num,"%d\t",v_embolsado);
		strcat(str,num);//velocidad embolsador
		sprintf(num,"%d\t",t_fact);
		strcat(str,num);//tiempo facturacion
		sprintf(num,"%d\t",cc_embolsado);//capacidad area embolsado
		strcat(str,num);
		sprintf(num,"%d\t",cc_bolsa);//capacidad bolsa
		strcat(str,num);
		for(i=0;i<carritos;i++){//tiempo por carrito
			sprintf(num,"%d\t",tiempo_cliente[i]);
			strcat(str,num);
			printf("Instantes de tiempo para el cliente %d: %d.\n",i,tiempo_cliente[i]);
		}
		int tiempo_total=0;
		for(i=0;i<carritos;i++){//numero de productos por carrito
			tiempo_total=tiempo_total+tiempo_cliente[i];
		}
		sprintf(num,"%d\t",tiempo_total);
		strcat(str,num);
		strcat(str,"\n");
		//Escribir en el log
		escribirLinea(log,str);

		printf("Tiempo total: %d.\n",tiempo_total);

		//Liberamos el espacio
		free(tiempo_cliente);
		liberarEspacioCola(banda);
		liberarEspacioPila(area_embolsado);
		//liberarEspacioBolsas(bolsas);
		liberarEspacioCola(espera_banda);
		liberarEspacioCola(espera_embolsado);
		liberarEspacioPila(elementos_grandes_embolsado);
		liberarEspacioNodo(elem_totalizando);
		liberarEspacioNodo(elem_grande);
		liberarEspacioNodo(elem_bolsa);
		liberarEspacioNodo(actual);
		liberarEspacioNodo(grande);


	}else if(modalidad==2){//automatica
		int tiempo_cliente[carritos];
		cola_t *banda=crearCola();
		pila_t *area_embolsado=crearPila();
		//bolsas_t *bolsas=crearBolsas();
		int elementos_banda=0; //en la banda
		int tiempo_cajera, tiempo_embolsador; //tiempos que han pasado mientras totalizan o abren una bolsa
		int elementos_embolsado=0; //en el area de embolsado
		cola_t *espera_banda=crearCola();
		cola_t *espera_embolsado=crearCola();
		pila_t *elementos_grandes_embolsado=crearPila();
		nodo_t *elem_totalizando=NULL;
		nodo_t *elem_grande=NULL;
		nodo_t *elem_bolsa=NULL;
		nodo_t *actual=NULL;
		nodo_t *grande=NULL;
		for(i=0;i<carritos;i++){
			bolsas_t *bolsas=crearBolsas();
			int instante=1;
			bool cajera_totaliza=false; //true si esta totalizando un elemento
			bool bolsa_abierta=false; //si se abre una bolsa
			int t_abrir_bolsa=v_embolsado;
			int capacidad_bolsa_actual=0;
			int facturacion=t_fact;
			elem_totalizando=NULL;
			elem_grande=NULL;
			elem_bolsa=NULL;
			actual=NULL;
			grande=NULL;
			//bool simulacion=false;
			while(true){
				//printf("LLENA LA BANDA\n");
				while(elementos_banda<cc_banda && estaVaciaLista(total_carritos[i])==false){// && actual!=NULL){
					//printf("LLENA LA BANDA\n");
					actual=buscarNodo(total_carritos[i],0);
					if(estaVaciaCola(banda) && (elementos_banda+actual->elem.cc) > cc_banda){//No se agregan mas elementos
						actual=eliminarNodo(total_carritos[i]);
						encolar(espera_banda,actual);
						break;
					}else if(estaVaciaCola(banda)==false && (elementos_banda+actual->elem.cc) > cc_banda){
						break;
					}else{
						actual=eliminarNodo(total_carritos[i]);
						encolar(banda,actual);
						elementos_banda=elementos_banda+(actual->elem.cc);
					}
				}

				//Si el carrito no esta vacio y la banda si
				//printf("VE SI EL ELEMENTO ES GRANDE\n");
				if(estaVaciaLista(total_carritos[i])==false && estaVaciaCola(banda)){
					//printf("VE SI EL ELEMENTO ES GRANDE\n");
					elem_grande=buscarNodo(total_carritos[i],0);
					if(elem_grande->elem.cc>cc_banda){//El proximo del carrito es mas grande que la banda
						//Lo coloco en espera
						elem_grande=eliminarNodo(total_carritos[i]);
						encolar(espera_banda,elem_grande);
					}
				}

				//Inicialmente se debe ver si se puede totalizar algo
				//Si la banda no esta vacia y la cajera no esta totalizando
				//Si empieza a totalizar algo, debe eliminarlo de la banda y restarle a elementos_banda
				//printf("CAJERA TOMA NUEVO PRODUCTO\n");
				if((estaVaciaCola(banda)==false) && (cajera_totaliza==false)){
					//printf("CAJERA TOMA NUEVO PRODUCTO\n");
					elem_totalizando=desencolar(banda);
					cajera_totaliza=true;
					elementos_banda=elementos_banda-(elem_totalizando->elem.cc);
				}

				//Cajera realiza la totalizacion
				//printf("CAJERA TOTALIZA\n");
				if(cajera_totaliza==true){
					//printf("CAJERA TOTALIZA\n");
					//Si la cajera termina de totalizar, pasa al embolsado
					//printf("CAJERA PASA EMBOLSADO\n");
					if(((elem_totalizando->elem.total)<=0)){
						//printf("CAJERA PASA EMBOLSADO\n");
						if((elementos_embolsado+elem_totalizando->elem.cc)<=cc_embolsado){
							push(area_embolsado,elem_totalizando);
							elementos_embolsado=elementos_embolsado+(elem_totalizando->elem.cc);
						}else{
							encolar(espera_embolsado,elem_totalizando);
						}
						cajera_totaliza=false;
					}else{
						//printf("La cajera está totalizando: %s.\n", elem_totalizando->elem.nombre);
						(elem_totalizando->elem.total)=(elem_totalizando->elem.total)-v_cajera;
					}
				}

				//Si en la cola de espera del embolsado se tienen elementos mas grandes, se colocan en una
				//pila de embolsado de elementos grandes y se totalizan al abrir una bolsa
				//printf("EMBOLSADO ESPERA\n");
				if(estaVaciaCola(espera_embolsado)==false){
					//printf("EMBOLSADO ESPERA\n");
					grande=peekCola(espera_embolsado);
					while(estaVaciaCola(espera_embolsado)==false){// && grande!=NULL (grande->elem.cc)>cc_bolsa && 
						if((grande->elem.cc)>cc_bolsa){
							grande=desencolar(espera_embolsado);
							push(elementos_grandes_embolsado,grande);
							grande=peekCola(espera_embolsado);
						}else{
							break;
						}
					}

				}

				//Si la cajera no esta totalizando y hay elementos en espera
				//printf("CAJERA TOTALIZA ELEMENTO EN ESPERA\n");
				if(cajera_totaliza==false && estaVaciaCola(espera_banda)==false){
					//printf("CAJERA TOTALIZA ELEMENTO EN ESPERA\n");
					elem_totalizando=desencolar(espera_banda);
					cajera_totaliza=true;
				}
				
				//Si no hay elementos en la banda y la cajera tampoco esta totalizando->factura--
				//printf("FACTURACION\n");
				if(estaVaciaCola(banda) && estaVaciaCola(espera_banda) && cajera_totaliza==false){
					//printf("FACTURACION\n");
					facturacion--;
				}

				//Si hay elementos para embolsar y la bolsa no esta abierta
				//printf("TIEMPO PARA ABRIR BOLSA\n");
				if((estaVaciaPila(area_embolsado)==false || estaVaciaPila(elementos_grandes_embolsado)==false) && bolsa_abierta==false){
					//printf("TIEMPO PARA ABRIR BOLSA\n");
					//printf("La cajera está facturando.\n");
					t_abrir_bolsa--;
				}

				//Si se puede abrir una bolsa
				//printf("SE PUEDE ABRIR BOLSA\n");
				if(t_abrir_bolsa==0){
					//printf("SE PUEDE ABRIR BOLSA\n");
					bolsa_abierta=true;
					t_abrir_bolsa=v_embolsado;
					capacidad_bolsa_actual=0;
				}

				//Si se agregan elementos a una bolsa, revisar los que estan en espera del area de embolsado
				//agregar los que se puedan
				//printf("ABRE BOLSA\n");
				if(bolsa_abierta){
					//printf("ABRE BOLSA\n");
					//Creamos una lista
					lista_t* bolsita=crearLista();
					//Creamos un nodo_lista_t para una nueva bolsa (lista)
					nodo_lista_t* bolsa_nueva=crearNodoLista(bolsita);
					nodo_t *siguiente;
					while(estaVaciaPila(area_embolsado)==false && capacidad_bolsa_actual<cc_bolsa){
						siguiente=peek(area_embolsado);		
						//Si es asi, se agrega a una bolsa solo hasta que se encuentre un elemento de menor cc que la capacidad de la bolsa			
						if((siguiente->elem.cc)>cc_bolsa){
							do{
								lista_t* bolsita_2=crearLista();
								siguiente=pop(area_embolsado);
								elementos_embolsado=elementos_embolsado-(siguiente->elem.cc);
								agregarNodo(bolsita_2,siguiente);
								nodo_lista_t *bolsa_nueva_2=crearNodoLista(bolsita_2);
								agregarBolsa(bolsas,bolsa_nueva_2);
								siguiente=peek(area_embolsado);
							}while(estaVaciaPila(area_embolsado)==false);
						}	//mientras que el elemento sea mas grande y la pila no este vacia
						else{//ya tengo el peek
							if((capacidad_bolsa_actual+(siguiente->elem.cc))>cc_bolsa){
								break;
							}else{
								capacidad_bolsa_actual=capacidad_bolsa_actual+(siguiente->elem.cc);
								siguiente=pop(area_embolsado);
								elementos_embolsado=elementos_embolsado-(siguiente->elem.cc);
								agregarNodo(bolsita,siguiente);
							}
						}
						//printf("Elemento grande\n");
						if(estaVaciaPila(elementos_grandes_embolsado)==false){
							do{
								lista_t* bolsita_2=crearLista();
								siguiente=pop(elementos_grandes_embolsado);
								//elementos_embolsado=elementos_embolsado-(siguiente->elem.cc);
								agregarNodo(bolsita_2,siguiente);
								nodo_lista_t *bolsa_nueva_2=crearNodoLista(bolsita_2);
								agregarBolsa(bolsas,bolsa_nueva_2);
								siguiente=peek(elementos_grandes_embolsado);
							}while(estaVaciaPila(elementos_grandes_embolsado)==false);
						}
					}

					//Chequear los elementos grandes para agregarlos a bolsas
					while(estaVaciaPila(elementos_grandes_embolsado)==false){
						siguiente=peek(elementos_grandes_embolsado);
						lista_t* bolsita_3=crearLista();
						siguiente=pop(elementos_grandes_embolsado);
						agregarNodo(bolsita_3,siguiente);
						nodo_lista_t *bolsa_nueva_3=crearNodoLista(bolsita_3);
						agregarBolsa(bolsas,bolsa_nueva_3);
						siguiente=peek(area_embolsado);
					}

					if(estaVaciaLista(bolsita)==false){
						agregarBolsa(bolsas,bolsa_nueva);
					}
					//Cerramos la bolsa, cambiamos la bolsa actual
					bolsa_abierta=false;
					capacidad_bolsa_actual=0;
					//Actualizamos el area de embolsado con los que estaban en espera
					
					if(estaVaciaCola(espera_embolsado)==false){
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

				instante++;
				//Se debe ver que todo este vacio y que no se este totalizando ni embolsando nada
				if(estaVaciaLista(total_carritos[i]) && estaVaciaCola(banda) && estaVaciaCola(espera_banda) && estaVaciaPila(area_embolsado) && estaVaciaCola(espera_embolsado) && bolsa_abierta==false && facturacion<=0){
					//printf("Se ha facturado el carrito %d\n",i);
					tiempo_cliente[i]=instante;
					//Liberar bolsas
					liberarEspacioBolsas(bolsas);
					break;
				}
			}
		}


		//Para la escritura en el log
		char str[100];
		strcpy(str,archivo_entrada);
		strcat(str,"\t"); //destination source. archivo entrada
		char num[10];
		sprintf(num,"%d\t",carritos);
		strcat(str,num);//cantidad de carritos
		for(i=0;i<carritos;i++){//numero de productos por carrito
			sprintf(num,"%d\t",compras_por_carrito[i]);
			strcat(str,num);
		}
		sprintf(num,"%d\t",cc_banda);
		strcat(str,num); //capacidad banda transportadora
		sprintf(num,"%d\t",v_cajera);
		strcat(str,num);//velocidad cajera
		sprintf(num,"%d\t",v_embolsado);
		strcat(str,num);//velocidad embolsador
		sprintf(num,"%d\t",t_fact);
		strcat(str,num);//tiempo facturacion
		sprintf(num,"%d\t",cc_embolsado);//capacidad area embolsado
		strcat(str,num);
		sprintf(num,"%d\t",cc_bolsa);//capacidad bolsa
		strcat(str,num);
		for(i=0;i<carritos;i++){//tiempo por carrito
			sprintf(num,"%d\t",tiempo_cliente[i]);
			strcat(str,num);
			printf("Instantes de tiempo para el cliente %d: %d.\n",i,tiempo_cliente[i]);
		}
		int tiempo_total=0;
		for(i=0;i<carritos;i++){//numero de productos por carrito
			tiempo_total=tiempo_total+tiempo_cliente[i];
		}
		sprintf(num,"%d\t",tiempo_total);
		strcat(str,num);
		strcat(str,"\n");
		//Escribir en el log
		escribirLinea(log,str);

		printf("Tiempo total: %d.\n",tiempo_total);

		//Liberamos el espacio
		free(tiempo_cliente);
		liberarEspacioCola(banda);
		liberarEspacioPila(area_embolsado);
		liberarEspacioCola(espera_banda);
		liberarEspacioCola(espera_embolsado);
		liberarEspacioPila(elementos_grandes_embolsado);
		liberarEspacioNodo(elem_totalizando);
		liberarEspacioNodo(elem_grande);
		liberarEspacioNodo(elem_bolsa);
		liberarEspacioNodo(actual);
		liberarEspacioNodo(grande);
	}
	return;
}
#endif