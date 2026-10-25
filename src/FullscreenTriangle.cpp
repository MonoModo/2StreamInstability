#include "FullscreenTriangle.h"
#include "OpenGLFunctions.h"

FullscreenTriangle::FullscreenTriangle()
{
	auto& gl = OpenGLFunctions::get();
	const GLfloat vertices[] = { -1.0f, -1.0f, 3.0f, -1.0f, -1.0f, 3.0f };
	gl.genVertexArrays(1, &vao_);
	gl.bindVertexArray(vao_);
	gl.genBuffers(1, &vbo_);
	gl.bindBuffer(GL_ARRAY_BUFFER, vbo_);
	gl.bufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	gl.enableVertexAttribArray(0);
	gl.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	gl.bindVertexArray(0);
}

FullscreenTriangle::~FullscreenTriangle()
{
	if (vbo_ != 0)
		OpenGLFunctions::get().deleteBuffers(1, &vbo_);
	if (vao_ != 0)
		OpenGLFunctions::get().deleteVertexArrays(1, &vao_);
}

void FullscreenTriangle::draw() const
{
	auto& gl = OpenGLFunctions::get();
	gl.bindVertexArray(vao_);
	gl.drawArrays(GL_TRIANGLES, 0, 3);
	gl.bindVertexArray(0);
}