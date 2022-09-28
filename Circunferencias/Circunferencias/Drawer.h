#ifndef DRAWER_CLASS_H
#define DRAWER_CLASS_H

#include<iostream>
#include<ctgmath>
#include<string>

const unsigned int x10(const unsigned int n);
const int toInt(const std::string args);
const int complement(const float r);
const int absolute(const int n);
const int aprox(const int destiny, const int position);

typedef struct vector {
public:
	int x = 0, y = 0;
	vector(std::string args) {
		unsigned int i = 0;
		for (; args[i] != '\0'; i++)
			if (args[i] == ',') {
				x = toInt(args.substr(0, i));
				y = toInt(args.substr(i + 1, args.length() - i));
			}
	}
	vector(const int x, const int y) {
		this->x = x;
		this->y = y;
	}
	void printCoords() {
		std::cout << "X = " << x << "\tY = " << y << std::endl;
	}
} Vector;
typedef struct node {
	Vector* vec = nullptr;
	struct node* next = nullptr;
	node(const int x, const int y, struct node* next) {
		vec = new Vector(x, y);
		this->next = next;
	}
} Nodo;
typedef struct stack {
	unsigned int size = 0;
	Nodo* top = nullptr;
	int push(const int x, const int y) {
		Nodo* it = top;
		while (it != nullptr)
			if (it->vec->x == x && it->vec->y == y)
				return 1;
			else
				it = it->next;
		Nodo* nuevo = new Nodo(x, y, top);
		top = nuevo;
		size++;
		return 0;
	}
	void printStack() {
		Nodo* it = top;
		while (it != nullptr) {
			it->vec->printCoords();
			it = it->next;
		}
		std::cout << "tamanio de pila: " << size << std::endl;
	}
	float* getArrayPoints(const float adjust = 1.0f) {
		float* arrayPoints = new float[size * 3];
		Nodo* it = top;
		for (unsigned int i = 0; i < size; i++) {
			arrayPoints[3 * i] = (float)(it->vec->x) * adjust;
			arrayPoints[3 * i + 1] = (float)(it->vec->y) * adjust;
			arrayPoints[3 * i + 2] = 0.0f;
			it = it->next;
		}
		return arrayPoints;
	}
	unsigned int* getIndexArray() {
		unsigned int* index = new unsigned int[2 * (size - 1)];
		for (unsigned int i = 0; i < size - 1; i++) {
			index[2 * i] = 0;
			index[2 * i + 1] = i + 1;
		}
		return index;
	}
} Stack;

Stack setCircle(const int radio, Vector centro);

#endif //DRAWER_CLASS_H