#ifndef DONUT_CLASS_H
#define DONUT_CLASS_H

#include<iostream>

typedef struct Node {
	float* data;
	Node* next;
	Node(float x, float y, float z) {
		data = new float[3];
		data[0] = x;
		data[1] = y;
		data[2] = z;
		next = nullptr;
	}
	Node(float u, float v) {
		data = new float[2];
		data[0] = u;
		data[1] = v;
		next = nullptr;
	}
}nodo;
typedef struct Stack {
	nodo* initV = nullptr;
	nodo* initT = nullptr;
	unsigned int sizeV = 0, sizeT = 0;
	void store(float x, float y, float z){
		nodo* nuevo = new nodo(x, y, z);
		if (initV == nullptr) {
			initV = nuevo;
			sizeV++;
			return ;
		}
		nodo* aux = initV;
		while (aux->next != nullptr)
			aux = aux->next;
		aux->next = nuevo;
		sizeV++;
	}
	void store(float u, float v) {
		nodo* nuevo = new nodo(u, v);
		if (initT == nullptr) {
			initT = nuevo;
			sizeT++;
			return ;
		}
		nodo* aux = initT;
		while (aux->next != nullptr)
			aux = aux->next;
		aux->next = nuevo;
		sizeT++;
	}

	void printStack() {
		if (sizeT != sizeV)
			std::cout << "Tamaño desigual" << std::endl;
		nodo* auxV = initV;
		nodo* auxT = initT;
		for (unsigned int i = 0; i < sizeT; i++) {
			std::cout << "Vertice (" << auxV->data[0] << "," << auxV->data[1] << "," << auxV->data[2] << ")\t";
			std::cout << "Textura (" << auxT->data[0] << "," << auxT->data[1] << ")\n";
			auxV = auxV->next;
			auxT = auxT->next;
		}
	}
	float* getArray() {
		float* arrayfloat = new float[sizeV * 5];
		nodo* auxV = initV;
		nodo* auxT = initT;
		for (unsigned int i = 0; i < sizeT; i ++) {
			arrayfloat[i*5 + 0] = auxV->data[0];
			arrayfloat[i*5 + 1] = auxV->data[1];
			arrayfloat[i*5 + 2] = auxV->data[2];
			arrayfloat[i*5 + 3] = auxT->data[0];
			arrayfloat[i*5 + 4] = auxT->data[1];
			auxV = auxV->next;
			auxT = auxT->next;
		}
		return arrayfloat;
	}
}pila;

float* bakeVertexDonut(float inRad, float forRad, unsigned int inQual, unsigned int forQual);
pila* makeCircle(float centerX, float centerY, unsigned int inQual);
void addUVIndex(pila* stack, unsigned int inQual, unsigned int forQual);


#endif // DONUT_CLASS_H