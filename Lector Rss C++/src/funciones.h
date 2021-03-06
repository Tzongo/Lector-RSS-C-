/*
 * funciones.h
 *
 *  Created on: 13/4/2016
 *      Author: Jon
 */
#include "Noticia.h"
#include "sqlite3.h"
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
//void conectarBD();
void almacenarEnBD(string nombreRSS, list<Noticia*>* noticias);
Noticia* get(list<Noticia*>* _list, int _i);
int ejecutarComandoBD( char * statement);
void exportarXML();
int callback(void *NotUsed, int argc, char **argv, char **azColName);
int callback2(void *NotUsed, int argc, char **argv, char **azColName,list<Noticia*>* noticias);
list<Noticia*>* getTableData(char* query, list<Noticia*>* noticias);
int getTableData(char* query);
Noticia* getTableDataNoticia(char* query);
#endif /* FUNCIONES_H_ */
