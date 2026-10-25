#include "OpenGLFunctions.h"

#include <stdexcept>
#include <string>

namespace OpenGLFunctions
{
namespace
{
API api{};

template <typename Function>
Function load(const char* name)
{
	GLFWglproc function = glfwGetProcAddress(name);
	if (function == nullptr)
		throw std::runtime_error(std::string("OpenGL function is unavailable: ") + name);
	return reinterpret_cast<Function>(function);
}
}

API& get()
{
	return api;
}

void initialize()
{
	api.createShader = load<API::CreateShader>("glCreateShader");
	api.shaderSource = load<API::ShaderSource>("glShaderSource");
	api.compileShader = load<API::CompileShader>("glCompileShader");
	api.getShaderiv = load<API::GetShaderiv>("glGetShaderiv");
	api.getShaderInfoLog = load<API::GetShaderInfoLog>("glGetShaderInfoLog");
	api.deleteShader = load<API::DeleteShader>("glDeleteShader");
	api.createProgram = load<API::CreateProgram>("glCreateProgram");
	api.attachShader = load<API::AttachShader>("glAttachShader");
	api.bindAttribLocation = load<API::BindAttribLocation>("glBindAttribLocation");
	api.linkProgram = load<API::LinkProgram>("glLinkProgram");
	api.getProgramiv = load<API::GetProgramiv>("glGetProgramiv");
	api.getProgramInfoLog = load<API::GetProgramInfoLog>("glGetProgramInfoLog");
	api.deleteProgram = load<API::DeleteProgram>("glDeleteProgram");
	api.useProgram = load<API::UseProgram>("glUseProgram");
	api.getUniformLocation = load<API::GetUniformLocation>("glGetUniformLocation");
	api.uniform1f = load<API::Uniform1f>("glUniform1f");
	api.uniform3f = load<API::Uniform3f>("glUniform3f");
	api.uniform4f = load<API::Uniform4f>("glUniform4f");
	api.genVertexArrays = load<API::GenVertexArrays>("glGenVertexArrays");
	api.bindVertexArray = load<API::BindVertexArray>("glBindVertexArray");
	api.deleteVertexArrays = load<API::DeleteVertexArrays>("glDeleteVertexArrays");
	api.genBuffers = load<API::GenBuffers>("glGenBuffers");
	api.bindBuffer = load<API::BindBuffer>("glBindBuffer");
	api.bufferData = load<API::BufferData>("glBufferData");
	api.deleteBuffers = load<API::DeleteBuffers>("glDeleteBuffers");
	api.enableVertexAttribArray = load<API::EnableVertexAttribArray>("glEnableVertexAttribArray");
	api.vertexAttribPointer = load<API::VertexAttribPointer>("glVertexAttribPointer");
	api.drawArrays = load<API::DrawArrays>("glDrawArrays");
}
}