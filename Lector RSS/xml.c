#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "funciones.h"
#include <string.h>
int main()
{
		FILE *ptr_file;
		char *buf;
		int s=-1;
		ptr_file =fopen("pruebasRss.xml","r");
		if (!ptr_file){
		printf("file not found!\n");
		getch();
		return 0;
		}

		fseek(ptr_file, 0, SEEK_END);
		s = ftell(ptr_file);
		fseek(ptr_file, 0, SEEK_SET);
		buf=(char*)malloc(s*sizeof(char));
		while (fgets(buf,s, ptr_file)!=NULL){
			printf(substr(buf,0,6));
			/*if (substr(buf,0,6) =="<item>") {
				printf("%s proba",buf);
			}*/
			//printf("%s",buf);
		}
	fclose(ptr_file);
	getch();
		return 0;
}
