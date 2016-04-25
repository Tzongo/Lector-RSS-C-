#include <libxml/parser.h>
#include <iconv.h>
int main(void)
{
xmlDocPtr doc = NULL;
xmlNodePtr nodo;
doc = xmlParseFile("pruebasRss.xml");
if(!doc)
return -1;
nodo = xmlDocGetRootElement(doc);
printf("%sn" , nodo->name);
nodo = nodo->xmlChildrenNode;
while(xmlNodeIsText(nodo) && nodo)
nodo = nodo->next;
printf("%sn", nodo->name);
xmlChar *text = xmlNodeListGetString(doc, nodo->xmlChildrenNode,1);
printf("%sn", text);
xmlFreeDoc(doc);
return 1;
}
