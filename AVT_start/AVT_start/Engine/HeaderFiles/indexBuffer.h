#pragma once
#include <GL/glew.h>

class IndexBuffer {
private:
	GLuint m_idGL;
	GLuint m_count;

public:
	IndexBuffer(const GLushort* data, GLuint count);
	~IndexBuffer();

	void bind();
	void unbind();
	inline GLuint getCount() { return m_count; }
};