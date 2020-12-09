#include "..\HeaderFiles\camera.h"

Camera::Camera(Vector3D _eye, Vector3D _center, Vector3D _up) : eye(_eye), center(_center), up(_up)
{
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
}

void Camera::parallelProjection(double l, double r, double b, double t, double n, double f)
{
	projection = Matrix4(
		2/(r-l), 0, 0, (l+r)/(l-r),
		0, 2/(t-b), 0, (b+t)/(b-t),
		0, 0, 2/(n-f), (n+f)/(n-f),
		0, 0, 0, 1
	);

	projType = CameraProj::Parallel;
	change = true;
}

void Camera::perspectiveProjection(double fovy, double aspect, double near, double far)
{
	double theta = fovy * M_PI / 180;
	double d = 1/tan(theta/2);
	projection = Matrix4(
		d / aspect, 0, 0, 0,
		0, d, 0, 0,
		0, 0, (near+far)/(near-far), 2*near*far/(near-far), 
		0, 0, -1, 0
	);

	projType = CameraProj::Perspective;
	change = true;
}

void Camera::move(Vector3D dir, double speed)
{
	if (state == Working::Off) return;

	Vector3D transform = dir.x * s + -dir.z * v;
	eye += transform * speed;
	center += transform * speed;

	updateView();
}

void Camera::look(double angle_h, double angle_v)
{
	if (state == Working::Off) return;

	Vector3D dir = center - eye;
	double len = dir.length();

	double sin1 = sin(angle_h), cos1 = cos(angle_h);
	double sin2 = sin(angle_v), cos2 = cos(angle_v);

	Vector3D rot = len * cos1 * cos2 * v +
		-len * sin2 * u +
		len * sin1 * cos2 * s;

	center = eye + rot;

	updateView();
}


void Camera::updateView()
{
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

void Camera::toggle()
{
	state = (state == Working::On) ? Working::Off : Working::On;
}


void Camera::drawCamera()
{
	if (projType == CameraProj::None) 
		throw "The camera projections has not been defined!";

	//dont re-render if there's no change
	if (!change) return;

	GLfloat* viewMatrix = view.toOpenGl(),
		*projectionMatrix = projection.toOpenGl();

	glBindBuffer(GL_UNIFORM_BUFFER, VboId);
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, 16 * sizeof(GLfloat), viewMatrix);
		glBufferSubData(GL_UNIFORM_BUFFER, 16 * sizeof(GLfloat), 16 * sizeof(GLfloat), projectionMatrix);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	change = false;
}
