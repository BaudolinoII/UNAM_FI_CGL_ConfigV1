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
typedef struct Vector3D {
	float x = 0; float y = 0; float z = 0;
	Vector3D(float x, float y, float z) {
		const float x2 = x * x, y2 = y * y, z2 = z * z;
		float c = sqrt(abs(x2) + abs(y2) + abs(z2));
		this->x = x / c;
		this->y = y / c;
		this->z = z / c;
	}
}vec3;

typedef struct Stack {
	fnodo* initV = nullptr;
	fnodo* initT = nullptr;
	fnodo* initN = nullptr;
	inodo* initI = nullptr;
	unsigned int sizeV = 0, sizeT = 0, sizeI = 0, sizeN = 0;
	Stack() {
		sizeV = 0; sizeT = 0; sizeI = 0, sizeN = 0;
	}
	void store(float x, float y, float z) {
		fnodo* nuevo = new fnodo(x, y, z);
		//std::cout << "Vertice Almacenado: #" << sizeV << std::endl;
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
		//std::cout << "Textel Almacenado: #" << sizeT << std::endl;
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
		//std::cout << "Triangulo Almacenado: #" << sizeI << std::endl;
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
	void storeNormal(vec3 vector) {
		fnodo* nuevo = new fnodo(vector.x, vector.y, vector.z);
		//std::cout << "Normal Almacenada: #" << sizeN << std::endl;
		if (initN == nullptr) {
			initN = nuevo;
			sizeN++;
			return;
		}
		fnodo* aux = initN;
		while (aux->next != nullptr)
			aux = aux->next;
		aux->next = nuevo;
		sizeN++;
	}

	void printVertex() {
		fnodo* auxV = initV;
		while (auxV != nullptr) {
			std::cout << "v " << auxV->data[0] << "," << auxV->data[1] << "," << auxV->data[2] << std::endl;
			auxV = auxV->next;
		}
	}
	void printUV() {
		fnodo* auxT = initT;
		while (auxT != nullptr) {
			std::cout << "vt " << auxT->data[0] << "," << auxT->data[1] << std::endl;
			auxT = auxT->next;
		}
	}
	void printFaces() {
		inodo* auxI = initI;
		while (auxI != nullptr) {
			std::cout <<"f " << auxI->data[0] << " , " << auxI->data[1] << " , " << auxI->data[2] << std::endl;
			auxI = auxI->next;
		}
	}
	void printNormal() {
		fnodo* auxN = initN;
		while (auxN != nullptr) {
			std::cout <<"vn "<< auxN->data[0] << " , " << auxN->data[1] << " , " << auxN->data[2] << std::endl;
			auxN = auxN->next;
		}
	}

	float* getArrayVertex() {
		float* arrayfloat = new float[sizeV * 3];
		fnodo* auxV = initV;
		for (unsigned int i = 0; i < sizeV; i++) {
			arrayfloat[i * 3 + 0] = auxV->data[0];
			arrayfloat[i * 3 + 1] = auxV->data[1];
			arrayfloat[i * 3 + 2] = auxV->data[2];
			auxV = auxV->next;
		}
		return arrayfloat;
	}
	float* getArrayUV() {
		float* arrayfloat = new float[sizeT * 2];
		fnodo* auxT = initT;
		for (unsigned int i = 0; i < sizeT; i++) {
			arrayfloat[i * 2 + 0] = auxT->data[0];
			arrayfloat[i * 2 + 1] = auxT->data[1];
			auxT = auxT->next;
		}
		return arrayfloat;
	}
	float* getArrayNormal() {
		float* arrayfloat = new float[sizeN * 3];
		fnodo* auxN = initN;
		for (unsigned int i = 0; i < sizeN; i++) {
			arrayfloat[i * 3 + 0] = auxN->data[0];
			arrayfloat[i * 3 + 1] = auxN->data[1];
			arrayfloat[i * 3 + 2] = auxN->data[2];
			auxN = auxN->next;
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
float* constantCircle(const float radius, const unsigned int inQual);
pila* bakeVertexDonut(const float inRad, const float forRad, const unsigned int inQual, const unsigned int forQual);
Vector3D crossProduct(float dx, float dy, float dz, float ix, float iy, float iz);

#endif // DONUT_CLASS_H