#pragma once

#include <vector>
#include "vector.h" 

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);
		default:
			return 0;
		}
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;

	template<typename T>
	struct falsey : std::false_type
	{ };

public:
	VertexBufferLayout() : stride(0) {}

	template<typename T>
	static VertexBufferElement getElement(unsigned int count) {
		static_assert(falsey<T>::value); // for non-handled types
	}

	template<>
	static VertexBufferElement getElement<float>(unsigned int count) {
		return { GL_FLOAT, count, GL_FALSE };
	}

	template<typename T>
	void push(unsigned int count) {
		static_assert(falsey<T>::value); // for non-handled types
	}

	template<>
	void push<float>(unsigned int count) {
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += sizeof(GLfloat) * count;
	}

	template<>
	void push<unsigned int>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += sizeof(GLuint) * count;
	}

	template<>
	void push<unsigned char>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += sizeof(GLubyte) * count;
	}

	template<>
	void push<Vector3D>(unsigned int count) {
		push<float>(3);
	}

	template<>
	void push<Vector2D>(unsigned int count) {
		push<float>(2);
	}

	std::vector<VertexBufferElement>& getElements() { return elements; }
	unsigned int getStride() { return stride; }

};