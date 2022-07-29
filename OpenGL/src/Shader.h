#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	void SetUniforms1i(const std::string& name, int v0);
	void SetUniforms4f(const std::string& name, float v0, float v2, float v3, float v4);
	void SetUniformsMat4f(const std::string& str, const glm::mat4& matrix);
private:
	int GetUniformLocation(const std::string& name) const;
	unsigned CompileShader(unsigned type, const std::string& source);
};

