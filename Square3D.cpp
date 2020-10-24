#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#pragma comment(lib, "glu32.lib")
using namespace std;
//Window dimentions
string readFile(const char* filePath);
int main() 
{
	//Initialisation glfw
	if (!glfwInit()) {
		cerr << "GLFW initialisation failed!";
		glfwTerminate();
		return 1;
	}

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
	if (!mainWindow)
	{
		cerr << "Window creation failed!" << endl;
		glfwTerminate();
		return 1;
	}
	//Set context for glew to use
	glfwMakeContextCurrent(mainWindow);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		cerr << "Glew initialisation failed!" << endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	{
		GLfloat positions[] =
		{
			-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
			 1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
			-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
			-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
			-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
			-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
		};
		VertexArray vao;
		VertexBuffer vb(positions, sizeof(positions));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		vao.AddBuffer(vb, layout);
	
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 pv = proj * view; 

		string vertexShader = readFile("vertex.shader");
		string fragmentShader = readFile("fragment.shader");
		Shader shader(vertexShader, fragmentShader);

		glm::vec3 cubePositions[] = {
			glm::vec3(1.0f, -1.0f, 0.0f),
			glm::vec3(0.0f,  0.0f, 0.0f),
		};
		
		vao.UnBind();
		vb.UnBind();
		shader.UnBind();
		Renderer renderer;
		while (!glfwWindowShouldClose(mainWindow))
		{
			renderer.clear();
			shader.Bind();
			renderer.draw(vao, shader, cubePositions, 2, pv);
			glfwSwapBuffers(mainWindow);
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return (0);
}
string readFile(const char* filePath) {
	string content;
	ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		cerr << "Could not read file!\n" << filePath << ". File does not exist!\n" << endl;
		return "";
	}

	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}