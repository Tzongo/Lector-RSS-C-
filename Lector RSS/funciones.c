/*
 * funciones.c
 *
 *  Created on: 13/4/2016
 *      Author: Jon
 */
#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char mostrarMenu()
{
	printf("MENU PRINCIPAL\n"
			"1.\tVisualizar RSS\n"
			"2.\tEditar RSS\n"
			"3.\tEstadisticas\n"
			"4.\tSalir\n\n"
			"Introduzca numero de la funcion deseada:\n");
	fflush(stdout);
	char resultado;
	resultado = getchar();
	fflush(stdin);
	return resultado;
}

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
		printf("\n�Archivo no encotrado!\n");
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
	getch();
	return 0;
}

