/*
 * ArrayInt.cpp
 *
 *  Created on: 2/5/2016
 *      Author: Jon
 */

#include "ArrayInt.h"
namespace containers{

	ArrayInt::ArrayInt() {
		capacity = 10;
		array = new int[this->capacity];
	}

	ArrayInt::~ArrayInt() {
		delete[] array;
	}

	ArrayInt::ArrayInt(unsigned int capacity) {
		this->capacity = capacity;
		array = new int[this->capacity];
	}

	unsigned int ArrayInt::getCapacity() {
		return capacity;
	}

	int ArrayInt::getValue(unsigned int index) {
		return array[index];
	}

	void ArrayInt::setCapacity(unsigned int capacity) {
		this->capacity = capacity;
		int* nuevoArray;
		nuevoArray = new int[this->capacity];
		int i;
		for (i = 0; i < (sizeof(array)/sizeof(array[0])); i++)
		{
			nuevoArray[i] = array[i];
		}
		delete[] array;
		array = nuevoArray;
	}



}
