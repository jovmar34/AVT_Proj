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
#include "../HeaderFiles/vector.h"
#include "../HeaderFiles/matrix.h"
#include "../HeaderFiles/mxfactory.h"
#include "../HeaderFiles/object.h"
#include "../HeaderFiles/camera.h"
#include "../HeaderFiles/quaternion.h"
#include "../HeaderFiles/objLoader.h"
#include "../HeaderFiles/sceneGraph.h"

double sprint_factor = 1;
double speed = 10;
bool animate_frame = false;
bool animate_cubes = false;
bool stop_cubes = true;
double ani_time_cubes = 2.0f;
double ani_time_frame = 5.0f;
double t_frame = 0.0f, t_cubes = 0.0f;
bool reset_cam = false;

Vector3D coords[] = {
		Vector3D(-0.6666, -1, 2),
		Vector3D(-2, -1	, 3),
		Vector3D(-1.3333, 0.1547, 4),
		Vector3D(-0.6666, 1.3094, 5),
		Vector3D(0.0, 2.4641, 6),
		Vector3D(0.6666, 1.3094, 7),
		Vector3D(1.3333, 0.1547, 8),
		Vector3D(2, -1	, 0),
		Vector3D(0.6666, -1, 1),
};

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
	std::cerr << "Press <return>.";
	std::cin.ignore();
}

void setupErrorCallback()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(error, 0);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, 0, GL_FALSE);
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

/////////////////////////////////////////////////////////////////////// SHADERs

struct ShaderSource {
	std::string VertexSource;
	std::string FragmentSource;

};

GLuint VaoId, VboId[2], UboId;
GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId;
Camera cam;

static ShaderSource ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos) 
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int) type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

static GLuint CompileShader(GLuint type, const std::string& source) {
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		std::cerr << errorLog.data() << std::endl;

		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		return -1;
	}


	return id;
}

void createShaderProgram()
{
	ShaderSource sources = ParseShader("res/shaders/cube.shader");

	std::string VertexShader = sources.VertexSource, 
		FragmentShader = sources.FragmentSource;

	VertexShaderId = CompileShader(GL_VERTEX_SHADER, VertexShader);

	FragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glLinkProgram(ProgramId);
	UboId = glGetUniformBlockIndex(ProgramId, "SharedMatrices");
	glUniformBlockBinding(ProgramId, UboId, UBO_BP);

	glDetachShader(ProgramId, VertexShaderId);
	glDeleteShader(VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);
	glDeleteShader(FragmentShaderId);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not create shaders.");
#endif
}

void destroyShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(ProgramId);

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not destroy shaders.");
#endif
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

int fakes[] = {	0,	0,	0, 0, 0, 0, 0, 0, 1 };

std::vector<Object*> scene;
SceneGraph graph;

void createBufferObjects()
{
	graph.init(ProgramId);
	
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
	if (animate_frame) {
		double time;
		t_frame += elapsed;

		if (t_frame >= ani_time_frame) {
			time = 1;
			animate_frame = false;
			t_frame = 0;
		}
		else {
			time = t_frame / ani_time_frame;
		}

		graph.animateFrame(time);
	}

	if (stop_cubes == false)
		animate_cubes = true;

	if (animate_cubes) {
		double angle;
		t_cubes += elapsed;

		if (t_cubes >= ani_time_cubes) {
			angle = 2 * M_PI;
			t_cubes = 0;

			if (stop_cubes) animate_cubes = false;
		}
		else {
			angle = 2 * M_PI * t_cubes / ani_time_cubes;
		}

		graph.animateCubes(angle);
	}
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

void drawScene(GLFWwindow* win, double elapsed)
{
	processInput(win, elapsed);

	graph.draw();

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
	std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;
	if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_P:
			if (cam.projType == CameraProj::Parallel) {
				cam.perspectiveProjection(60, 4.0f / 3.0f, 1, 50);
			}
			else {
				cam.parallelProjection(-10, 10, -10, 10, 1, 50);
			}
			break;
		case GLFW_KEY_ESCAPE:
			if (cam.state == Working::On) {
				glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else {
				glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			cam.toggle();
			break;
		case GLFW_KEY_LEFT_SHIFT:
			sprint_factor = 1;
			break;
		case GLFW_KEY_F:
			animate_frame = true;
			break;
		case GLFW_KEY_C:
			stop_cubes = !stop_cubes;
			break;
		case GLFW_KEY_R:
			reset_cam = true;
			break;
		}
	}
	else if (action == GLFW_PRESS) {
		switch (key)
		{
		case GLFW_KEY_LEFT_SHIFT:
			sprint_factor = 3;
			break;
		}
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
	//updateFPS(win, elapsed_sec);
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

void populateScene() {
	// Camera init
	cam = Camera(Vector3D(0, 0, 25), Vector3D(0, 0, 0), Vector3D(0, 1, 0));
	cam.parallelProjection(-10,10,-10,10,1,50);

	graph.setCamera(&cam);

	// Painting
	Object* obj;
	std::string filepath;
	ObjLoader c_loader;

	/**/
	graph.setCurrToRoot();

	Matrix4 frameInit = MxFactory::rotation4(Vector3D(0, 1, 0), -90) *
		MxFactory::scaling4(Vector3D(5, 7, 4));

	filepath = "res/meshes/frame.obj";
	LoaderInfo frame_info = c_loader.readFromFile(filepath);
	Mesh frame_mesh(frame_info);
	obj = new Object(frame_mesh, 0, 0);

	graph.addChild(obj, "frame", frameInit);
	graph.setCurr();

	/**/
	Matrix4 frameCounter = MxFactory::invscaling4(Vector3D(5, 7, 4)) *
		MxFactory::invrotation4(Vector3D(0, 1, 0), -90);
	filepath = "res/meshes/backpiece.obj";
	LoaderInfo back_info = c_loader.readFromFile(filepath);
	Mesh back_mesh(back_info);

	obj = new Object(back_mesh, 1, 0);
	Matrix4 backInit = MxFactory::translation4(Vector3D(0, 0, -0.5f)) *
		MxFactory::rotation4(Vector3D(0, 1, 0), -90) *
		MxFactory::scaling4(Vector3D(5, 7, 4));

	graph.addChild(obj, "backpiece", frameCounter * backInit);

	/**/
	filepath = "res/meshes/cube.obj";
	
	LoaderInfo vertices = c_loader.readFromFile(filepath);
	Mesh cube_meh(vertices);

	Matrix4 init =  MxFactory::scaling4(Vector3D(0.5, 0.5, 0.5)) *
		MxFactory::rotation4(Vector3D(0, 1, 0), 45) *
		MxFactory::rotation4(Vector3D(1, 0, 0), 45) *
		MxFactory::rotation4(Vector3D(0, 0, 1), 90);
		
	graph.addChild(nullptr, "cube_container", frameCounter * MxFactory::translation4(Vector3D(0, -0.1547f, 0)));
	graph.setCurr();

	for (int i = 0; i < 9; i++) {
		stringstream ss;
		obj = new Object(cube_meh, -1, fakes[i]); 

		ss << "cube" << i;
		graph.addChild(obj, ss.str(), MxFactory::translation4(Vector3D(coords[i])) * init);
	}

	/**/

	graph.describe();
}

int main(int argc, char* argv[])
{
	/**/
	populateScene();

	/**/
	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		640, 480, "Hello Modern 2D World", is_fullscreen, is_vsync);

	run(win);
	/** /
	
	SceneGraph graph;
	graph.setTransform(MxFactory::translation4(Vector3D(0, 0, -1)));
	graph.addChild("frame");
	graph.addChild("backpiece");
	graph.addChild("cube_container");
	graph.setCurr();
	graph.addChild("cube1", MxFactory::translation4(Vector3D(0, 0, 1)));
	graph.addChild("cube2", MxFactory::translation4(Vector3D(0, 0, 2)));

	graph.describe();
	/**/
	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END