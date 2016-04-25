/*
 * funciones.c
 *
 *  Created on: 13/4/2016
 *      Author: Jon
 */
#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char mostrarMenu()
{
	printf("MEN� PRINCIPAL\n"
			"1.\tVisualizar RSS\n"
			"2.\tEditar RSS\n"
			"3.\tEstad�sticas\n"
			"4.\tSalir\n\n"
			"Introduzca n�mero de la funci�n deseada:\n");
	fflush(stdout);
	char resultado;
	resultado = getchar();
	fflush(stdin);
	return resultado;
}

char* substr(char* cadena, int comienzo, int longitud)
{
	if (longitud == 0) longitud = strlen(cadena)-comienzo-1;

	char *nuevo = (char*)malloc(sizeof(char) * longitud);

	strncpy(nuevo, cadena + comienzo, longitud);

	return nuevo;
}
int _find(char* cadena, char* palabra){

    int i, j = 0;

    for(i = 0; i < strlen(cadena); i++){
        if(palabra[j] == cadena[i]){
            ++j;

            if(j == strlen(palabra))
                return (2 + i - j);
        }

        else j = 0;
    }

    return -1;
}
