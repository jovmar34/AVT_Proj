#include "..\HeaderFiles\indexBuffer.h"

IndexBuffer::IndexBuffer(const GLuint* data, GLuint count): m_count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
