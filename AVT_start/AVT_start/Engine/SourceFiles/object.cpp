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
	GLsizeiptr vsize = (GLsizeiptr) 2 * positions.size() * 4 * sizeof(GLfloat);

	GLfloat* Vertices = (GLfloat*) calloc(2 * positions.size() * 4, sizeof(GLfloat));

	if (Vertices == NULL) return;

	for (int i = 0; i < positions.size(); i++) {
		Vertices[8 * i] = (GLfloat) positions[i].x;
		Vertices[8 * i + 1] = (GLfloat) positions[i].y;
		Vertices[8 * i + 2] = (GLfloat) positions[i].z;
		Vertices[8 * i + 3] = (GLfloat) positions[i].w;
		Vertices[8 * i + 4] = (GLfloat) vertexColors[i].x;
		Vertices[8 * i + 5] = (GLfloat) vertexColors[i].y;
		Vertices[8 * i + 6] = (GLfloat) vertexColors[i].z;
		Vertices[8 * i + 7] = (GLfloat) vertexColors[i].w;
	}

	GLint isize = (GLint) indices.size() * sizeof(GLuint);
	GLushort* Indices = (GLushort*) calloc(indices.size(), sizeof(GLuint));

	if (Indices == NULL) {
		free(Vertices);
		return;
	}

	for (int i = 0; i < indices.size(); i++) {
		Indices[i] = indices[i];
	}

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(2, VboId);

		glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, vsize, Vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(POSITIONS);
			glVertexAttribPointer(POSITIONS, 4, GL_FLOAT, GL_FALSE, 2 * 4 * sizeof(GLfloat), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, 2 * 4 * sizeof(GLfloat), (GLvoid*) (4 * sizeof(GLfloat)));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, Indices, GL_STATIC_DRAW);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	free(Vertices);
	free(Indices);
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