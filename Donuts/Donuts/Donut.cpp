#include"Donut.h"

float* bakeVertexDonut(float inRad, float forRad, unsigned int inQual, unsigned int forQual){

}
pila* makeCircle(float centerX, float centerY, unsigned int inQual){}
void addUVIndex(pila* stack, unsigned int inQual, unsigned int forQual){
	const float facX = 1.0f / (float)forQual;
	const float facY = 1.0f / (float)inQual;
	for(unsigned int i = 0; i < forQual; i++)
		for (unsigned int j = 0; j < inQual; j++)
			stack->store((float)i * facX, (float)j * facY);
}