/*
 * funciones.h
 *
 *  Created on: 13/4/2016
 *      Author: Jon
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

typedef struct
{
	char* tituloRss;
	char* autorRss;
	char* items;
	char* fuentes;
}Info;
char mostrarMenu();
char* substring();
int _find();
int abrirRss(char* nombre);
Info infoRss(char* nombre);

#endif /* FUNCIONES_H_ */
