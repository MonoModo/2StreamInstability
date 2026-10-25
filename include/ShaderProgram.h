#pragma once

#include <string>
#include <unordered_map>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertex_source, const std::string& fragment_source);
	~ShaderProgram();

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

	void use() const;
	void unbind() const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;

private:
	int uniformLocation(const std::string& name) const;

	unsigned int program_ = 0;
	mutable std::unordered_map<std::string, int> uniform_locations_;
};