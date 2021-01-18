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
	double t_frame = 0.0f;
	bool reset_cam = false;
	bool save_img = false;
	bool add_mesh = false;
	bool new_mat = false;
	bool new_obj = false;
	bool enter_command = false;
	int mesh_indicator = 0;
	bool choosing_object = false;

	double old_x = 0, old_y = 0;
	double angle_x = M_PI_2 / 50, angle_y = M_PI / 50;

	// gizmo manipulation
	Vector4D worldDir;
	Vector3D pos;
	Vector2D screenDir;
	bool gizmoActive = false;
	double gizmo_x, gizmo_y, scale;
	TransformInfo fullTransform,
		localTransform;


	void processInput(GLFWwindow* win, double elapsed);
	void manipulateGizmo(GLFWwindow* win, double elapsed);
	void animate(GLFWwindow* win, double elapsed);
	void look(GLFWwindow* win, double elapsed);
	void walk(GLFWwindow* win, double elapsed);
	void save(GLFWwindow* win);

public:
	void populateScene();
	void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
	void mouseCallback(GLFWwindow* win, double xpos, double ypos) { }
	void mouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
	void update(GLFWwindow* win, double elapsed);
	
	void enterCommand();
	
	
	// Import Commands
	void importMesh(string meshname);
	void importShader(string shadername);
	void importTexture(string texturename);
	
	// Object Commands
	void loadObject(string objecttype);
	void createObject(string objname, string meshname, string materialname);
	void destroyObject(string objname);
	void objectSetMaterial(string objname, string materialname);
	void objectSetParent(string objname, string parentname);
	
	
	void createMaterial(string materialname, string shadername);
	void materialSetUniform(string materialname, string uniformname, string uniformtype, string uniform_value);
	
};