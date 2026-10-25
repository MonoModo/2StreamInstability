#pragma once

class FullscreenTriangle
{
public:
	FullscreenTriangle();
	~FullscreenTriangle();

	FullscreenTriangle(const FullscreenTriangle&) = delete;
	FullscreenTriangle& operator=(const FullscreenTriangle&) = delete;

	void draw() const;

private:
	unsigned int vao_ = 0;
	unsigned int vbo_ = 0;
};