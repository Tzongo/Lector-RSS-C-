/*
 * main.cpp
 *
 *  Created on: 16 de may. de 2016
 *      Author: gotzon gerrikabeitia
 */
#include <stdio.h>
#include <iostream>
#include "Noticia.h"
using namespace std;
int main(void){
	Noticia* n= new Noticia("Patxi","Jon","Mikel");
	cout << n->getAutor();
}


