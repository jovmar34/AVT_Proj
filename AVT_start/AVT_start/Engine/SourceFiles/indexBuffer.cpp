#include "..\HeaderFiles\indexBuffer.h"

IndexBuffer::IndexBuffer(const GLushort* data, GLuint count): m_count(count)
{
	glGenBuffers(1, &m_idGL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idGL);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_idGL);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_idGL);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
