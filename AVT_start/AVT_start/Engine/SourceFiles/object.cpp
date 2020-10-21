#include "..\HeaderFiles\object.h"

void Object::rotateAroundAxis(double ax, double ay, double az, double angle)
{
	transformations = MxFactory::rotation4(ax, ay, az, angle) * transformations;
}

void Object::translate(double ax, double ay, double az)
{
	transformations = MxFactory::translation4(ax, ay, az) * transformations;
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

void Strip::drawObject(GLint UniformId, GLint ProgramId) {
	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	glUniformMatrix4fv(UniformId, 1, GL_FALSE, transformations.toOpenGl());
	glDrawElements(GL_TRIANGLE_STRIP, (GLsizei) positions.size(), GL_UNSIGNED_SHORT, (GLvoid*)0);

	glBindVertexArray(0);
	glUseProgram(0);

}

void Strip::initObject()
{
	GLfloat*** Vertices = new GLfloat** [positions.size()];
	GLushort* Indices = new GLushort[positions.size()];

	for (unsigned short i = 0; i < positions.size(); i++) {
		Vertices[i] = new GLfloat* [2];
		Vertices[i][0] = positions[i].toOpenGL();
		Vertices[i][1] = vertexColors[i].toOpenGL();
		Indices[i] = i;
	}

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(2, VboId);

		glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), Vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), (GLvoid*) sizeof(Vertices[0][0]));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
