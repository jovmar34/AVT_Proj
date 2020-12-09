#pragma once

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray {
private:
	GLuint my_ID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout);
	void addAttribute(unsigned int location, VertexBufferElement& element);

	void bind();
	void unbind();
};