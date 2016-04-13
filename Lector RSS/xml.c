/*
 * xml.c
 *
 *  Created on: 13 de abr. de 2016
 *      Author: gotzo
 */
#include <expat.h>
#include <stdio.h>
#include <string.h>
int Parse(FILE *in_Stream) {
  XML_Parser p = XML_ParserCreate(NULL);
  if (! p) {
    fprintf(stderr, "Couldn't allocate memory for parser\n");
    return -1;
  }
  XML_UseParserAsHandlerArg(p);
  XML_SetElementHandler(p, start_hndl, end_hndl);
  XML_SetCharacterDataHandler(p, char_hndl);
  XML_SetProcessingInstructionHandler(p, proc_hndl);
  char buff;
  int  done = 0;
  for (fread(&buff, sizeof(char), 1, in_Stream); !feof(in_Stream); fread(&buff, sizeof(char), 1, in_Stream))
     if (! XML_Parse(p, &buff, sizeof(char), done)) {
        fprintf(stderr, "Parse error at line %d:\n%s\n",
          XML_GetCurrentLineNumber(p),
          XML_ErrorString(XML_GetErrorCode(p)));
        return -1;
     }
  return 0;
}

