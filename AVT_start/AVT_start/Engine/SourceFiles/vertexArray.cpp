#include "..\HeaderFiles\vertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout)
{
	auto& elements = layout.getElements();

	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset);
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::addAttribute(unsigned int location, VertexBufferElement& element)
{
	unsigned int stride = element.count * VertexBufferElement::getSizeOfType(element.type);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, element.count, element.type, element.normalized, stride, (const void*) 0);
}

void VertexArray::bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}
