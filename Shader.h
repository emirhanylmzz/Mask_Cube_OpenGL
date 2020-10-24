#pragma once
#include <iostream>
#include "glm.hpp"
using namespace std;
class Shader
{
private:
	unsigned int m_RendererID;
public:
	Shader(const string& v, const string& f);
	~Shader();
	void Bind() const;
	void UnBind() const;
	//Set uniforms
	void SetUniform4f(const string& name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const string& name, int v0);
	void SetUniformMat4f(const string& name, const glm::mat4 matrix);
private:
	unsigned int CompileShader(unsigned int type, const string& source);
	unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
	int GetUniformLocation(const string& name);
};