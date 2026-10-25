#pragma once

#include <GLFW/glfw3.h>

#include <cstddef>

namespace OpenGLFunctions
{
struct API
{
	using CreateShader = GLuint (APIENTRY *)(GLenum);
	using ShaderSource = void (APIENTRY *)(GLuint, GLsizei, const char* const*, const GLint*);
	using CompileShader = void (APIENTRY *)(GLuint);
	using GetShaderiv = void (APIENTRY *)(GLuint, GLenum, GLint*);
	using GetShaderInfoLog = void (APIENTRY *)(GLuint, GLsizei, GLsizei*, char*);
	using DeleteShader = void (APIENTRY *)(GLuint);
	using CreateProgram = GLuint (APIENTRY *)();
	using AttachShader = void (APIENTRY *)(GLuint, GLuint);
	using BindAttribLocation = void (APIENTRY *)(GLuint, GLuint, const char*);
	using LinkProgram = void (APIENTRY *)(GLuint);
	using GetProgramiv = void (APIENTRY *)(GLuint, GLenum, GLint*);
	using GetProgramInfoLog = void (APIENTRY *)(GLuint, GLsizei, GLsizei*, char*);
	using DeleteProgram = void (APIENTRY *)(GLuint);
	using UseProgram = void (APIENTRY *)(GLuint);
	using GetUniformLocation = GLint (APIENTRY *)(GLuint, const char*);
	using Uniform1f = void (APIENTRY *)(GLint, GLfloat);
	using Uniform3f = void (APIENTRY *)(GLint, GLfloat, GLfloat, GLfloat);
	using Uniform4f = void (APIENTRY *)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
	using GenVertexArrays = void (APIENTRY *)(GLsizei, GLuint*);
	using BindVertexArray = void (APIENTRY *)(GLuint);
	using DeleteVertexArrays = void (APIENTRY *)(GLsizei, const GLuint*);
	using GenBuffers = void (APIENTRY *)(GLsizei, GLuint*);
	using BindBuffer = void (APIENTRY *)(GLenum, GLuint);
	using BufferData = void (APIENTRY *)(GLenum, std::ptrdiff_t, const void*, GLenum);
	using DeleteBuffers = void (APIENTRY *)(GLsizei, const GLuint*);
	using EnableVertexAttribArray = void (APIENTRY *)(GLuint);
	using VertexAttribPointer = void (APIENTRY *)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
	using DrawArrays = void (APIENTRY *)(GLenum, GLint, GLsizei);

	CreateShader createShader;
	ShaderSource shaderSource;
	CompileShader compileShader;
	GetShaderiv getShaderiv;
	GetShaderInfoLog getShaderInfoLog;
	DeleteShader deleteShader;
	CreateProgram createProgram;
	AttachShader attachShader;
	BindAttribLocation bindAttribLocation;
	LinkProgram linkProgram;
	GetProgramiv getProgramiv;
	GetProgramInfoLog getProgramInfoLog;
	DeleteProgram deleteProgram;
	UseProgram useProgram;
	GetUniformLocation getUniformLocation;
	Uniform1f uniform1f;
	Uniform3f uniform3f;
	Uniform4f uniform4f;
	GenVertexArrays genVertexArrays;
	BindVertexArray bindVertexArray;
	DeleteVertexArrays deleteVertexArrays;
	GenBuffers genBuffers;
	BindBuffer bindBuffer;
	BufferData bufferData;
	DeleteBuffers deleteBuffers;
	EnableVertexAttribArray enableVertexAttribArray;
	VertexAttribPointer vertexAttribPointer;
	DrawArrays drawArrays;
};

API& get();
void initialize();
}