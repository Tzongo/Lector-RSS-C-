/*
 * Noticia.h
 *
 *  Created on: 16 de may. de 2016
 *      Author: gotzon gerrikabeitia
 */
using namespace std;
#include <string>
#ifndef NOTICIA_H_
#define NOTICIA_H_

class Noticia {
public:

	Noticia();
	Noticia(string titulo,string autor,string desc);
	virtual ~Noticia();

	string getAutor() ;
	string getDescripcion() ;
	string getTitulo() ;
	void setAutor(string autor) ;
	void setDescripcion(string desc) ;
	void setTitulo(string titulo) ;


private:
	string titulo;
	string autor;
	string descripcion;
};

#endif /* NOTICIA_H_ */
