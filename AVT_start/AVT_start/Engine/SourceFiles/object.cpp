#include "..\HeaderFiles\object.h"

Object::Object(Mesh _mesh, float zbuf, int fake) : mesh(_mesh), m_zbuf(zbuf) {
	m_fake = (fake == 1) ? true : false;
	transform = MxFactory::identity4();
	initTransform = transform;
}

Object::~Object()
{
	glBindVertexArray(VaoId);
	glDeleteVertexArrays(1, &VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::rotateAroundAxis(Vector3D axis, double angle)
{
	transform = MxFactory::rotation4(axis, angle) * transform;
}

void Object::translate(Vector3D translateVec)
{
	transform = MxFactory::translation4(translateVec) * transform;
}

void Object::scale(Vector3D scaleVec)
{
	transform = MxFactory::scaling4(scaleVec) * transform;
}

void Object::initObject(GLuint ProgId)
{
	ProgramId = ProgId;
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	mesh.init();
	
	glBindVertexArray(0);
}

void Object::drawObject(Matrix4& transf)
{
	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	GLuint MatrixId = glGetUniformLocation(ProgramId, "ModelMatrix");
	GLuint zbufid = glGetUniformLocation(ProgramId, "zbuf");
	GLuint fakeid = glGetUniformLocation(ProgramId, "fake");


	glUniformMatrix4fv(MatrixId, 1, GL_FALSE, transf.toOpenGl());
	glUniform1f(zbufid, m_zbuf);
	glUniform1i(fakeid, (m_fake) ? 1 : 0);

	mesh.draw();

	glUseProgram(0);
	glBindVertexArray(0);
}

// save initial transform
void Object::saveInitTransform() {

	initTransform = transform;
}

void Object::resetTransform() {

	transform = initTransform;
}

void Object::setTransform(Matrix4 _transform) {

	transform = _transform;
}

Vector3D Object::getPosition()
{
	return Vector3D(transform(3, 0), transform(3, 1), transform(3, 2));
}

Vector3D Object::getBasePosition()
{
	return Vector3D(initTransform(0, 3), initTransform(1, 3), initTransform(2, 3));
}
