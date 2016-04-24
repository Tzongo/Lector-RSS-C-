#include <libxml/parser.h>
int main(void)
{
xmlDocPtr doc = NULL;
xmlNodePtr nodo;
doc = xmlParseFile("pruebasRss.xml"); // linea 5
if(!doc) // error (comunmente que el archivo no existe)
return -1;
nodo = xmlDocGetRootElement(doc); // linea 10
// veamos como se llama nuestra raiz:
printf("%sn" , nodo->name);
// Nos movemos al nodo hijo, e imprimimos su nombre
nodo = nodo->xmlChildrenNode; // linea 16
while(xmlNodeIsText(nodo) && nodo) // linea 17
nodo = nodo->next; // linea 18
printf("%sn", nodo->name);
// extraemos la informaci�n del nodo y la imprimimos
xmlChar *text = xmlNodeListGetString(doc, nodo->xmlChildrenNode,1);
printf("%sn", text); // linea 23
xmlFreeDoc(doc);
// aljover.com
return 1;
}
