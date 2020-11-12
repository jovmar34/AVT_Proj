#include "..\HeaderFiles\Mesh.h"

Mesh::Mesh(LoaderInfo _vertices) 
	: vertices(_vertices), posbuf(NULL), uvbuf(NULL), normbuf(NULL), indbuf(NULL)
{
}

Mesh::~Mesh()
{
	if (!posbuf) return;

	glDisableVertexAttribArray(POSITIONS);
	delete posbuf;

	if (vertices.hasTextures) {
		glDisableVertexAttribArray(UVCOORDS);
		delete uvbuf;
	}
	if (vertices.hasNormals) {
		glDisableVertexAttribArray(NORMALS);
		delete normbuf;
	}

	delete indbuf;
}

void Mesh::init()
{
	posbuf = new VertexBuffer(&vertices.positions[0], vertices.positions.size() * Vector3D::byteSize());
	glEnableVertexAttribArray(POSITIONS);
	glVertexAttribPointer(POSITIONS, 3, GL_FLOAT, GL_FALSE, Vector3D::byteSize(), 0);

	if (vertices.hasTextures) {
		uvbuf = new VertexBuffer(&vertices.textureCoords[0], vertices.textureCoords.size() * Vector2D::byteSize());
		glEnableVertexAttribArray(UVCOORDS);
		glVertexAttribPointer(UVCOORDS, 2, GL_FLOAT, GL_FALSE, Vector2D::byteSize(), 0);
	}

	if (vertices.hasNormals) {
		normbuf = new VertexBuffer(&vertices.normals[0], vertices.normals.size() * Vector3D::byteSize());
		glEnableVertexAttribArray(NORMALS);
		glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, Vector3D::byteSize(), 0);
	}

	indbuf = new IndexBuffer(&vertices.indices[0], vertices.indices.size());
	indbuf->unbind();
	normbuf->unbind();
}

void Mesh::draw()
{
	glDrawElements(GL_TRIANGLES, (GLsizei) vertices.indices.size(), GL_UNSIGNED_SHORT, (GLvoid*) 0);
}
