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

char *substring(char *string, int position, int length)
{
   char *pointer;
   int c;

   pointer = malloc(length+1);

   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }

   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *(string+position-1);
      string++;
   }

   *(pointer+c) = '\0';

   return pointer;
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
