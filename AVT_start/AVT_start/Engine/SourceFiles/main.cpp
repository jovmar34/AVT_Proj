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
#include <fstream>
#include <iomanip>
#include <cmath>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "FreeImage.h"
#include "../HeaderFiles/engine.h"
#include "../HeaderFiles/manager.h"
#include "../HeaderFiles/myApp.h"

/////////////////////////////////////////////////////////////////////// SHADERs
bool save_img = false;

SceneGraph graph;
<<<<<<< HEAD
myApp app;
=======

void populateScene() {
	
	// Camera init
	cam = Camera(Vector3D(4, 4, 4), Vector3D(0, 0, 0), Vector3D(0, 1, 0));
	cam.perspectiveProjection(60, 4.0f / 3.0f, 1, 200);

	graph.setCamera(&cam);

	Manager* h = Manager::getInstance();

	// Meshes
	Mesh	*plane_mesh = h->addMesh("plane_mesh", new Mesh("res/meshes/plane.obj")),
			*cube_mesh = h->addMesh("cube_mesh", new Mesh("res/meshes/bunny_smooth.obj")),
			*cylinder_mesh = h->addMesh("cylinder_mesh", new Mesh("res/meshes/cylinder.obj")),
			*torus_mesh = h->addMesh("torus_mesh", new Mesh("res/meshes/torus.obj"));

	// Textures
	Texture *test_texture = h->addTexture("test_texture", new Texture("res/textures/test_texture.png"));
	Texture* toon_ramp_texture = h->addTexture("toon_ramp_texture", new Texture("res/textures/toon_ramp_texture.png"));

	// Shaders
	Shader	*texture_shader = h->addShader("texture_shader", new Shader("res/shaders/texture_vs.glsl", "res/shaders/texture_fs.glsl")),
			*phong_shader = h->addShader("phong_shader", new Shader("res/shaders/phong_vs.glsl", "res/shaders/phong_fs.glsl")),
			*blinn_phong_shader = h->addShader("blinn_phong_shader", new Shader("res/shaders/blinn_phong_vs.glsl", "res/shaders/blinn_phong_fs.glsl")),
			*gouraud_shader = h->addShader("gouraud_shader", new Shader("res/shaders/gouraud_vs.glsl", "res/shaders/gouraud_fs.glsl")),
			*toon_shader = h->addShader("toon_shader", new Shader("res/shaders/toon_vs.glsl", "res/shaders/toon_fs.glsl"));

	// Materials 
	Material* test_mat_r = h->addMaterial("test_mat_r", new Material(gouraud_shader));
	Material* test_mat_g = h->addMaterial("test_mat_g", new Material(blinn_phong_shader));
	Material* test_mat_b = h->addMaterial("test_mat_b", new Material(toon_shader));
	test_mat_r->setUniformVec3("u_AlbedoColor", Vector3D(1, 0, 0));
	test_mat_g->setUniformVec3("u_AlbedoColor", Vector3D(0, 1, 0));
	test_mat_b->setUniformVec3("u_AlbedoColor", Vector3D(0, 0, 1));
	test_mat_b->setTexture(toon_ramp_texture);

	Material* test_mat_texture = h->addMaterial("test_mat_texture", new Material(texture_shader));
	test_mat_texture->setTexture(test_texture);

	//plane
	Matrix4 plane_transform = MxFactory::rotation4(Vector3D(1, 0, 0), 90) 
							* MxFactory::scaling4(Vector3D(4, 1, 4))
							* MxFactory::translation4(Vector3D(0,-5,0));
	graph.addChild(test_mat_texture, plane_mesh, "plane", plane_transform);
	
	//cylinder
	graph.addChild(test_mat_r, cylinder_mesh, "cylinder", MxFactory::translation4(Vector3D(-3, 0, 0)));

	//cube
	graph.addChild(test_mat_g, cube_mesh, "cube");

	//torus
	graph.addChild(test_mat_b, torus_mesh, "torus", MxFactory::translation4(Vector3D(3, 0, 0)));

	graph.describe();
}

>>>>>>> main

void createShaderProgram()
{
	app.populateScene();

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not create shaders.");
#endif
}

void destroyShaderProgram()
{
	Manager::destroy();
#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not destroy shaders.");
#endif
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createBufferObjects()
{
	Manager::getInstance()->init();
	
#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
#endif
}

void destroyBufferObjects()
{
	
#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
#endif
}

/////////////////////////////////////////////////////////////////////// SCENE

<<<<<<< HEAD
=======
void walk(GLFWwindow* win, double elapsed) {
	int r = (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS ), 
		l = (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS),
		d = (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS),
		u = (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS);

	double xaxis = (double) r - l, 
		yaxis = (double) d - u;

	if (xaxis != 0 || yaxis != 0) {
		Vector3D dir = Vector3D(xaxis, 0, yaxis);
		dir.normalize();

		cam.move(dir, sprint_factor * speed * elapsed);
	}
}

double old_x, old_y;
double angle_x = M_PI_2 / 50, angle_y = M_PI / 50;

void look(GLFWwindow* win, double elapsed) {
	double x, y;
	glfwGetCursorPos(win, &x, &y);

	int w, h;
	glfwGetWindowSize(win, &w, &h);

	double move_x = (x - old_x);
	double move_y = (y - old_y);

	if (move_x != 0 || move_y != 0) 
		cam.look(angle_x * move_x * elapsed, angle_y * move_y * elapsed);

	old_x = x;
	old_y = y;
}

void animate(GLFWwindow* win, double elapsed) {
	//Matrix4 transf = MxFactory::rotation4(Vector3D(1, 0, 0), 180 * elapsed);
	//graph.applyTransform("torus",transf);
}

void processInput(GLFWwindow* win, double elapsed) {
	if (reset_cam) {
		cam.eye = Vector3D(0, 0, 20);
		cam.center = Vector3D(0, 0, 0);
		cam.up = Vector3D(0, 1, 0);

		cam.updateView();
		reset_cam = false;
	}
	else {
		walk(win, elapsed);
		look(win, elapsed);
	}

	animate(win, elapsed);
}

>>>>>>> main
void drawScene(GLFWwindow* win, double elapsed)
{
	app.update(win, elapsed);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not draw scene.");
#endif
}


///////////////////////////////////////////////////////////////////// CALLBACKS

void window_close_callback(GLFWwindow* win)
{
	destroyShaderProgram();
	destroyBufferObjects();
	std::cout << "closing..." << std::endl;
}

void window_size_callback(GLFWwindow* win, int winx, int winy)
{
	std::cout << "size: " << winx << " " << winy << std::endl;
	glViewport(0, 0, winx, winy);
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	app.keyCallback(win, key, scancode, action, mods);
}

void mouse_callback(GLFWwindow* win, double xpos, double ypos)
{
	app.mouseCallback(win, xpos, ypos);
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
	/*
	glfwSetCursorPosCallback(win, mouse_callback);
	glfwSetMouseButtonCallback(win, mouse_button_callback);
	glfwSetScrollCallback(win, scroll_callback);
	glfwSetJoystickCallback(joystick_callback);
	*/
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
	createShaderProgram();
	createBufferObjects();
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
	drawScene(win, elapsed_sec);
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

////////////////////////////////////////////////////////////////////////// MAIN


int main(int argc, char* argv[])
{
	/**/
	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		1920, 1080, "Hello Modern 2D World", is_fullscreen, is_vsync);

	run(win);
	/**/
	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END