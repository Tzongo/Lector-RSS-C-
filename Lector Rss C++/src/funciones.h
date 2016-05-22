/*
 * funciones.h
 *
 *  Created on: 13/4/2016
 *      Author: Jon
 */
#include "Noticia.h"
#include <sqlite3.h>
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
void crearRss(string nombreRSS, list<Noticia*>* noticias);
void conectarBD(sqlite3* db, int rc);
void almacenarEnBD(string nombreRSS, list<Noticia*> noticias);
Noticia* get(list<Noticia*> _list, int _i);

#endif /* FUNCIONES_H_ */
