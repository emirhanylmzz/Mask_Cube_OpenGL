#include <GL/glew.h>
#include <iostream>
#include "Renderer.h"
#include "gtc/matrix_transform.hpp"
#include "glm.hpp"
using namespace std;
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall()
{
	while (GLenum error = glGetError())
	{
		cout << "[OpenGL Error] (" << error << ")" << endl;
		return false;
	}
	return true;
}
void Renderer::clear() const
{
	GLCall(glEnable(GL_STENCIL_TEST));
	GLCall(glClearColor(1, 1, 1, 1));
	GLCall(glClearDepthf(1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT));
	GLCall(glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE));
}
void Renderer::draw(const VertexArray& va, Shader& shader, const glm::vec3 pos[], const int& size, const glm::mat4& pv) const
{
	va.Bind();
	shader.Bind();

	for (int i = 0; i < size; ++i)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), pos[i]);
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		glm::mat4 mvp = pv * model;

		shader.SetUniformMat4f("u_MVP", mvp);
		
		if (i == 0) { 
			GLCall(glDepthFunc(GL_LESS));
			GLCall(glEnable(GL_DEPTH_TEST));
			GLCall(glDepthMask(GL_TRUE));

			shader.SetUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);
			GLCall(glDrawArrays(GL_QUADS, 0, 24));
		}
		if (i == 1) {
			GLCall(glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE));
			GLCall(glDepthMask(GL_TRUE));
			GLCall(glDepthFunc(GL_LESS));
			
			shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);
			GLCall(glDrawArrays(GL_QUADS, 0, 24));
		}
	}
	glDisable(GL_DEPTH_TEST);
}	