#include "..\HeaderFiles\Mesh.h"

Mesh::Mesh(const std::string& n, std::string path)
	: posbuf(nullptr), uvbuf(nullptr), normbuf(nullptr), indbuf(nullptr), va(nullptr)
{
	ObjLoader c_loader;
	vertices = c_loader.readFromFile(path);
}

Mesh::~Mesh()
{
	va->bind();
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

	va->unbind();
}

void Mesh::init()
{
	va = new VertexArray();
	vector<GLfloat> pos;

	for (Vector3D vec : vertices.positions) {
		GLfloat* newpos = vec.toOpenGL();
		pos.insert(std::end(pos), newpos, newpos + 3);
	}

	posbuf = new VertexBuffer(&pos[0], (unsigned int) pos.size() * sizeof(GLfloat));

	VertexBufferElement poselement = VertexBufferLayout::getElement<float>(3);
	va->addAttribute(POSITIONS, poselement);

	posbuf->unbind();
	/**/
	if (vertices.hasTextures) {
		vector<GLfloat> uvs;
		for (Vector2D uvcoord : vertices.textureCoords) {
			GLfloat* newuv = uvcoord.toOpenGL();
			uvs.insert(std::end(uvs), newuv, newuv + 2);
		}

		uvbuf = new VertexBuffer(&uvs[0], (unsigned int) uvs.size() * sizeof(GLfloat));
		VertexBufferElement uvelement = VertexBufferLayout::getElement<float>(2);
		va->addAttribute(UVCOORDS, uvelement);

		uvbuf->unbind();
	}

	if (vertices.hasNormals) {
		vector<GLfloat> norms;
		for (Vector3D norm : vertices.normals) {
			GLfloat* newnorm = norm.toOpenGL();
			norms.insert(std::end(norms), newnorm, newnorm + 3);
		}

		normbuf = new VertexBuffer(&norms[0], (unsigned int) norms.size() * sizeof(GLfloat));
		VertexBufferElement normelement = VertexBufferLayout::getElement<float>(3);
		va->addAttribute(NORMALS, normelement);

		normbuf->unbind();
	}
	/**/

	indbuf = new IndexBuffer(vertices.indices.data(), (unsigned int) vertices.indices.size());
	indbuf->unbind();
	
	va->unbind();
}

void Mesh::draw()
{
	va->bind();
	glDrawElements(GL_TRIANGLES, (GLsizei) vertices.indices.size(), GL_UNSIGNED_INT, (GLvoid*) 0);
	va->unbind();
}
