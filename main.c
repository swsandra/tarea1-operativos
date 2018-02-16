#include "listaordenada.h"
#include "cola.h"
#include "pila.h"
#include "lectura_escritura.h"
#include "modificar_simulacion.h"
#include "simulacion.h"

int main(int argc, char *argv[]){

	//cantidad correcta de argumentos
	if(argc!=2){
		fprintf(stderr,"USO de %s: archivo_de_entrada\n", argv[0]);  
		exit(1);
	}

	bool salir=false;
	char opcion;
	while(salir==false){
		do{
			printf("Menú\n");
			printf("1. Ejecutar la simulación\n");
			printf("2. Cambiar las opciones de la simulación\n");
			printf("3. Salir del programa\n");
			fflush(stdin);
			printf("Introduzca una opción: ");
			scanf(" %c",&opcion);
			//printf("%c\n", opcion);
			printf("\n");
		}while(opcion!='1' && opcion!='2' && opcion!='3');
		
		int opciones_sim[9];
		//Inicializamos las opciones por defecto
		int *opciones=opciones_sim;
		*opciones=1;//Modalidad 1 interactiva 2 automatica
		*(opciones+1)=3;
		*(opciones+2)=30;
		*(opciones+3)=200;
		*(opciones+4)=1;
		*(opciones+5)=4;
		*(opciones+6)=130;
		*(opciones+7)=150;
		*(opciones+8)=120;

		switch(opcion){
			case '1'://ejecutar simulacion
				simulacion(opciones,argv[1],"log.txt");
				break;
			case '2'://cambiar opciones simulacion
				modificar_simulacion(opciones_sim);
				simulacion(opciones,argv[1],"log.txt");
				printf("holaaaaaa\n");
				break;
			case '3'://salir del programa
				salir=true;
				break;
		}

	}

	return 0;
}