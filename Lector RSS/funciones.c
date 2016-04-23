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
	printf("MENÚ PRINCIPAL\n"
			"1.\tVisualizar RSS\n"
			"2.\tEditar RSS\n"
			"3.\tEstadísticas\n"
			"4.\tSalir\n\n"
			"Introduzca número de la función deseada:\n");
	fflush(stdout);
	char resultado;
	resultado = getchar();
	fflush(stdin);
	return resultado;
}

