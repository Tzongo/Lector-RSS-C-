/*
 * funciones.c
 *
 *  Created on: 13/4/2016
 *      Author: Jon
 */
#include "funciones.h"
#include <stdio.h>

char mostrarMenu()
{
	printf("1.\tVisualizar RSS\n"
			"2.\tEditar RSS\n"
			"3.\tEstadísticas\n"
			"4.\tSalir\n\n"
			"Introduzca número de la función deseada: ");
	fflush(stdout);
	char resultado;
	resultado = getchar();
	return resultado;
}

