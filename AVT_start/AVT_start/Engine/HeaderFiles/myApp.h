#pragma once

#include "IApp.h"
#include "manager.h"
#include "FreeImage.h"

class myApp : IApp {
private:
	double sprint_factor = 1;
	double speed = 10;
	bool animate_frame = false;
	bool animate_cubes = false;
	bool stop_cubes = true;
	double ani_time_cubes = 2.0f;
	double ani_time_frame = 5.0f;
	double t_frame = 0.0f, t_cubes = 0.0f;
	bool reset_cam = false;
	bool save_img = false;

	double old_x = 0, old_y = 0;
	double angle_x = M_PI_2 / 50, angle_y = M_PI / 50;


	void processInput(GLFWwindow* win, double elapsed);
	void animate(GLFWwindow* win, double elapsed);
	void look(GLFWwindow* win, double elapsed);
	void walk(GLFWwindow* win, double elapsed);
	void save(GLFWwindow* win);

public:
	void populateScene();
	void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
	void mouseCallback(GLFWwindow* win, double xpos, double ypos) { }
	void update(GLFWwindow* win, double elapsed);
};