///////////////////////////////////////////////////////////////////////////////
//
// Assignment 1 consists in the following:
//
// - Update your graphics drivers to their latest versions.
// - Download the appropriate libraries GLEW and GLFW for your system.
// - Create a project to compile, link and run the code provided in this 
//   section in your favourite programming environment 
//   (course will use VS2019 Community Edition).
// - Verify what OpenGL contexts your computer can support, a minimum of 
//   OpenGL 3.3 support is required for this course.
//
// Further suggestions to verify your understanding of the concepts explored:
// - Create an abstract class for an OpenGL application.
// - Change the program so display is called at 30 FPS.
//
// (c)2013-20 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../HeaderFiles/vector.h"
#include "../HeaderFiles/matrix.h"
#include "../HeaderFiles/mxfactory.h"

////////////////////////////////////////////////// ERROR CALLBACK (OpenGL 4.3+)

static const std::string errorSource(GLenum source)
{
	switch (source) {
	case GL_DEBUG_SOURCE_API:				return "API";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		return "window system";
	case GL_DEBUG_SOURCE_SHADER_COMPILER:	return "shader compiler";
	case GL_DEBUG_SOURCE_THIRD_PARTY:		return "third party";
	case GL_DEBUG_SOURCE_APPLICATION:		return "application";
	case GL_DEBUG_SOURCE_OTHER:				return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static const std::string errorType(GLenum type)
{
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:				return "error";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:	return "deprecated behavior";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:	return "undefined behavior";
	case GL_DEBUG_TYPE_PORTABILITY:			return "portability issue";
	case GL_DEBUG_TYPE_PERFORMANCE:			return "performance issue";
	case GL_DEBUG_TYPE_MARKER:				return "stream annotation";
	case GL_DEBUG_TYPE_PUSH_GROUP:			return "push group";
	case GL_DEBUG_TYPE_POP_GROUP:			return "pop group";
	case GL_DEBUG_TYPE_OTHER_ARB:			return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static const std::string errorSeverity(GLenum severity)
{
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:			return "high";
	case GL_DEBUG_SEVERITY_MEDIUM:			return "medium";
	case GL_DEBUG_SEVERITY_LOW:				return "low";
	case GL_DEBUG_SEVERITY_NOTIFICATION:	return "notification";
	default:								exit(EXIT_FAILURE);
	}
}

static void error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	std::cerr << "GL ERROR:" << std::endl;
	std::cerr << "  source:     " << errorSource(source) << std::endl;
	std::cerr << "  type:       " << errorType(type) << std::endl;
	std::cerr << "  severity:   " << errorSeverity(severity) << std::endl;
	std::cerr << "  debug call: " << std::endl << message << std::endl << std::endl;
}

void setupErrorCallback()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(error, 0);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
	// params: source, type, severity, count, ids, enabled
}

///////////////////////////////////////////////// ERROR HANDLING (All versions)

static const std::string errorString(GLenum error)
{
	switch(error) {
	case GL_NO_ERROR:
		return "No error has been recorded.";
	case GL_INVALID_ENUM:
		return "An unacceptable value is specified for an enumerated argument.";
	case GL_INVALID_VALUE:
		return "A numeric argument is out of range.";
	case GL_INVALID_OPERATION:
		return "The specified operation is not allowed in the current state.";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "The framebuffer object is not complete.";
	case GL_OUT_OF_MEMORY:
		return "There is not enough memory left to execute the command.";
	case GL_STACK_UNDERFLOW:
		return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
	case GL_STACK_OVERFLOW:
		return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
	default: exit(EXIT_FAILURE);
	}
}

static bool isOpenGLError() 
{
	bool isError = false;
	GLenum errCode;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		std::cerr << "OpenGL ERROR [" << errorString(errCode) << "]." << std::endl;
	}
	return isError;
}

static void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

///////////////////////////////////////////////////////////////////// CALLBACKS

void window_close_callback(GLFWwindow* win)
{
	std::cout << "closing..." << std::endl;
}

void window_size_callback(GLFWwindow* win, int winx, int winy)
{
	std::cout << "size: " << winx << " " << winy << std::endl;
	glViewport(0, 0, winx, winy);
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(win, GLFW_TRUE);
		window_close_callback(win);
	}
}

void mouse_callback(GLFWwindow* win, double xpos, double ypos)
{
	std::cout << "mouse: " << xpos << " " << ypos << std::endl;
}

void mouse_button_callback(GLFWwindow* win, int button, int action, int mods)
{
	std::cout << "button: " << button << " " << action << " " << mods << std::endl;
}

void scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
{
	std::cout << "scroll: " << xoffset << " " << yoffset << std::endl;
}

void joystick_callback(int jid, int event)
{
	std::cout << "joystick: " << jid << " " << event << std::endl;
}

///////////////////////////////////////////////////////////////////////// SETUP

void glfw_error_callback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

GLFWwindow* setupWindow(int winx, int winy, const char* title, 
	int is_fullscreen, int is_vsync)
{
	GLFWmonitor* monitor = is_fullscreen ? glfwGetPrimaryMonitor() : 0;
	GLFWwindow* win = glfwCreateWindow(winx, winy, title, monitor, 0);
	if (!win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(is_vsync);
	return win;
}

void setupCallbacks(GLFWwindow* win)
{
	glfwSetKeyCallback(win, key_callback);
	glfwSetCursorPosCallback(win, mouse_callback);
	glfwSetMouseButtonCallback(win, mouse_button_callback);
	glfwSetScrollCallback(win, scroll_callback);
	glfwSetJoystickCallback(joystick_callback);

	glfwSetWindowCloseCallback(win, window_close_callback);
	glfwSetWindowSizeCallback(win, window_size_callback);
}

GLFWwindow* setupGLFW(int gl_major, int gl_minor, 
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow* win = setupWindow(winx, winy, title, is_fullscreen, is_vsync);
	setupCallbacks(win);

#if _DEBUG
	std::cout << "GLFW " << glfwGetVersionString() << std::endl;
#endif
	return win;
}

void setupGLEW()
{
	glewExperimental = GL_TRUE;
	// Allow extension entry points to be loaded even if the extension isn't 
	// present in the driver's extensions string.
	GLenum result = glewInit();
	if (result != GLEW_OK) 
	{
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
	// You might get GL_INVALID_ENUM when loading GLEW.
}

void checkOpenGLInfo()
{
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void setupOpenGL(int winx, int winy)
{
#if _DEBUG
	checkOpenGLInfo();
#endif
	glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glViewport(0, 0, winx, winy);
}

GLFWwindow* setup(int major, int minor, 
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	GLFWwindow* win = 
		setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
	setupGLEW();
	setupOpenGL(winx, winy);
	setupErrorCallback();
	return win;
}

////////////////////////////////////////////////////////////////////////// RUN

void updateFPS(GLFWwindow* win, double elapsed_sec)
{	
	static unsigned int acc_frames = 0;
	static double acc_time = 0.0;
	const double UPDATE_TIME = 1.0;

	++acc_frames;
	acc_time += elapsed_sec;
	if (acc_time > UPDATE_TIME)
	{
		std::ostringstream oss;
		double fps = acc_frames / acc_time;
		oss << std::fixed << std::setw(5) << std::setprecision(1) << fps << " FPS";
		glfwSetWindowTitle(win, oss.str().c_str());

		acc_frames = 0;
		acc_time = 0.0;
	}
}

void display_callback(GLFWwindow* win, double elapsed_sec)
{
	updateFPS(win, elapsed_sec);
}

void run(GLFWwindow* win)
{
	double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(win))
	{
		double time = glfwGetTime();
		double elapsed_time = time - last_time;
		last_time = time;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display_callback(win, elapsed_time);
		glfwSwapBuffers(win);
		glfwPollEvents();

		//checkOpenGLError("ERROR: MAIN/RUN");
	}
	glfwDestroyWindow(win);
	glfwTerminate();
}

// ====================== Rodrigues Rotation ===============================

const Vector3D RodrRot(Vector3D& v, Vector3D& k, double angle) {
	double r_angle = angle * M_PI / 180; // convert the angle in degrees to radians
	k.normalize();

	Vector3D v1 = v * cos(r_angle);
	Vector3D v2 = (k % v) * sin(r_angle);
	Vector3D v3 = k * (k * v) * (1 - cos(r_angle));

	return (v1 + v2 + v3);
}

// =========================================================================

void transformationsTest() {
	MxFactory mx;

	// Scaling test
	Matrix4 sc = mx.scaling4(1, 2, 3), invsc = mx.invscaling4(1, 2, 3);
	Vector4D p1(1, 2, 3, 1);

	std::cout << "The point we're scaling is " << p1 << endl;
	std::cout << "The matrix used for scaling by (1,2,3) is:\n" << sc << endl;
	std::cout << "Its inverse is:\n" << invsc << endl;

	p1 = sc * p1;
	std::cout << "P' = Sc * P = " << p1 << std::endl;

	p1 = invsc * p1;
	std::cout << "P = Sc^-1 * P'  = " << p1 << std::endl;

	// Translation test
	Matrix4 tx = mx.translation4(1, 2, 3), invtx = mx.invtranslation4(1, 2, 3);
	Vector4D p2(1, 1, 1, 1);

	std::cout << "The point we're tranlating is " << p2 << endl;
	std::cout << "The matrix used for translation by (1,2,3) is:\n" << tx << endl;
	std::cout << "Its inverse is:\n" << invtx << endl;

	p2 = tx * p2;
	std::cout << "P' = Tx * P = " << p2 << std::endl;

	p2 = invtx * p2;
	std::cout << "P = Tx^-1 * P'  = " << p2 << std::endl;

	// Rotation test
	Matrix4 rot = mx.rotation4(0, 1, 0, 90.0f), invrot = mx.invrotation4(0, 1, 0, 90.0f);
	Vector4D p3(1, 0, 0, 1);

	std::cout << "The point we're rotating is " << p3 << std::endl;
	std::cout << "The matrix used for rotating around (0,1,0) by 90 is:\n" << rot << std::endl;
	std::cout << "Its inverse is:\n" << invrot << std::endl;

	p3 = rot * p3;
	std::cout << "P' = Rot * P = " << p3 << std::endl;

	p3 = invrot * p3;
	std::cout << "P = Rot^-1 * P'  = " << p3 << std::endl << std::endl;

}

void errorsTest() {
	Vector3D v1(1, 1, 1), v2(1.1, 0.9, 1), v3(1.000001, 0.99999, 1);

	std::cout << "v1, v2, v3 = " << v1 << ", " << v2 << ", " << v3 << std::endl;
	std::cout << "v1 == v2? " << (v1 == v2) << std::endl;
	std::cout << "v1 == v3? " << (v1 == v3) << std::endl;
}

// ========================= Assignment 2 ========================================
void Assignment2() {
	srand((unsigned int)time(NULL));

	// Part 1: 10 random pairs, prove equalities
	float r;
	array<double, 9> args;
	int mxs = 0;
	Matrix3 lcombo, rcombo;

	std::cout << "========== Part 1 ===========" << std::endl;
	while (mxs < 10) {
		for (int j = 0; j < 9; j++) {
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r = r * 20 - 10;
			args[j] = r;
		}

		Matrix3 A(args), invA, trA;

		for (int j = 0; j < 9; j++) {
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r = r * 20 - 10;
			args[j] = r;
		}

		Matrix3 B(args), invB, trB;

		try {
			invA = A.inverse();
			invB = B.inverse();
		}
		catch (char const* e) {
			std::cout << "at least one of the matrix wasn't invertible" << std::endl;
			continue;
		}

		mxs++;

		trA = A.transpose();
		trB = B.transpose();

		lcombo = (A * B).transpose();
		rcombo = trB * trA;

		std::cout << "(A" << mxs << "*B" << mxs << ")^T = B" << mxs << "^T*A" << mxs << "^T ? " << (lcombo == rcombo) << std::endl;

		lcombo = (A * B).inverse();
		rcombo = invB * invA;

		std::cout << "(A" << mxs << "*B" << mxs << ")^-1 = B" << mxs << "^-1*A" << mxs << "^-1 ? " << (lcombo == rcombo) << std::endl << std::endl;

	}

	// Part 2
	std::cout << "========== Part 2 ===========" << std::endl;

	Matrix3 M(
		2,3,1,
		3,4,1,
		3,7,2), trM, invM;

	Matrix3 N(
		1, 0, 0,
		0, 0, -2,
		-5, 0, 9), trN, invN;

	double detM, detN;

	trM = M.transpose();
	std::cout << "M^T\n" << trM << std::endl;

	trN = N.transpose();
	std::cout << "N^T\n" << trN << std::endl;

	detM = M.determinant();
	detN = N.determinant();

	std::cout << "|M| = " << detM << "\n|N| = " << detN << std::endl << std::endl;

	try {
		invM = M.inverse();
		std::cout << "M^-1:\n" << invM << std::endl;
	}
	catch (char const* e) {
		std::cout << e << "(matrix M)" << std::endl;
	}

	try {
		invN = N.inverse();
		std::cout << "N^-1:\n" << invN << std::endl;
	}
	catch (char const* e) {
		std::cout << e << "(matrix N)" << std::endl;
	}

	GLfloat *arrM = M.toOpenGl(), *arrN = N.toOpenGl();

	std::cout << "M in OpenGL: [ ";
	for (int i = 0; i < 9; i++) {
		std::cout << arrM[i] << " ";
	}
	std::cout << "]\n";

	std::cout << "N in OpenGL: [ ";
	for (int i = 0; i < 9; i++) {
		std::cout << arrN[i] << " ";
	}
	std::cout << "]\n";

	// Part 3: transformations
	std::cout << "========== Part 3 ===========" << std::endl;

	MxFactory mx;
	Matrix4 tr = mx.translation4(4,5,6);
	Matrix4 sc = mx.scaling4(4, 5, 6);
	Matrix4 rot = mx.rotation4(0, 0, 1, 34);

	std::cout << "Matrix for (4,5,6) tranlation:\n" << tr << std::endl;
	std::cout << "Matrix for (4,5,6) scale:\n" << sc << std::endl;
	std::cout << "Matrix for 34 degree rotation around z axis:\n" << rot << std::endl;

}

////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[])
{

	std::cout << std::boolalpha;

	Assignment2();

	exit(EXIT_SUCCESS); 
}

/////////////////////////////////////////////////////////////////////////// END