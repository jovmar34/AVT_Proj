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
	vector<GLfloat> pos;

	for (Vector3D vec : vertices.positions) {
		GLfloat* newpos = vec.toOpenGL();
		pos.insert(std::end(pos), newpos, newpos + 3);
	}

	posbuf = new VertexBuffer(&pos[0], (unsigned int) pos.size() * sizeof(GLfloat));
	glEnableVertexAttribArray(POSITIONS);
	glVertexAttribPointer(POSITIONS, 3, GL_FLOAT, GL_FALSE, Vector3D::byteSize(), 0);

	if (vertices.hasTextures) {
		vector<GLfloat> uvs;
		for (Vector2D uvcoord : vertices.textureCoords) {
			GLfloat* newuv = uvcoord.toOpenGL();
			uvs.insert(std::end(uvs), newuv, newuv + 3);
		}

		uvbuf = new VertexBuffer(&uvs[0], (unsigned int) uvs.size() * sizeof(GLfloat));
		glEnableVertexAttribArray(UVCOORDS);
		glVertexAttribPointer(UVCOORDS, 2, GL_FLOAT, GL_FALSE, Vector2D::byteSize(), 0);
	}

	if (vertices.hasNormals) {
		vector<GLfloat> norms;
		for (Vector3D norm : vertices.normals) {
			GLfloat* newnorm = norm.toOpenGL();
			norms.insert(std::end(norms), newnorm, newnorm + 3);
		}

		normbuf = new VertexBuffer(&norms[0], (unsigned int) norms.size() * sizeof(GLfloat));
		glEnableVertexAttribArray(NORMALS);
		glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, Vector3D::byteSize(), 0);
	}

	indbuf = new IndexBuffer(vertices.indices.data(), (unsigned int) vertices.indices.size());
	indbuf->unbind();
	normbuf->unbind();
}

void Mesh::draw()
{
	glDrawElements(GL_TRIANGLES, (GLsizei) vertices.indices.size(), GL_UNSIGNED_INT, (GLvoid*) 0);
}
