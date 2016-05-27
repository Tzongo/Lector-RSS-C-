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

//	sqlite3 *db;
//	char *zErrMsg = 0;
//	int rc;
//	conectarBD(db, rc);

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
			char*  statement;
			char* noticia;
			bool continuar;
			continuar = true;
			char respuesta;
			char* modificacion;
			bool repetir2;
			repetir2 = true;
			do
			{
			statement = "SELECT COD_NOT,TITULO from NOTICIA";
			ejecutarComandoBD(statement);
			printf("\nIntroduzca el codigo de la noticia que desea modificar");
			fflush(stdout);
			scanf("%c",noticia);
			printf( "\n ");
			statement = "SELECT * from NOTICIA where COD_NOT = " + noticia + ";";
			ejecutarComandoBD(statement);
			printf( "\n¿Es esta la noticia que quieres modificar? (s/n) ");
			fflush(stdout);
			scanf("%i",respuesta);
			if (respuesta = "s") continuar = false;

			} while(continuar);
			do
			{
			printf( "\n¿Que desea modificar?  ");
			printf("\n"
					"1.\tTitulo\n"
					"2.\tAutor\n"
					"3.\tDescripcion\n"
					"4.\tSalir\n\n"
					"Introduzca numero de la funcion deseada:\n");
			fflush(stdout);
			char resultado;
			scanf("%i",respuesta);
			switch(respuesta)
			{
			case '1':
				printf( "\nIntroduzca el nuevo titulo : ");
				fflush(stdout);
				scanf("%c",modificacion);
				statement = "UPDATE NOTICIA SET TITULO = '"+ modificacion +"' WHERE ID = "+ noticia +";";
				ejecutarComandoBD(statement);
				printf( "\nEl titulo ha sido modificado ");
				fflush(stdout);
				break;
			case '2':
				printf( "\nIntroduzca el nuevo autor : ");
				fflush(stdout);
				scanf("%c",modificacion);
				statement = "UPDATE NOTICIA SET AUTOR = '"+ modificacion +"' WHERE ID = "+ noticia +";";
				ejecutarComandoBD(statement);
				printf( "\nEl autor  ha sido modificado ");
				fflush(stdout);
				break;
			case '3':
					printf( "\nIntroduzca la nueva descripcion : ");
					fflush(stdout);
					scanf("%c",modificacion);
					statement =
							"UPDATE NOTICIA SET DESC = '"
							+
							modificacion
							+
							"' WHERE ID = "
							+ noticia +
							";"
							;
					ejecutarComandoBD(statement);
					printf( "\nLa descripcion ha sido modificada ");
					fflush(stdout);
					break;
			case '4':
				repetir2 = false;
			break;
			default:
				printf("\nï¿½Opcion incorrecta!\n\n");
				break;
			}
			}while(repetir2);

			break;
		case '3':
		{
			list<Noticia*> noticias;
			string tituloRSS;
			printf("Introduce titulo del RSS: \n");
			fflush(stdout);

//			getline(cin, tituloRSS);
			/*scanf("%s", tituloRSS.c_str());
			fflush(stdin);*/
			cin >> tituloRSS;
			cout << endl;
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
			printf("\nï¿½Opcion incorrecta!\n\n");
			break;
		}
	} while (repetir);

	return 0;
}

