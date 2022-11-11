#include<iostream>
#include"Donut.h"

int main() {
	pila* Pila = bakeVertexDonut(15.0f, 15.0f, 1, 1);
	/*for(int i = 0; i < 25; i++)
		Pila.store(0.0f, 0.0f, 0.0f);
	addUVIndex(&Pila, 4, 4);
	addIndexArray(&Pila, 1, 1);
	Pila.printStack();
	float* arreglo = Pila.getArrayVertex();*/
	Pila->printStack();
	return 0;
}