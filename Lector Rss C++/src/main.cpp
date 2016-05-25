/*
 * main.cpp
 *
 *  Created on: 16 de may. de 2016
 *      Author: gotzon gerrikabeitia
 */
#include <stdio.h>
#include <iostream>
#include "Noticia.h"
#include "funciones.h"
#include <stdbool.h>
#include <list>
#include "sqlite3.h"
using namespace std;

int main(void) {
	char funcMenu;
	bool repetir;
	Noticia* n;

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	conectarBD(db, rc);

	do {
		repetir = true;
		funcMenu = mostrarMenu();
		switch (funcMenu) {
		case '1':
			printf("Introduce nombre (con extension) del archivo: \n");
			fflush(stdout);
			char nombre[20];
			scanf("%s", nombre);
			fflush(stdin);
			printf("%s", nombre);
			//abrirRss(nombre);
			printf("\n");
			break;
		case '2':
			break;
		case '3':
		{
			list<Noticia*> noticias;
			string tituloRSS;
			printf("Introduce titulo del RSS: \n");
			fflush(stdout);
			scanf("%s", tituloRSS.c_str());
			fflush(stdin);

			crearRss(tituloRSS, &noticias);
			//mostrarNoticia(nuevaNoticia());
			int i;
			for(i=0;i<noticias.size();i++)
			{
				mostrarNoticia(get(&noticias,i));
			}
		}
			break;
		case '4':
			printf("Introduce nombre (con extension) del archivo: \n");
			fflush(stdout);
			char nombreInf[20];
			scanf("%s", nombreInf);
			fflush(stdin);
			//Info inform; inform = infoRss(nombreInf);
			printf("%s\n\n", nombreInf);
			//printf("\tTITULO DEL RSS:\n\n");
			//printf("%s", inform.tituloRss);
			printf("\n\tAUTOR DEL RSS:\n\n");
			//printf("%s", inform.autorRss);
			printf("\n\tITEMS DEL RSS:\n\n");
			//printf("%s", inform.items);
			printf("\n\tFUENTES DEL RSS:\n\n");
			//printf("%s\n", inform.fuentes);
			break;
		case '5':
			repetir = false;
			break;
		default:
			printf("\n�Opcion incorrecta!\n\n");
			break;
		}
	} while (repetir);

	return 0;
}

