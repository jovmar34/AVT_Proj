#pragma once
#include <GL/glew.h>

class VertexBuffer {
private:
	GLuint m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind();
	void unbind();
};