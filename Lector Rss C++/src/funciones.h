/*
 * funciones.h
 *
 *  Created on: 13/4/2016
 *      Author: Jon
 */
#include "Noticia.h"
#include <list>
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
Noticia* nuevaNoticia();
void mostrarNoticia(Noticia* n);
list<Noticia*> crearRss() ;

#endif /* FUNCIONES_H_ */
