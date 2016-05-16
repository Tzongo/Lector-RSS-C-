/*
 * Noticia.h
 *
 *  Created on: 16 de may. de 2016
 *      Author: gotzon gerrikabeitia
 */

#ifndef NOTICIA_H_
#define NOTICIA_H_

class Noticia {
public:

	Noticia();
	Noticia(char titulo,char autor,char desc);
	virtual ~Noticia();

	char* getAutor() ;
	char* getDescripcion() ;
	char* getTitulo() ;
	void setAutor(char autor) ;
	void setDescripcion(char desc) ;
	void setTitulo(char titulo) ;


private:
	char titulo[];
	char autor[];
	char descripcion[];
};

#endif /* NOTICIA_H_ */
