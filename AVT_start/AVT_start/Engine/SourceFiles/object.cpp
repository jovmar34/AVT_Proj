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

void Object::initObject()
{
	size_t size = 2 * positions.size() * 4 * sizeof(GLfloat);
	std::cout << size << std::endl;

	GLfloat* Vertices = (GLfloat*) alloca(size);
	GLfloat* curr = Vertices;

	for (int i = 0; i < positions.size(); i++) {
		curr[0] = positions[i].x;
		curr[1] = positions[i].y;
		curr[2] = positions[i].z;
		curr[3] = positions[i].w;
		curr[4] = vertexColors[i].x;
		curr[5] = vertexColors[i].y;
		curr[6] = vertexColors[i].z;
		curr[7] = vertexColors[i].w;
		curr += 8;
	}

	for (int i = 0; i < (2 * positions.size() * 4); i++) {
		std::cout << Vertices[i] << " ";
	}

	std::cout << std::endl;

	GLushort Indices[] =
	{	
		0,1,2,3,2,1,2,3,5,5,4,2
	};

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(2, VboId);

		glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, size, Vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 2 * 4 * sizeof(GLfloat), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 2 * 4 * sizeof(GLfloat), (GLvoid*) (4 * sizeof(GLfloat)));
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

void Object::drawObject(GLuint ProgramId)
{
	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	GLuint UniformId = glGetUniformLocation(ProgramId, "Matrix");

	glUniformMatrix4fv(UniformId, 1, GL_FALSE, transformations.toOpenGl());
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, (GLvoid*) 0);

	glUseProgram(0);
	glBindVertexArray(0);
}
