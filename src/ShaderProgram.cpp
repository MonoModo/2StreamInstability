#include "ShaderProgram.h"

#include "GLSLReader.h"
#include "OpenGLFunctions.h"

#include <stdexcept>

namespace
{
std::string withVersion(const std::string& source)
{
	if (source.compare(0, 8, "#version") == 0)
		return source;

#if defined(__EMSCRIPTEN__)
	return "#version 300 es\nprecision highp float;\n" + source;
#elif defined(__APPLE__)
	return "#version 150\n" + source;
#else
	return "#version 130\n" + source;
#endif
}

GLuint compileStage(GLenum type, const std::string& source)
{
	auto& gl = OpenGLFunctions::get();
	GLuint shader = gl.createShader(type);
	const char* source_pointer = source.c_str();
	gl.shaderSource(shader, 1, &source_pointer, nullptr);
	gl.compileShader(shader);

	GLint compiled = GL_FALSE;
	gl.getShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint log_length = 0;
		gl.getShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		std::string log(static_cast<size_t>(log_length > 1 ? log_length : 1), '\0');
		gl.getShaderInfoLog(shader, static_cast<GLsizei>(log.size()), nullptr, &log[0]);
		gl.deleteShader(shader);
		throw std::runtime_error("Shader compilation failed:\n" + log);
	}
	return shader;
}
}

ShaderProgram::ShaderProgram(const std::string& vertex_source, const std::string& fragment_source)
{
	auto& gl = OpenGLFunctions::get();
	const GLuint vertex_shader = compileStage(GL_VERTEX_SHADER, withVersion(vertex_source));
	GLuint fragment_shader = 0;
	try
	{
		fragment_shader = compileStage(GL_FRAGMENT_SHADER, withVersion(fragment_source));
	}
	catch (...)
	{
		gl.deleteShader(vertex_shader);
		throw;
	}

	program_ = gl.createProgram();
	gl.attachShader(program_, vertex_shader);
	gl.attachShader(program_, fragment_shader);
	gl.bindAttribLocation(program_, 0, "aPosition");
	gl.linkProgram(program_);
	gl.deleteShader(vertex_shader);
	gl.deleteShader(fragment_shader);

	GLint linked = GL_FALSE;
	gl.getProgramiv(program_, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		GLint log_length = 0;
		gl.getProgramiv(program_, GL_INFO_LOG_LENGTH, &log_length);
		std::string log(static_cast<size_t>(log_length > 1 ? log_length : 1), '\0');
		gl.getProgramInfoLog(program_, static_cast<GLsizei>(log.size()), nullptr, &log[0]);
		gl.deleteProgram(program_);
		program_ = 0;
		throw std::runtime_error("Shader program link failed:\n" + log);
	}
}

ShaderProgram::~ShaderProgram()
{
	if (program_ != 0)
		OpenGLFunctions::get().deleteProgram(program_);
}

void ShaderProgram::use() const
{
	OpenGLFunctions::get().useProgram(program_);
}

void ShaderProgram::unbind() const
{
	OpenGLFunctions::get().useProgram(0);
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
	OpenGLFunctions::get().uniform1f(uniformLocation(name), value);
}

void ShaderProgram::setVec3(const std::string& name, float x, float y, float z) const
{
	OpenGLFunctions::get().uniform3f(uniformLocation(name), x, y, z);
}

void ShaderProgram::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	OpenGLFunctions::get().uniform4f(uniformLocation(name), x, y, z, w);
}

int ShaderProgram::uniformLocation(const std::string& name) const
{
	auto found = uniform_locations_.find(name);
	if (found != uniform_locations_.end())
		return found->second;

	const int location = OpenGLFunctions::get().getUniformLocation(program_, name.c_str());
	uniform_locations_.emplace(name, location);
	return location;
}