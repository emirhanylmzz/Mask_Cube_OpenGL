#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include "VertexArray.h"
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall())
void GLClearError();
bool GLLogCall();

class Renderer
{
private:
public:
	void clear() const;
	void draw(const VertexArray& va, Shader& shader, const glm::vec3 pos[], const int& size, const glm::mat4& pv) const;
};