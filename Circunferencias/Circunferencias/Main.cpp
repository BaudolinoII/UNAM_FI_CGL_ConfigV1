#include<iostream>
#include<string>
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);
const unsigned int x10(const unsigned int n);
const int toInt(const std::string args);
const int complement(double r);
const int absolute(const int n);
const int aprox(const int destiny, const int position);

const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -15.0f;

float vertices[] = {
	 0.5f, 0.5f,0.0f,
	 0.5f,-0.5f,0.0f,
	-0.5f, 0.5f,0.0f,
	 0.5f,-0.5f,0.0f,
	-0.5f, 0.5f,0.0f,
	-0.5f,-0.5f,0.0f
};

int main() {

	std::string args;
	std::cout << "Programa Listo para Iniciar: " << std::endl << "Inserte el tamanio del Radio: ";
	std::cin >> args;
	int radio = absolute(toInt(args));
	std::cout << std::endl << "Coloque el centro en el siguiente formato x,y" << std::endl;
	std::cin >> args;
	int x = 0, y = 0;
	for (unsigned int i = 0; args[i] != '\0'; i++)
		if (args[i] == ',') {
			x = toInt(args.substr(0, i));
			y = toInt(args.substr(i + 1, args.length() - i));
		}
	glm::vec3 centro((float)x, (float)y, 0.0f);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1", nullptr, nullptr);
	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);

	while (!glfwWindowShouldClose(window)) {//////////////////////////////////////MAIN LOOP////////////////////////////////////////
		Inputs(window);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::translate(glm::mat4(1), glm::vec3(movX, movY, movZ));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = glGetUniformLocation(ourShader.Program, "color");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		glBindVertexArray(VAO);
		model = glm::translate(model, centro);
		color = glm::vec3(0.0f, 0.5f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 24);

		color = glm::vec3(0.5f, 0.5f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		int beforeY = y, currentY = y, oppositeY = y, pastY = y;
		for (int i = x - radio; i <= x + radio; i++) {
			currentY = complement(sqrt(radio * radio - (i - x) * (i - x))) + y;
			oppositeY = y - complement(sqrt(radio * radio - (i - x) * (i - x)));
			while (absolute(currentY - beforeY) > 0) {
				if (i >= x) {
					beforeY = aprox(currentY, beforeY);
					pastY = aprox(oppositeY, pastY);
				}
				model = glm::translate(glm::mat4(1), glm::vec3((float)(i - (i < x ? 1 : 0)), (float)beforeY, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 24);
				model = glm::translate(glm::mat4(1), glm::vec3((float)(i - (i < x ? 1 : 0)), (float)pastY, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 24);
				if (i < x) {
					beforeY = aprox(currentY, beforeY);
					pastY = aprox(oppositeY, pastY);
				}
			}
			model = glm::translate(glm::mat4(1), glm::vec3((float)i, (float)currentY, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 24);
			model = glm::translate(glm::mat4(1), glm::vec3((float)i, (float)oppositeY, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 24);
		}

		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}


void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.008f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.008f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movY += 0.008f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movY -= 0.008f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		movZ -= 0.008f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		movZ += 0.008f;
}
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