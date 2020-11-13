#include "..\HeaderFiles\object.h"

Object::~Object()
{
	
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

void Object::initObject(GLuint ProgramId)
{
	
	UniformId = glGetUniformLocation(ProgramId, "ModelMatrix");

	mesh.init();
	
	glBindVertexArray(0);
}

void Object::drawObject()
{
	glUniformMatrix4fv(UniformId, 1, GL_FALSE, transform.toOpenGl());

	mesh.draw();
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