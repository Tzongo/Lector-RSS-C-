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
		int p1,p2;
		while (fgets(buf,s, ptr_file)!=NULL){
			if (_find(buf,"<item>")!=-1) {
				printf("\nNuevo Item:-----------------------\n");
			}else if (_find(buf,"<title>")!=-1) {
				p1=_find(buf,"<title>");
				p2=_find(buf,"]]></title>");
				char* str;
				str=substring(buf,p1+17,(p2-1)-(p1+17));
				printf("%s\n",str);
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
				/*p1=_find(buf,"<description>");
				p2=_find(buf,"]]></description>");
				char* str;
				str=substring(buf,p1+23,(p2-1)-(p1+23));
				printf("%s\n",str);*/
				printf("Fin Item;-------------------\n");
			}
			else if(_find(buf,"</rss>")!=-1){
				return 0;
			}
		}
	fclose(ptr_file);
	getch();
		return 0;
}
