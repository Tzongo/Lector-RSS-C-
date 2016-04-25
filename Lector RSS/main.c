/*
 * main.c
 *  Created on: 13/4/2016
 *      Author: Jon
 */
#include "funciones.h"
#include <stdio.h>
#include <stdbool.h>

int main (void){
	char funcMenu;
	bool repetir;
	do
	{
		repetir = false;
		funcMenu = mostrarMenu();
		switch (funcMenu)
			{
				case '1':
						printf("Introduce nombre del archivo: \n");
						fflush(stdout);
						char nombre[20];
						scanf("%s",nombre);
						fflush(stdin);
						printf("%s",nombre);
						abrirRss(nombre);
						repetir=true;
					break;
				case '2':
					break;
				case '3':
					break;
				case '4':
					break;
				default:
					printf("\n¡Opcion incorrecta!\n\n");
					repetir = true;
					break;
			}
	}while (repetir);

	return 0;
}

