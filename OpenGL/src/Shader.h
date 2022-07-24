#pragma once

#include <string>
#include <unordered_map>

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
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	void SetUniforms4f(const std::string& name, float v0, float v2, float v3, float v4);
private:
	int GetUniformLocation(const std::string& name);
	unsigned CompileShader(unsigned type, const std::string& source);
};

