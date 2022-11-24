#include<iostream>
#include"Donut.h"

int main() {
	pila* Pila = bakeVertexDonut(15.0f, 15.0f, 4, 4);
	/*for(int i = 0; i < 25; i++)
		Pila.store(0.0f, 0.0f, 0.0f);
	addUVIndex(&Pila, 4, 4);
	addIndexArray(&Pila, 1, 1);
	Pila.printStack();
	float* arreglo = Pila.getArrayVertex();*/
	Pila->printVertex();
	Pila->printUV();
	Pila->printFaces();
	Pila->printNormal();
	/*const unsigned int n = getRealSubDiv(9) + 1;
	float* circle = constantCircle(10.0f, n);
	for (unsigned int i = 0; i < n; i++) {
		std::cout << circle[i] << std::endl;
	}*/
	return 0;
}