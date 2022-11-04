#include<iostream>
#include"Donut.h"

int main() {
	pila Pila;
	Pila.store(0.0f, 0.0f, 1.0f);
	Pila.store(0.0f, 1.0f, 1.0f);
	Pila.store(1.0f, 0.0f, 1.0f);
	Pila.store(1.0f, 1.0f, 1.0f);
	Pila.store(0.0f, 0.0f);
	Pila.store(0.0f, 0.5f);
	Pila.store(0.5f, 0.0f);
	Pila.store(0.5f, 0.5f);
	Pila.printStack();
	float* arreglo = Pila.getArray();
	for (unsigned int i = 0; i < Pila.sizeV * 5; i++)
		std::cout << arreglo[i] << (i % 5 == 4 ? "\n":" , ");
	
	return 0;
}