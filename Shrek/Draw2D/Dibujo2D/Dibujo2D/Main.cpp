#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;
float	movX = 0.0f,
movY = 0.0f,
movZ = -7.5f;

void Inputs(GLFWwindow* window);

int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shaders/core.vs", "Shaders/core.frag");

	GLfloat vertices[] = {
		-0.403f,  1.762f, 0.0f,		0.69f,0.87f, 0.22f,//0
		-0.613f,  1.647f, 0.0f,		0.50f,0.65f, 0.08f,//1
		-0.668f,  1.623f, 0.0f,		0.35f,0.47f, 0.00f,//2
		-0.605f,  1.702f, 0.0f,		0.50f,0.65f, 0.08f,//3
		-0.521f,  1.741f, 0.0f,		0.61f,0.78f, 0.13f,//4
		-0.734f,  1.527f, 0.0f,		0.35f,0.47f, 0.00f,//5
		-0.204f,  1.715f, 0.0f,		0.69f,0.87f, 0.22f,//6
		-0.264f,  1.744f, 0.0f,		0.69f,0.87f, 0.22f,//7
		-0.367f,  1.727f, 0.0f,		0.69f,0.87f, 0.22f,//8
		-0.742f,  1.432f, 0.0f,		0.18f,0.22f, 0.08f,//9
		-0.719f,  1.504f, 0.0f,		0.35f,0.47f, 0.00f,//10
		-0.604f,  1.575f, 0.0f,		0.50f,0.65f, 0.08f,//11
		-0.443f,  1.544f, 0.0f,		0.61f,0.78f, 0.13f,//12
		-0.607f,  1.534f, 0.0f,		0.35f,0.47f, 0.00f,//13
		-0.343f,  1.667f, 0.0f,		0.50f,0.65f, 0.08f,//14
		-0.260f,  1.671f, 0.0f,		0.69f,0.87f, 0.22f,//15
		-0.174f,  1.663f, 0.0f,		0.69f,0.87f, 0.22f,//16
		-0.695f,  1.470f, 0.0f,		0.18f,0.22f, 0.08f,//17
		-0.549f,  1.494f, 0.0f,		0.18f,0.22f, 0.08f,//18
		-0.493f,  1.510f, 0.0f,		0.18f,0.22f, 0.08f,//19
		-0.376f,  1.539f, 0.0f,		0.18f,0.22f, 0.08f,//20
		-0.370f,  1.597f, 0.0f,		0.50f,0.65f, 0.08f,//21
		-0.268f,  1.615f, 0.0f,		0.18f,0.22f, 0.08f,//22
		-0.191f,  1.639f, 0.0f,		0.18f,0.22f, 0.08f,//23
		-0.158f,  1.642f, 0.0f,		0.18f,0.22f, 0.08f,//24
		-0.757f,  1.296f, 0.0f,		0.10f,0.13f, 0.03f,//25
		-0.852f,  1.401f, 0.0f,		0.10f,0.13f, 0.03f,//26
		-0.762f,  1.398f, 0.0f,		0.50f,0.65f, 0.08f,//27
		-0.971f,  1.466f, 0.0f,		0.50f,0.65f, 0.08f,//28
		-0.934f,  1.389f, 0.0f,		0.10f,0.13f, 0.03f,//29
		-1.003f,  1.331f, 0.0f,		0.50f,0.65f, 0.08f,//30
		-0.863f,  1.349f, 0.0f,		0.10f,0.13f, 0.03f,//31
		-0.789f,  1.332f, 0.0f,		0.10f,0.13f, 0.03f,//32
		-1.005f,  1.466f, 0.0f,		0.10f,0.13f, 0.03f,//33
		-1.027f,  1.435f, 0.0f,		0.10f,0.13f, 0.03f,//34
		-1.029f,  1.364f, 0.0f,		0.10f,0.13f, 0.03f,//35
		-0.505f,  1.430f, 0.0f,		0.10f,0.13f, 0.03f,//36
		-0.624f,  1.424f, 0.0f,		0.10f,0.13f, 0.03f,//37
		-0.676f,  1.321f, 0.0f,		0.10f,0.13f, 0.03f,//38
		-0.613f,  1.399f, 0.0f,		0.92f,0.93f, 0.88f,//39
		-0.595f,  1.354f, 0.0f,		0.92f,0.93f, 0.88f,//40
		-0.653f,  1.350f, 0.0f,		0.92f,0.93f, 0.88f,//41
	};
	const unsigned int nIndices = 131;
	unsigned int indices[] = {
		//3				6			9			12			15			18			21
		1,2,5		,1,2,3		,3,1,4		,5,4,6		,4,0,8		,0,8,7		,7,8,6,		//21
		5,9,10		,5,10,11	,10,11,13	,11,12,13	,11,12,14	,12,14,15	,15,16,6,	//42
		14,15,6		,9,10,18	,17,10,13	,17,13,19	,13,19,12	,12,20,21	,20,21,22,	//63
		21,22,15	,23,15,16	,23,16,24	,23,15,24	,23,15,22	,9,27,25	,25,26,27,	//84
		26,31,32	,26,28,29	,26,29,31	,29,30,31	,28,29,30	,28,34,33	,34,30,28,	//105
		25,18,17	,25,18,9	,36,37,18	,18,19,36	,12,19,20	,36,37,38	,37,38,39,	//126
		38,40,41	,39,40,41	,25,37,38	
	};

	GLuint VBO, VAO ,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. Despues colocamos las caracteristicas de los vertices
	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glm::mat4 projection = glm::mat4(1);
	glPointSize(5);
	//Creación de proyecciones
	projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 1000.0f);
	while (!glfwWindowShouldClose(window)){
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		Inputs(window);
		glfwPollEvents();
		// Render
		// Clear the colorbuffer
		glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);

		view = glm::translate(view, glm::vec3(movX, movY, movZ));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, (GLvoid*)(0 * sizeof(GLfloat)));
		//glDrawArrays(GL_POINTS, 0, 9);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}

const float speed = 0.004f;

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX += speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX -= speed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movY += speed;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movY -= speed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		movZ -= speed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		movZ += speed;
}