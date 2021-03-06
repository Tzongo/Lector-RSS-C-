/*
 /*
 * funciones.c
 *
 *  Created on: 13/4/2016
 *      Author: Jon
 */
#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Noticia.h"
#include <list>
#include "sqlite3.h"
#include <iostream>
#include <sstream>
#include <typeinfo>
FILE *doc;
using namespace std;
char mostrarMenu() {
	printf("MENU PRINCIPAL\n"
			"1.\tVisualizar RSS\n"
			"2.\tEditar RSS\n"
			"3.\tCrear RSS\n"
			"4.\tSalir\n\n"
			"Introduzca numero de la funcion deseada:\n");
	fflush(stdout);
	char resultado;
	resultado = getchar();
	fflush(stdin);
	return resultado;
}
void crearRss(string nombreRSS, list<Noticia*>* noticias) {

	char fin = 'n';
	do {
		noticias->push_back(nuevaNoticia());
		printf("Quieres introudcir mas noticias? s/n \n");
		fflush(stdout);
		cin >> fin;
		cout << endl;
	} while (fin == 's');
	almacenarEnBD(nombreRSS, noticias);
}
Noticia* nuevaNoticia() {

	Noticia* n = new Noticia();
	printf("Introduce titulo de la noticia: \n");
	fflush(stdout);
	string titulo;
	cin >> titulo;
	cout << endl;
	n->setTitulo(titulo);
	//////titulo//////
	printf("Introduce autor de la noticia: \n");
	fflush(stdout);
	string autor;
	cin >> autor;
	cout << endl;
	n->setAutor(autor);
	//////autor//////
	printf("Introduce descripcion de la noticia: \n");
	fflush(stdout);
	string desc;
	cin >> desc;
	cout << endl;
	n->setDescripcion(desc);
	//////descripcion//////
	return n;
}
void mostrarNoticia(Noticia* n) {
	printf("Titulo de la noticia: %s\n", n->getTitulo().c_str());
	fflush(stdout);
	printf("Autor de la noticia: %s\n", n->getAutor().c_str());
	fflush(stdout);
	printf("Descripcion de la noticia: %s\n", n->getDescripcion().c_str());
	fflush(stdout);
}

/*sqlite3* conectarBD()
 {
 int rc;
 sqlite3* db;
 rc = sqlite3_open("xmlbd.s3db", &db);

 if( rc ){
 //cambiar stderr por stdout para mostrar por consola
 fprintf(stdout, "Error al abrir BD: %s\n", sqlite3_errmsg(db));
 exit(0);
 }else{
 fprintf(stdout, "Base de datos abierta exitosamente\n");
 }
 return db;
 }*/
void cerrarBD(sqlite3* db) {
	sqlite3_close(db);
}
int callback(void *NotUsed, int argc, char **argv, char **azColName) {

	NotUsed = 0;

	for (int i = 0; i < argc; i++) {

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

Noticia* getTableDataNoticia(char* query) {
	sqlite3_stmt *statement;
	sqlite3* db;
	int rc;
	Noticia* n = new Noticia();
	rc = sqlite3_open("xmlbd.s3db", &db);

	if (rc) {
		//cambiar stderr por stdout para mostrar por consola
		fprintf(stdout, "Error al abrir BD: %s\n", sqlite3_errmsg(db));
		exit(0);
	} else {
		fprintf(stdout, "Base de datos abierta exitosamente\n");
	}

	if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
		int ctotal = sqlite3_column_count(statement);
		int res = 0;

		while (1) {
			res = sqlite3_step(statement);

			if (res == SQLITE_ROW) {

				for (int i = 0; i < ctotal; i++) {

					string s = (char*) sqlite3_column_text(statement, i);
					// print or format the output as you want

					switch (i) {
					case 0:
						n->setId(atoi(s.c_str()));
						break;
					case 1:
						n->setTitulo(s);
						break;
					case 2:
						n->setAutor(s.c_str());
						break;
					case 3:
						n->setDescripcion(s);
						break;
					default:
						break;
					}
				}
			}


			if (res == SQLITE_DONE || res == SQLITE_ERROR) {
				cout << "done " << endl;
				break;
			}
		}

	}
	mostrarNoticia(n);
	return n;
}

int getTableDataID(char* query) {
	int a;
	sqlite3_stmt *statement;
	sqlite3* db;
	int rc;
	rc = sqlite3_open("xmlbd.s3db", &db);

	if (rc) {
		//cambiar stderr por stdout para mostrar por consola
		fprintf(stdout, "Error al abrir BD: %s\n", sqlite3_errmsg(db));
		exit(0);
	} else {
		fprintf(stdout, "Base de datos abierta exitosamente\n");
	}

	if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
		int ctotal = sqlite3_column_count(statement);
		int res = 0;

		while (1) {
			res = sqlite3_step(statement);
			if (res == SQLITE_ROW) {

				for (int i = 0; i < ctotal; i++) {

					string s = (char*) sqlite3_column_text(statement, i);
					// print or format the output as you want

					switch (i) {
					case 0:
						a = atoi(s.c_str());
						break;
					default:
						break;
					}
				}
			}

			if (res == SQLITE_DONE || res == SQLITE_ERROR) {
				cout << "done " << endl;
				break;
			}
		}

	}
	return a;
}

void almacenarEnBD(string nombreRSS, list<Noticia*>* noticias) {
	sqlite3* db;
	int rc;
	char *zErrMsg = 0;
	//conectarBD();

	rc = sqlite3_open("xmlbd.s3db", &db);

	if (rc) {
		//cambiar stderr por stdout para mostrar por consola
		fprintf(stdout, "Error al abrir BD: %s\n", sqlite3_errmsg(db));
		exit(0);
	} else {
		fprintf(stdout, "Base de datos abierta exitosamente\n");
	}


	string sql = "";
	string sql2 = "INSERT INTO XML (NOM_XML, RUTA)VALUES ('" + nombreRSS
			+ "', 'Lector Rss C++/src/" + nombreRSS + ".xml');";

	const char *csql2 = sql2.c_str();
	rc = sqlite3_exec(db, csql2, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stdout, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "XML creado\n");
	}
	int a;
	a = getTableDataID(
			(char*) ("SELECT COD_XML FROM XML WHERE NOM_XML LIKE '" + nombreRSS
					+ "';").c_str());

	unsigned int i;

	string result;

	ostringstream convert;

	convert << a;

	result = convert.str();

	for (i = 0; i < noticias->size(); i++) {

		sql += "INSERT INTO NOTICIA (TITULO,AUTOR,DESC, COD_XML)VALUES ( '"
				+ get(noticias, i)->getTitulo() + "', '"
				+ get(noticias, i)->getAutor() + "', '"
				+ get(noticias, i)->getDescripcion() + "'," + result + ");";
	}
	const char *csql = sql.c_str();
	rc = sqlite3_exec(db, csql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Noticias insertadas\n");
	}
	cerrarBD(db);
}

Noticia* get(list<Noticia*>* _list, int _i) {
	list<Noticia*>::iterator it = _list->begin();
	for (int i = 0; i < _i; i++) {
		++it;
	}
	return *it;
}
int ejecutarComandoBD(char * statement) {
	int devolver;
	int rc;

	sqlite3* db;
	rc = sqlite3_open("xmlbd.s3db", &db);

	if (rc) {
		//cambiar stderr por stdout para mostrar por consola
		fprintf(stdout, "Error al abrir BD: %s\n", sqlite3_errmsg(db));
		exit(0);
	} else {
		fprintf(stdout, "Base de datos abierta exitosamente\n");
	}

	char *zErrMsg = 0;
	const char* data = "Callback function called";
	rc = sqlite3_exec(db, statement, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		fflush(stdout);
		sqlite3_free(zErrMsg);
		devolver = 1;
	} else {
		fprintf(stdout, "Operacion correcta\n");
		devolver = 0;

	}
	cerrarBD(db);
	return devolver;

}
/*void exportarXML() {
 sqlite3 *db;
 char *zErrMsg = 0;
 int rc, rc1;
 char *sql;
 string sqla;
 string sqld;
 string sqlt;

 const char* data = "Callback function called";
 // Open database
 //rc = sqlite3_open("xmlbd.s3db", &db);

 rc = sqlite3_open("xmlbd.s3db", &db);

 if (rc) {
 //cambiar stderr por stdout para mostrar por consola
 fprintf(stdout, "Error al abrir BD: %s\n", sqlite3_errmsg(db));
 exit(0);
 } else {
 fprintf(stdout, "Base de datos abierta exitosamente\n");
 }
 int (*callback)(void*, int, char**, char**);
 // Create SQL statement
 int i, var;
 rc1 = sqlite3_exec(db, "select count(*) from NOTICIA", callback,
 (void*) data, &zErrMsg);

 for (i = 0; i < rc1; i++) {
 string nom = "RSS ";
 nom.append(i + ".xml");
 const char *cnom = sqld.c_str();
 doc = fopen(cnom, "a+");

 for (var = 0; var < rc1; ++var) {
 string result;

 ostringstream convert;

 convert << i;

 result = convert.str();
 string result2;


 convert << var;

 result = convert.str();
 sqla = "select AUTOR from NOTICIA  where COD_XML = " + result
 + " and COD_NOT = " + result2;
 sqlt = "select TITULO from NOTICIA  where COD_XML = " + result
 + " and COD_NOT=" + result2;
 sqld = "select DESCRIPCION from NOTICIA  where COD_XML = " + result
 + " and COD_NOT=" + result2;

 const char *csqld = sqld.c_str();
 const char *csqlt = sqlt.c_str();
 const char *csqla = sqla.c_str();
 int (*callback)(void*, int, char**, char**);

 fprintf(doc, "<channel><title>");
 fprintf(doc, "%i",
 sqlite3_exec(db, csqlt, callback, (void*) data, &zErrMsg));
 fprintf(doc, "</title>\t");
 fprintf(doc, "<description><![CDATA[");
 fprintf(doc, "%i",
 sqlite3_exec(db, csqlt, callback, (void*) data, &zErrMsg));
 fprintf(doc, "]]</description>\t");
 fprintf(doc, "<author>");
 fprintf(doc, "%i",
 sqlite3_exec(db, csqla, callback, (void*) data, &zErrMsg));
 fprintf(doc, "</author>\t");

 }
 }
 if (rc != SQLITE_OK) {
 fprintf(stdout, "SQL error: %s\n", zErrMsg);
 sqlite3_free(zErrMsg);
 } else {
 fprintf(stdout, "Operation done successfully\n");
 }
 sqlite3_close(db);
 }*/
