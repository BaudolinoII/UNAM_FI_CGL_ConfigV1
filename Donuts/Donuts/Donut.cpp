#include"Donut.h"
#include<cmath>

void addUVIndex(pila* stack, const unsigned int inQual, const unsigned int forQual) {
	const float inFact = 1.0f / (float)(inQual);
	const float forFact = 1.0f / (float)(forQual);
	for (unsigned int i = 0; i <= forQual; i++)
		for (unsigned int j = 0; j <= inQual; j++) 
			stack->store((float)i * inFact, (float)j * forFact);
}
void addIndexArray(pila* stack, const unsigned int inQual, const unsigned int forQual) {
	for (unsigned int i = 0; i < forQual; i++)
		for (unsigned int j = 0; j < inQual - 1; j++) {
			stack->store(j, (i + 1) * (inQual+1) + j, (i + 1) * (inQual+1) + j + 1);
			stack->store(j, j + 1, (i + 1) * (inQual+1) + j + 1);
		}
}
unsigned int getRealSubDiv(const int n) {
	if (n < 1)
		return 2;
	return 2*n + 2;
}

pila* bakeVertexDonut(const float inRad, const float forRad, const unsigned int inQual, const unsigned int forQual) {
	pila stack;
	const unsigned int iQ = getRealSubDiv(inQual) + 1, fQ = getRealSubDiv(forQual);
	const float incX = (inRad * 2) / (float)iQ;
	const float incAng = 6.2831853f / (float)fQ;
	for (unsigned int i = 0; i <= fQ; i++) {
		const float pivX = std::cos(incAng*(float)i), pivY = std::sin(incAng * (float)i);
		for (int j = 0; j <= (iQ/2); j++) {
			const float zeta = std::sqrt(inRad*inRad - ((float)j * incX - (inRad + forRad))* ((float)j * incX - (inRad + forRad)));
			stack.store(pivX * (float)j * incX, pivY * (float)j * incX, zeta);
		}
		for (int j = (iQ/2) - 1; j >= 0; j--) {
			const float zeta = std::sqrt(inRad * inRad - ((float)j * incX - (inRad + forRad)) * ((float)j * incX - (inRad + forRad)));
			stack.store(pivX * (float)j * incX, pivY * (float)j * incX, -zeta);
		}
	}
	addUVIndex(&stack, iQ - 1, fQ);
	addIndexArray(&stack, iQ - 1, fQ);
	return &stack;
}