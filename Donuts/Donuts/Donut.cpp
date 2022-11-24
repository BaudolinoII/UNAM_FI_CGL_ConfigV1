#include"Donut.h"
#include<cmath>

#define PI 3.14159265358979323846f

void addUVIndex(pila* stack, const unsigned int inQual, const unsigned int forQual) {
	const float inFact = 1.0f / (float)(inQual);
	const float forFact = 1.0f / (float)(forQual);
	for (unsigned int i = 0; i <= forQual; i++)
		for (unsigned int j = 0; j <= inQual; j++) 
			stack->store((float)i * inFact, (float)j * forFact);
}
void addIndexArray(pila* stack, const unsigned int inQual, const unsigned int forQual) {
	unsigned int n = 0, nx = 0, ny = 0, nz = 0;
	float* iA = stack->getArrayVertex();
	float xd = 0.0f, yd = 0.0f, zd = 0.0f, xi = 0.0f, yi = 0.0f, zi = 0.0f;
	vec3 normal(0.0f, 0.0f, 0.0f);
	for (unsigned int i = 0; i < forQual; i++) {
		for (unsigned int j = 0; j < inQual - 1; j++) {
			nx = i * inQual + j + n; ny = (i + 1) * (inQual + 1) + j + 1, nz = (i + 1) * (inQual + 1) + j;
			stack->store(nx, ny, nz);
			xd = iA[ny * 3] - iA[nx * 3]; yd = iA[ny * 3 + 1] - iA[nx * 3 + 1]; zd = iA[ny * 3 + 2] - iA[nx * 3 + 2]; 
			xi = iA[nz * 3] - iA[nx * 3]; yi = iA[nz * 3 + 1] - iA[nx * 3 + 1]; zi = iA[nz * 3 + 2] - iA[nx * 3 + 2];
			/*std::cout << "valores obtenidos vector Pivote (" << nx * 3 << " ," << nx * 3 + 1 << " ," << nx * 3 + 2 << ")\n";
			std::cout << "valores obtenidos vector Derecha (" << ny * 3 << " ," << ny * 3 + 1 << " ," << ny * 3 + 2 << ")\n";
			std::cout << "valores obtenidos vector Izquierda (" << nz * 3 << " ," << nz * 3 + 1 << " ," << nz * 3 + 2 << ")\n";
			std::cout << "Vector derecha (" << xd << " ," << yd << " ," << zd << ") Vector Izquierda (" << xi << " ," << yi << " ," << zi << ")\n";*/
			normal = crossProduct(xd, yd, zd, xi, yi, zi);
			stack->storeNormal(normal);

			nx = i * inQual + j + n; ny = i * inQual + j + n + 1; nz = (i + 1) * (inQual + 1) + j + 1;
			stack->store(nx, ny, nz);
			xd = iA[ny * 3] - iA[nx * 3]; yd = iA[ny * 3 + 1] - iA[nx * 3 + 1]; zd = iA[ny * 3 + 2] - iA[nx * 3 + 2];
			xi = iA[nz * 3] - iA[nx * 3]; yi = iA[nz * 3 + 1] - iA[nx * 3 + 1]; zi = iA[nz * 3 + 2] - iA[nx * 3 + 2];
			/*std::cout << "valores obtenidos vector Pivote (" << nx * 3 << " ," << nx * 3 + 1 << " ," << nx * 3 + 2 << ")\n";
			std::cout << "valores obtenidos vector Derecha (" << ny * 3 << " ," << ny * 3 + 1 << " ," << ny * 3 + 2 << ")\n";
			std::cout << "valores obtenidos vector Izquierda (" << nz * 3 << " ," << nz * 3 + 1 << " ," << nz * 3 + 2 << ")\n";
			std::cout << "Vector derecha (" << xd << " ," << yd << " ," << zd << ") Vector Izquierda (" << xi << " ," << yi << " ," << zi << ")\n";*/
			normal = crossProduct(xd, yd, zd, xi, yi, zi);
		}
		n++;
	}
}
unsigned int getRealSubDiv(const int n) {
	if (n < 1)
		return 2;
	return 2*n + 2;
}
float* constantCircle(const float radius, const unsigned int inQual) {
	float* arrayCircle = new float[inQual];
	const float incX = PI * 2 / (float)(inQual-1);
	for (int i = 0; i < inQual; i++) {
		const float zeta = radius * (float)std::sin(incX * (float)i);
		arrayCircle[i] = (0.00001 < abs(zeta) ? zeta : 0.0f);
	}
	return arrayCircle;
}
pila* bakeVertexDonut(const float inRad, const float forRad, const unsigned int inQual, const unsigned int forQual) {
	pila stack;
	const unsigned int iQ = getRealSubDiv(inQual) + 1, fQ = getRealSubDiv(forQual);
	const float incAng = 2*PI / (float)fQ;
	float* inCircle = constantCircle(inRad, iQ);
	for (unsigned int i = 0; i <= fQ; i++) {
		const float pivX = forRad * std::cos(incAng * (float)i), pivZ = forRad * std::sin(incAng * (float)i);
		for (int j = 0; j < iQ; j++) {
			stack.store((0.00001 < abs(pivX) ? pivX : 0.0f), inCircle[j], (0.00001 < abs(pivZ) ? pivZ : 0.0f));
		}
	}
	addUVIndex(&stack, iQ - 1, fQ);
	addIndexArray(&stack, iQ - 1, fQ);
	return &stack;
}
vec3 crossProduct(float dx, float dy, float dz, float ix, float iy, float iz) {
	const float fx = dy * iz - iy * dz, fy = dx * iz - ix * dz, fz = dx * iy - ix * dy;
	return vec3(fx, fy, fz);
}