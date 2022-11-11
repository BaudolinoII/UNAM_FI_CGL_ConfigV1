#ifndef DONUT_CLASS_H
#define DONUT_CLASS_H

#include<iostream>

typedef struct FloatNode {
	float* data;
	FloatNode* next;
	FloatNode(float x, float y, float z) {
		data = new float[3];
		data[0] = x;
		data[1] = y;
		data[2] = z;
		next = nullptr;
	}
	FloatNode(float u, float v) {
		data = new float[2];
		data[0] = u;
		data[1] = v;
		next = nullptr;
	}
}fnodo;
typedef struct IntNode {
	unsigned int* data;
	IntNode* next;
	IntNode(unsigned int x, unsigned int y, unsigned int z) {
		data = new unsigned int[3];
		data[0] = x;
		data[1] = y;
		data[2] = z;
		next = nullptr;
	}
}inodo;

typedef struct Stack {
	fnodo* initV = nullptr;
	fnodo* initT = nullptr;
	inodo* initI = nullptr;
	unsigned int sizeV = 0, sizeT = 0, sizeI = 0;
	Stack() {
		std::cout << "Tamanio original: " << sizeT << "\t" << sizeV << std::endl;
	}
	void store(float x, float y, float z) {
		fnodo* nuevo = new fnodo(x, y, z);
		std::cout << "Vertice Almacenado: #" << sizeV << std::endl;
		if (initV == nullptr) {
			initV = nuevo;
			sizeV++;
			return;
		}
		fnodo* aux = initV;
		while (aux->next != nullptr)
			aux = aux->next;
		aux->next = nuevo;
		sizeV++;
	}
	void store(float u, float v) {
		fnodo* nuevo = new fnodo(u, v);
		std::cout << "Textel Almacenado: #" << sizeT << std::endl;
		if (initT == nullptr) {
			initT = nuevo;
			sizeT++;
			return;
		}
		fnodo* aux = initT;
		while (aux->next != nullptr)
			aux = aux->next;
		aux->next = nuevo;
		sizeT++;
	}
	void store(unsigned int x, unsigned int y, unsigned int z) {
		inodo* nuevo = new inodo(x, y, z);
		std::cout << "Triangulo Almacenado: #" << sizeI << std::endl;
		if (initI == nullptr) {
			initI = nuevo;
			sizeI++;
			return;
		}
		inodo* aux = initI;
		while (aux->next != nullptr)
			aux = aux->next;
		aux->next = nuevo;
		sizeI++;
	}

	void printStack() {
		if (sizeT != sizeV) {
			std::cout << "Tamanio desigual: " << sizeT <<"\t"<< sizeV <<std::endl;
			return;
		}
		fnodo* auxV = initV;
		fnodo* auxT = initT;
		/*for (unsigned int i = 0; i < sizeV; i++) {
			std::cout << "Vertice (" << auxV->data[0] << "," << auxV->data[1] << "," << auxV->data[2] << ")\t";
			std::cout << "Textura (" << auxT->data[0] << "," << auxT->data[1] << ")\n";
			auxV = auxV->next;
			auxT = auxT->next;
		}*/
		inodo* auxI = initI;
		for (unsigned int i = 0; i < sizeI; i++) {
			std::cout << auxI->data[0] << " , " << auxI->data[1] << " , " << auxI->data[2] << std::endl;
			auxI = auxI->next;
		}
	}
	float* getArrayVertex() {
		float* arrayfloat = new float[sizeV * 5];
		fnodo* auxV = initV;
		fnodo* auxT = initT;
		for (unsigned int i = 0; i < sizeT; i++) {
			arrayfloat[i * 5 + 0] = auxV->data[0];
			arrayfloat[i * 5 + 1] = auxV->data[1];
			arrayfloat[i * 5 + 2] = auxV->data[2];
			arrayfloat[i * 5 + 3] = auxT->data[0];
			arrayfloat[i * 5 + 4] = auxT->data[1];
			auxV = auxV->next;
			auxT = auxT->next;
		}
		return arrayfloat;
	}
	unsigned int* getArrayIndex() {
		unsigned int* arrayInt = new unsigned int [sizeI * 3];
		inodo* auxI = initI;
		for (unsigned int i = 0; i < sizeI; i++) {
			arrayInt[i * 3 + 0] = auxI->data[0];
			arrayInt[i * 3 + 1] = auxI->data[1];
			arrayInt[i * 3 + 2] = auxI->data[2];
			auxI = auxI->next;
		}
		return arrayInt;
	}
}pila;

void addUVIndex(pila* stack, const unsigned int inQual, const unsigned int forQual);
void addIndexArray(pila* stack, const unsigned int inQual, const unsigned int forQual);
unsigned int getRealSubDiv(const int n);
pila* bakeVertexDonut(const float inRad, const float forRad, const unsigned int inQual, const unsigned int forQual);


#endif // DONUT_CLASS_H