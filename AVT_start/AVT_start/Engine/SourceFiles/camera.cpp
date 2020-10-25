#include "..\HeaderFiles\camera.h"

const GLuint UBO_BP = 0;

void Camera::setupCamera()
{
	GLuint i;
	glGenBuffers(1, &i);

	glBindBuffer(GL_UNIFORM_BUFFER, i);
	{
		glBufferData(GL_UNIFORM_BUFFER, 2 * 16 * sizeof(GLfloat), 0, GL_STREAM_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, i);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	VboId = i;
}

void Camera::updateView() {
	Vector3D v, u, s;
	v = center - eye;
	v.normalize();

	s = v % up;
	s.normalize();

	u = s % v;

	view = Matrix4(
		s.x, s.y, s.z, -(s * eye),
		u.x, u.y, u.z, -(u * eye),
		-v.x, -v.y, -v.z, v * eye,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	change = true;
}

void Camera::parallelProjection(double l, double r, double b, double t, double n, double f)
{
	projection = Matrix4(
		2/(r-l), 0, 0, (l+r)/(l-r),
		0, 2/(t-b), 0, (b+t)/(b-t),
		0, 0, 2/(n-f), (n+f)/(n-f),
		0, 0, 0, 1
	);

	change = true;
}

void Camera::drawCamera(GLuint ProgramId)
{
	if (!change) return;

	GLuint UboId = glGetUniformBlockIndex(ProgramId, "SharedMatrices");

	glBindBuffer(GL_UNIFORM_BUFFER, VboId);
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, 16 * sizeof(GLfloat), view.toOpenGl());
		glBufferSubData(GL_UNIFORM_BUFFER, 16 * sizeof(GLfloat), 16 * sizeof(GLfloat), projection.toOpenGl());
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	change = false;
}
