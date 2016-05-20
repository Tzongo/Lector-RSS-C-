/*
 * Noticia.cpp
 *
 *  Created on: 16 de may. de 2016
 *      Author: gotzon gerrikabeitia
 */

#include "Noticia.h"
using namespace std;
Noticia::Noticia() {
	// TODO Auto-generated constructor stub
}
Noticia::Noticia(string titulo,string autor,string desc) {
	// TODO Auto-generated constructor stub
	this->titulo = titulo;
	this->autor = autor;
	this->descripcion = desc;
}
string Noticia::getAutor(void){
	return autor;
}
string Noticia::getDescripcion(void){
	return descripcion;
}
string Noticia::getTitulo(void){
	return titulo;
}
void Noticia::setTitulo(string titulo){
	this->titulo = titulo;
}
void Noticia::setAutor(string autor){
	this->autor = autor;
}
void Noticia::setDescripcion(string desc){
	this->descripcion = desc;
}
Noticia::~Noticia() {
	// TODO Auto-generated destructor stub
	delete[] this;
}

