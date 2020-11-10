#include "..\HeaderFiles\object.h"

void Object::rotateAroundAxis(Vector3D axis, double angle)
{
	transformations = MxFactory::rotation4(axis, angle) * transformations;
}

void Object::translate(Vector3D translateVec)
{
	transformations = MxFactory::translation4(translateVec) * transformations;
}

void Object::scale(Vector3D scaleVec)
{
	transformations = MxFactory::scaling4(scaleVec) * transformations;
}

void Object::addVertex(double posx, double posy, double posz, double r, double g, double b, double a)
{
	positions.push_back(Vector4D(posx, posy, posz, 1.0f));
	vertexColors.push_back(Vector4D(r, g, b, a));
}

void Object::addTriangle(GLushort v1, GLushort v2, GLushort v3)
{
	indices.push_back(v1);
	indices.push_back(v2);
	indices.push_back(v3);
}

void Object::deleteObject()
{
	glBindVertexArray(VaoId);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteBuffers(2, VboId);
	glDeleteVertexArrays(1, &VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::initObject()
{
	vector<GLfloat> pos;

	for (Vector4D vec : positions) {
		GLfloat* newpos = vec.toOpenGL();
		pos.insert(std::end(pos), newpos, newpos + 4);
	}

	vector<GLfloat> cols;

	for (Vector4D col : vertexColors) {
		GLfloat* newcol = col.toOpenGL();
		cols.insert(std::end(cols), newcol, newcol + 4);
	}

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		posbuf = new VertexBuffer(&pos[0], pos.size() * sizeof(GLfloat));
		glEnableVertexAttribArray(POSITIONS);
		glVertexAttribPointer(POSITIONS, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);

		colbuf = new VertexBuffer(&cols[0], cols.size() * sizeof(GLfloat));
		glEnableVertexAttribArray(COLORS);
		glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		colbuf->unbind();

		indbuf = new IndexBuffer(&indices[0], indices.size());
		indbuf->unbind();
	}

	glBindVertexArray(0);
	positions.clear();
	vertexColors.clear();
}

void Object::drawObject(GLuint ProgramId)
{
	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	GLuint UniformId = glGetUniformLocation(ProgramId, "ModelMatrix");

	glUniformMatrix4fv(UniformId, 1, GL_FALSE, transformations.toOpenGl());
	glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_SHORT, (GLvoid*) 0);
	glUseProgram(0);
	glBindVertexArray(0);
}

// save initial transform
void Object::saveInitTransform() {

	initTransformations = transformations;
}

void Object::resetTransform() {

	transformations = initTransformations;
}

void Object::setTransform(Matrix4 transform) {

	transformations = transform;
}