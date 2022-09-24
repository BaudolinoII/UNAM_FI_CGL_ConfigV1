#include<iostream>
#include<ctgmath>
#include<string>

const unsigned int x10(const unsigned int n) {
	unsigned int p = 1, i = 0;
	for (; i < n; i++)
		p *= 10;
	return p;
}
const int toInt(const std::string args) {
	int n = 0;
	unsigned int i = (args[0] == '-' ? 1 : 0);
	for (; args[i] != '\0'; i++)
		n += x10(args.length() - i - 1) * (args[i] - 48);
	n *= (args[0] == '-' ? -1 : 1);
	return n;
}
const int complement(const float r) {
	float rp = (r > 0 ? r : r * -1);
	while (rp >= 1.0f)
		rp--;
	if (rp >= 0.0f && rp < 0.5f)
		return (int)r;
	return (int)(r + (r > 0 ? 1 : -1));
}

const int absolute(const int n) {
	return (n > 0 ? n : n * -1);
}

typedef struct vector {
public:
	int x = 0, y = 0;
	vector(std::string args) {
		unsigned int i = 0;
		for(; args[i] != '\0' ; i++)
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
	void push(const int x, const int y) {
		Nodo* nuevo = new Nodo(x, y, top);
		top = nuevo;
		size++;
	}
	void printStack() {
		Nodo* it = top;
		while (it != nullptr) {
			it->vec->printCoords();
			it = it->next;
		}
		std::cout << "tamanio de pila: " << size << std::endl;
	}
	float* getArrayPoints(const float adjust) {
		float* arrayPoints = new float[size * 3];
		Nodo* it = top;
		for (unsigned int i = 0; i < size; i++) {
			arrayPoints[3*i] = (float)(it->vec->x) * adjust;
			arrayPoints[3*i + 1] = (float)(it->vec->y) * adjust;
			arrayPoints[3*i + 2] = 0.0f;
			it = it->next;
		}
		return arrayPoints;
	}
} Stack;

float* setCircle(const unsigned int radio, Vector centro, const float adjust = 1.0f){
	Stack pila;
	int before = centro.y, past = centro.y, current = 0, oposite = 0, otherside = radio + centro.x;
	for (int i = (centro.x - radio); i < (radio + centro.x); i++) {
		current = complement(sqrt(radio * radio - (i - centro.x) * (i - centro.x))) + centro.y;
		oposite = centro.y - complement(sqrt(radio * radio - (i - centro.x) * (i - centro.x)));
		while(absolute(current - before) > 0){
			pila.push(i - 1 , before);
			pila.push(otherside + 1, past);
			before += (current > before ? 1 : -1);
			past   += (oposite > past ? 1 : -1);
		}
		pila.push(i, current);
		pila.push(otherside, oposite);
		before += (current >= before ? 1 : -1);
		past   += (oposite > past ? 1 : -1);
		otherside--;
	}
	return pila.getArrayPoints(adjust);
}

int main() {
	std::string args = "";
	unsigned int radio;
	/*std::cout << "Inserte Radio Circunferencia" << std::endl;
	std::cin >> args;
	radio = toInt(args);
	std::cout << "Inserte Posicion en X,Y" << std::endl;
	std::cin >> args;
	Vector centro(args);*/
	std::cout << complement(-9.5f) << std::endl;
	std::cout << complement(-9.0f);
	/*Stack pila;
	pila.push(1, 2);
	pila.push(2, 4);
	pila.push(3, 8);
	pila.push(4, 16);
	pila.printStack();
	float* arr = pila.getArrayPoints(1.5f);
	for (int i = 0; i < 12; i++)
		std::cout << " [" << arr[i] << "] ";*/
	return 0;
}