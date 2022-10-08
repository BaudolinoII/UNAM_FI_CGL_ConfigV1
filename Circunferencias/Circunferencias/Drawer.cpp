#include "Drawer.h"

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
const int complement(double r) {
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
const int aprox(const int destiny, const int position) {
	if (destiny == position)
		return position;
	if (destiny > position)
		return position + 1;
	return position - 1;
}

Stack setCircle(const int radio, Vector centro) {
	Stack pila;
	int before = centro.y, past = centro.y, current = 0, oposite = 0, otherside = radio + centro.x;
	for (int i = (centro.x - radio); i <= (radio + centro.x); i++) {
		//std::cout << "Iteracion: " << i << "\t de " << (radio + centro.x) << std::endl;
		current = complement(sqrt(radio * radio - (i - centro.x) * (i - centro.x))) + centro.y;
		oposite = centro.y - complement(sqrt(radio * radio - (i - centro.x) * (i - centro.x)));
		while (absolute(current - before) > 1) {
			//std::cout << "Costura: [" << i - (i < centro.x ? 1 : 0) << "," << before << "]\t";
			pila.push(i - (i < centro.x ? 1 : 0), before);
			//std::cout << "[" << otherside + (i < centro.x ? 1 : 0) << "," << past << "]\n";
			pila.push(otherside + (i < centro.x ? 1 : 0), past);
			before = aprox(current, before);
			past = aprox(oposite, past);
		}
		//std::cout << "Progreso: [" << i << "," << current << "]";
		pila.push(i, current);
		//std::cout << "[" << otherside << "," << oposite << "]" << std::endl;
		pila.push(otherside, oposite);
		before = aprox(current, before);
		past = aprox(oposite, past);
		otherside--;

	}
	pila.push(centro.x, centro.y);
	//pila.printStack();
	return pila;
}
