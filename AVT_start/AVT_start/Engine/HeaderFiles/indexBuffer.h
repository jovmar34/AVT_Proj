#pragma once
#include <GL/glew.h>

class IndexBuffer {
private:
	GLuint m_RendererID;
	GLuint m_count;

public:
	IndexBuffer(const GLuint* data, GLuint count);
	~IndexBuffer();

	void bind();
	void unbind();
	inline GLuint getCount() { return m_count; }
};