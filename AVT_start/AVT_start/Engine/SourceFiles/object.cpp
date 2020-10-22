#include "..\HeaderFiles\object.h"

void Object::rotateAroundAxis(double ax, double ay, double az, double angle)
{
	transformations = MxFactory::rotation4(ax, ay, az, angle) * transformations;
}

void Object::translate(double ax, double ay, double az)
{
	transformations = MxFactory::translation4(ax, ay, az) * transformations;
	std::cout << transformations << std::endl;
}

void Object::scale(double ax, double ay, double az)
{
	transformations = MxFactory::scaling4(ax, ay, az) * transformations;
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

	GLfloat* Vertices = (GLfloat*) malloc(vsize);
	GLfloat* curr = Vertices;

	for (int i = 0; i < positions.size(); i++) {
		curr[0] = (GLfloat) positions[i].x;
		curr[1] = (GLfloat) positions[i].y;
		curr[2] = (GLfloat) positions[i].z;
		curr[3] = (GLfloat) positions[i].w;
		curr[4] = (GLfloat) vertexColors[i].x;
		curr[5] = (GLfloat) vertexColors[i].y;
		curr[6] = (GLfloat) vertexColors[i].z;
		curr[7] = (GLfloat) vertexColors[i].w;
		curr += 8;
	}

	GLint isize = (GLint) indices.size() * sizeof(GLuint);
	GLushort* Indices = (GLushort*) malloc(isize);
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
}

void Object::drawObject(GLuint ProgramId)
{
	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	GLuint UniformId = glGetUniformLocation(ProgramId, "Matrix");

	glUniformMatrix4fv(UniformId, 1, GL_FALSE, transformations.toOpenGl());
	glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_SHORT, (GLvoid*) 0);
	glUseProgram(0);
	glBindVertexArray(0);
}
