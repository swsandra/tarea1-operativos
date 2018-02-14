#ifndef MODIFICAR_SIMULACION_H
#define MODIFICAR_SIMULACION_H

#include <stdio.h>
#include <stdlib.h>

void modificar_simulacion(int *opciones){

	int opcion;
	bool salir=false;
	while(salir==false){
		do{
			printf("1. Modalidad (Interactiva por defecto)\n");
			printf("2. Cantidad de carritos en la cola (3 por defecto)\n");
			printf("3. Cantidad máxima de productos que puede tener un carrito (30 por defecto)\n");
			printf("4. Capacidad máxima de la banda transportadora (200 cc por defecto)\n");
			printf("5. Velocidad de la cajera (1 ops por defecto)\n");
			printf("6. Velocidad del embolsador (4 spb por defecto)\n");
			printf("7. Tiempo de facturación (130 s por defecto)\n");
			printf("8. Capacidad máxima del área de embolsado (150 cc por defecto)\n");
			printf("9. Capacidad máxima de una bolsa (120 cc por defecto)\n");
			printf("10. Salir\n");
			fflush(stdin);
			printf("Introduzca la opción que desea modificar: ");
			scanf(" %d",&opcion);
			printf("\n");
		}while(opcion<1 || opcion>10);
		//while(strcmp(opcion,"1") && strcmp(opcion,"2") && strcmp(opcion,"3") && strcmp(opcion,"4") && strcmp(opcion,"5") && strcmp(opcion,"6") && strcmp(opcion,"7") && strcmp(opcion,"8") && strcmp(opcion,"9") && strcmp(opcion,"10"));

		//Modificar el arreglo de las opciones
		switch(opcion){

			int op;
			//char opm;
			case 1:
				do{
					printf("Modalidad\n");
					printf("1. Interactiva\n");
					printf("2. Automática\n");
					fflush(stdin);
					printf("Introduzca una opción: ");
					scanf(" %d",&op);
					printf("\n");
				}while(op<1 || op>2);
				printf("%c\n", op);
				if(op==1) *(opciones)=1;
				else if(op==2) *(opciones)=2;
				break;

			case 2:
				do{
					printf("Cantidad de carritos en la cola: ");
					fflush(stdin);
					scanf(" %d",&op);
					printf("\n");
				}while(op<1);
				*(opciones+1)=op;
				//opciones[1]=op;
				break;

			case 3:
				do{
					printf("Cantidad máxima de productos que puede tener un carrito: ");
					fflush(stdin);
					scanf(" %d",&op);
					printf("\n");
				}while(op<1);
				*(opciones+2)=op;
				//opciones[2]=op;
				break;

			case 4:
				do{
					printf("Capacidad máxima de la banda transportadora en cc: ");
					fflush(stdin);
					scanf(" %d",&op);
					printf("\n");
				}while(op<1);
				*(opciones+3)=op;
				//opciones[3]=op;
				break;

			case 5:
				do{
					printf("Velocidad de la cajera en ops (operaciones): ");
					fflush(stdin);
					scanf(" %d",&op);
					printf("\n");
				}while(op<1);
				*(opciones+4)=op;
				//opciones[4]=op;
				break;

			case 6:
				do{
					printf("Velocidad del embolsador en segundos por bolsa: ");
					fflush(stdin);
					scanf(" %d",&op);
					printf("\n");
				}while(op<1);
				*(opciones+5)=op;
				//opciones[5]=op;
				break;

			case 7:
				do{
					printf("Tiempo de facturación en segundos: ");
					fflush(stdin);
					scanf(" %d",&op);
					printf("\n");
				}while(op<1);
				*(opciones+6)=op;
				//opciones[6]=op;
				break;

			case 8:
				do{
					printf("Capacidad máxima del área de embolsado en cc: ");
					fflush(stdin);
					scanf(" %d",&op);
					printf("\n");
				}while(op<1);
				*(opciones+7)=op;
				//opciones[7]=op;
				break;

			case 9:
				do{
					printf("Capacidad máxima de una bolsa en cc: ");
					fflush(stdin);
					scanf(" %d",&op);
					printf("\n");
				}while(op<1);
				*(opciones+8)=op;
				//opciones[8]=op;
				break;

			case 10:
				salir=true;
				printf("\n");
				break;

			}
		}
	return;
}

#endif