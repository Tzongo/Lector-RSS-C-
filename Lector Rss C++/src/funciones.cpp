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
#include <typeinfo>
using namespace std;
char mostrarMenu() {
	printf("MENU PRINCIPAL\n"
			"1.\tVisualizar RSS\n"
			"2.\tEditar RSS\n"
			"3.\tCrear RSS\n"
			"4.\tInformacion RSS\n"
			"5.\tSalir\n\n"
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
		/*scanf("%c", &fin);
		 fflush(stdin);*/
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
	//getline(cin, titulo);
	/*scanf("%s", titulo.c_str());
	 fflush(stdin);*/
	n->setTitulo(titulo);
	//////titulo//////
	printf("Introduce autor de la noticia: \n");
	fflush(stdout);
	string autor;
	cin >> autor;
	cout << endl;
	//getline(cin, autor);
	/*scanf("%s", autor.c_str());
	 fflush(stdin);*/
	n->setAutor(autor);
	//////autor//////
	printf("Introduce descripcion de la noticia: \n");
	fflush(stdout);
	string desc;
	cin >> desc;
	cout << endl;
	//getline(cin, desc);
	/*scanf("%s", desc.c_str());
	 fflush(stdin);*/
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

list<Noticia*>* getTableData(char* query,list<Noticia*>* noticias) {
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
			Noticia* n;n = new Noticia();
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
					default:
						break;
					}
				}
			}
			mostrarNoticia(n);
			noticias->push_back(n);

			if (res == SQLITE_DONE || res == SQLITE_ERROR) {
				cout << "done " << endl;
				break;
			}
		}

	}
	return noticias;
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

	printf("Titulo de la noticia: %s\n", nombreRSS.c_str());
	fflush(stdout);

	string sql = "";
	string sql2 = "INSERT INTO XML (NOM_XML, RUTA)VALUES ('" + nombreRSS
			+ "', 'Lector Rss C++/src/" + nombreRSS + ".xml');";

	const char *csql2 = sql2.c_str();
	rc = sqlite3_exec(db, csql2, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stdout, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Records created successfully1\n");
	}

	ejecutarComandoBD(
			(char*) ("SELECT COD_XML FROM XML WHERE NOM_XML LIKE '" + nombreRSS
					+ "';").c_str());
	unsigned int i;
	for (i = 0; i < noticias->size(); i++) {
		sql.append("INSERT INTO NOTICIA (TITULO,AUTOR,DESC)VALUES ( '");
		sql.append(get(noticias, i)->getTitulo());
		sql.append("', '");
		sql.append(get(noticias, i)->getAutor());
		sql.append("', '");
		sql.append(get(noticias, i)->getDescripcion());
		sql.append("' );");
	}
	const char *csql = sql.c_str();
	rc = sqlite3_exec(db, csql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Records created successfully2\n");
	}
	cerrarBD(db);
}

/*
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

 int abrirRss(char* nombre)
 {
 FILE *ptr_file;
 char *buf;
 int s=-1;
 ptr_file =fopen(nombre,"r");
 if (!ptr_file){
 printf("\n\nArchivo no encotrado!\n\n");
 //getch();
 return 0;
 }

 fseek(ptr_file, 0, SEEK_END);
 s = ftell(ptr_file);
 fseek(ptr_file, 0, SEEK_SET);
 int cont;cont=0;
 buf=(char*)malloc(s*sizeof(char));
 while (fgets(buf,s, ptr_file)!=NULL){
 int p1,p2;
 if (_find(buf,"<item>")!=-1) {
 printf("\n-----------------------\n");
 }else if (_find(buf,"<title>")!=-1) {
 p1=_find(buf,"<title>");
 p2=_find(buf,"]]></title>");
 if (cont==0) {
 char* str;
 str=substring(buf,p1+7,(p2-1)-(p1+6));
 printf("\n\n%s\n",str);
 cont++;
 }
 else{
 char* str;
 str=substring(buf,p1+17,(p2-1)-(p1+17));
 printf("%s\n",str);
 }

 }
 else if (_find(buf,"<pubDate>")!=-1) {
 p1=_find(buf,"<pubDate>");
 p2=_find(buf,"</pubDate>");
 char* str;
 str=substring(buf,p1+9,(p2-1)-(p1+9));
 printf("%s\n",str);
 }else if (_find(buf,"<link>")!=-1) {
 p1=_find(buf,"<link>");
 p2=_find(buf,"</link>");
 char* str;
 str=substring(buf,p1+6,(p2-1)-(p1+5));
 printf("%s\n",str);
 }else if (_find(buf,"<description>")!=-1) {
 p1=_find(buf,"<description><![CDATA[ ");
 p2=_find(buf,"]]></description>");
 char* str;
 str=substring(buf,p1+23,(p2-1)-(p1));
 printf("%s\n",str);
 printf("-------------------\n");
 }
 else if(_find(buf,"</rss>")!=-1){
 return 0;
 }
 }
 fclose(ptr_file);
 //getch();
 return 0;
 }

 Info infoRss(char* nombre)
 {
 FILE *ptr_file;
 char *buf;
 int s=-1;
 ptr_file =fopen(nombre,"r");
 if (!ptr_file){
 printf("\n\nArchivo no encotrado!\n\n");
 //getch();

 }

 fseek(ptr_file, 0, SEEK_END);
 s = ftell(ptr_file);
 fseek(ptr_file, 0, SEEK_SET);
 int contTitulo;contTitulo=0;
 int contItem;contItem=1;
 char numItem[10];
 sprintf(numItem, "%d", contItem);
 strcat(numItem, ". ");
 int contFuente;contFuente=1;
 char numFuente[10];
 sprintf(numFuente, "%d", contFuente);
 strcat(numFuente, ". ");
 buf=(char*)malloc(s*sizeof(char));
 int numCaracteres = 0;
 //		while (fgets(buf,s, ptr_file)!=NULL){
 //			numCaracteres += strlen(buf);
 //		}

 Info inform;
 inform.tituloRss = (char*)malloc(200 * sizeof(char));
 inform.autorRss = (char*)malloc(200 * sizeof(char));
 inform.items = (char*)malloc(10000 * sizeof(char));
 inform.fuentes = (char*)malloc(10000 * sizeof(char));
 while (fgets(buf,s, ptr_file)!=NULL){
 int p1, p2;
 if (_find(buf,"<title>")!=-1) {
 p1=_find(buf,"<title>");
 p2=_find(buf,"]]></title>");
 if (contTitulo==0) {
 char* str;
 str=substring(buf,p1+7,(p2-1)-(p1+6));
 strcpy(inform.tituloRss, str);
 strcat(inform.tituloRss, "\n");
 contTitulo++;
 }
 else{
 char* str;
 str=substring(buf,p1+17,(p2-1)-(p1+17));
 strcat(inform.items, &numItem);
 if(contItem==1)
 {
 strcpy(inform.items, "1. ");
 }
 strcat(inform.items, str);
 strcat(inform.items, "\n");
 contItem++;
 sprintf(numItem, "%d", contItem);
 strcat(numItem, ". ");
 }

 }else if (_find(buf,"<author>")!=-1) {
 p1=_find(buf,"<author>");
 p2=_find(buf,"</author>");
 char* str;
 str=substring(buf,p1+8,(p2-1)-(p1+7));
 strcpy(inform.autorRss, str);
 strcat(inform.autorRss, "\n");
 }else if (_find(buf,"<link>")!=-1) {
 p1=_find(buf,"<link>");
 p2=_find(buf,"</link>");
 char* str;
 str=substring(buf,p1+6,(p2-1)-(p1+5));
 strcat(inform.fuentes, &numFuente);
 if(contFuente==1)
 {
 strcpy(inform.fuentes, "1. ");
 }
 strcat(inform.fuentes, str);
 strcat(inform.fuentes, "\n");
 contFuente++;
 sprintf(numFuente, "%d", contFuente);
 strcat(numFuente, ". ");
 }

 }
 return inform;

 }
 */

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

	//conectarBD();

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
	list<Noticia*>* noticias;
	callbackArray a;
	rc = sqlite3_exec(db, statement, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		fflush(stdout);
		sqlite3_free(zErrMsg);
		devolver = 1;
	} else {
		fprintf(stdout, "Operation done successfully\n");
		devolver = 0;

	}
	cerrarBD(db);
	return devolver;

}
/*void exportarXML(){
 sqlite3 *db;
 char *zErrMsg = 0;
 int rc,rc1;
 char *sql;
 string sqla;
 string sqld;
 string sqlt;

 const char* data = "Callback function called";
 // Open database
 //rc = sqlite3_open("xmlbd.s3db", &db);

 conectarBD(db,0);
 int (*callback)(void*, int, char**, char**);
 // Create SQL statement
 int i,var;
 rc1 = sqlite3_exec(db, "select count(*) from NOTICIA", callback, (void*)data, &zErrMsg);
 for(i = 0; i<rc1; i++){
 string nom = "RSS ";
 nom.append(i+".xml");
 const char *cnom = sqld.c_str();
 doc = fopen(cnom,"a+");
 for (var = 0; var < rc1; ++var) {

 sqla = "select AUTOR from NOTICIA  where COD_XML = "+i+" and COD_NOT = "+var;
 sqlt = "select TITULO from NOTICIA  where COD_XML = "+i+" and COD_NOT="+var;
 sqld = "select DESCRIPCION from NOTICIA  where COD_XML = "+i+" and COD_NOT="+var;

 const char *csqld = sqld.c_str();
 const char *csqlt = sqlt.c_str();
 const char *csqla = sqla.c_str();
 int (*callback)(void*, int, char**, char**);

 fprintf(doc,"<channel><title>");
 fprintf(doc,"%i",sqlite3_exec(db, csqlt, callback, (void*)data, &zErrMsg));
 fprintf(doc,"</title>\t");
 fprintf(doc,"<description><![CDATA[");
 fprintf(doc,"%i",sqlite3_exec(db, csqlt, callback, (void*)data, &zErrMsg));
 fprintf(doc,"]]</description>\t");
 fprintf(doc,"<author>");
 fprintf(doc,"%i",sqlite3_exec(db, csqla, callback, (void*)data, &zErrMsg));
 fprintf(doc,"</author>\t");

 }
 }
 if( rc != SQLITE_OK ){
 fprintf(stdout, "SQL error: %s\n", zErrMsg);
 sqlite3_free(zErrMsg);
 }else{
 fprintf(stdout, "Operation done successfully\n");
 }
 sqlite3_close(db);
 }*/
