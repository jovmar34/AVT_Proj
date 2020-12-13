#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "sceneGraph.h"

class IApp {
public:
	SceneGraph graph;
	virtual void populateScene() = 0;
	virtual void update(GLFWwindow *win, double elapsed) = 0;
	virtual void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods) = 0;
	virtual void mouseCallback(GLFWwindow* win, double xpos, double ypos) = 0;
};