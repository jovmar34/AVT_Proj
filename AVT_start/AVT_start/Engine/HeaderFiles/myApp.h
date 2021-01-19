#pragma once

#include "IApp.h"
#include "manager.h"
#include "FreeImage.h"


class myApp : IApp {
private:
	bool move_camera = false;
	bool first_person = false;

	bool reset_cam = false;
	bool save_img = false;
	bool add_mesh = false;
	bool new_mat = false;
	bool move_obj = false;
	bool new_obj = false;
	int mesh_indicator = 0;
	bool choosing_object = false;
	bool animate_frame = false;

	float xDelta, yDelta;
	double old_x = 0, old_y = 0;
	int w, h;

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
	void cleanScene();
	void walk(GLFWwindow* win, double elapsed);
	void fps_look(GLFWwindow* win, double elapsed);
	void camera_movement(GLFWwindow* win, double elapsed);
	void save(GLFWwindow* win);

public:
	void populateScene();
	void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
	void mouseCallback(GLFWwindow* win, double xpos, double ypos);
	void mouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
	void scrollCallback(GLFWwindow* win, double xoffset, double yoffset);
	
	void update(GLFWwindow* win, double elapsed);

	// Command Processing
	void processCommands(queue<std::string> &commands);
	void executeCommand(std::string command);
	
	// Import Commands
	bool importMesh(string meshname); //x
	bool importShader(string shadername); //x
	bool importTexture(string texturename, string format); //x
	
	// Object Commands
	void loadObject(string objecttype);
	void createObject(string objname, string meshname, string materialname);

	void removeObject(string objname); //x
	void objectSetMaterial(string objname, string materialname); //x
	void objectSetParent(string objname, string parentname); //x
	
	
	void createMaterial(string materialname, string shadername); //x
	void materialSetUniform(string materialname, string uniformname, string uniformtype, string uniform_value); //x
	
	void seeAssets();
	bool checkFile(string filename);
};