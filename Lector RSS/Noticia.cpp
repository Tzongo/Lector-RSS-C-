/*
 * Noticia.cpp
 *
 *  Created on: 16 de may. de 2016
 *      Author: gotzon gerrikabeitia
 */

#include "Noticia.h"

Noticia::Noticia() {
	// TODO Auto-generated constructor stub

}
Noticia::Noticia(char titulo,char autor,char desc) {
	// TODO Auto-generated constructor stub
	this->titulo = titulo;
	this->autor = autor;
	this->descripcion = desc;
}
char* Noticia::getAutor(){
	return autor;
}
char* Noticia::getDescripcion(){
	return descripcion;
}
char* Noticia::getTitulo(){
	return titulo;
}
void Noticia::setTitulo(char titulo){
	this->titulo = titulo;
}
void Noticia::setAutor(char autor){
	this->autor = autor;
}
void Noticia::setDescripcion(char desc){
	this->descripcion = desc;
}
Noticia::~Noticia() {
	// TODO Auto-generated destructor stub
	delete[] this;
}

