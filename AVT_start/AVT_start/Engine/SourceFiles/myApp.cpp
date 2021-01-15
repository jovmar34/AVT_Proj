#include "..\HeaderFiles\myApp.h"

void myApp::processInput(GLFWwindow* win, double elapsed)
{
	Camera* cam = graph.getCam();

	if (reset_cam) {
		cam->eye = Vector3D(0, 0, 20);
		cam->center = Vector3D(0, 0, 0);
		cam->up = Vector3D(0, 1, 0);

		cam->updateView();
		reset_cam = false;
	}
	else {
		walk(win, elapsed);
		look(win, elapsed);
	}

	if (gizmoActive) {
		manipulateGizmo(win, elapsed);
	}

	animate(win, elapsed);
}

void myApp::manipulateGizmo(GLFWwindow* win, double elapsed)
{
	double x, y;
	glfwGetCursorPos(win, &x, &y);

	std::string name = graph.getSelected()->name;
	TransformInfo info;
	GizmoType type = graph.getGizmoType();
	Vector3D world3D = worldDir.to3D();

	if (type == GizmoType::Translation) {
		Vector2D currDir = Vector2D(x - gizmo_x, gizmo_y - y);

		double dot = currDir * screenDir;

		info = MxFactory::translate(world3D * dot * 0.1);
		graph.setTransforms(name, { useful, info });
	}
	else if (type == GizmoType::Scaling) {
		Vector2D currDir = Vector2D(x - gizmo_x, y - gizmo_y);

		info = MxFactory::scale((Vector3D(1, 1, 1) - world3D) + (world3D * fabs(currDir.length()) * scale));
		graph.setTransforms(name, { info, useful });
	}
	else if (type == GizmoType::Rotation) {
		Vector2D currDir = Vector2D(x - gizmo_x, y - gizmo_y).normalize();

		double cos = currDir * screenDir;
		if (cos > 1) cos = 1;
		if (cos < -1) cos = -1;
		
		Vector3D axis = screenDir.to3D() % currDir.to3D();
		if (axis.length() != 0) {
			axis.normalize();
		}

		std::cout << "axis: " << axis << std::endl;

		double angleDeg = scale * -axis.z * acos(cos) / M_PI_2 * 90;

		std::cout << "angle: " << angleDeg << std::endl;

		//screenDir = currDir;

		info = MxFactory::rotate(world3D, angleDeg);
		graph.setTransforms(name, { info, useful });
	}

	
}

void myApp::animate(GLFWwindow* win, double elapsed)
{
	/** /
	t_frame += elapsed;

	graph.setTransforms("cube", { MxFactory::scale(Vector3D(2, 1, 1)), MxFactory::rotate(Vector3D(0,1,0), t_frame * 90) });
	/**/
}

void myApp::look(GLFWwindow* win, double elapsed)
{
	Camera* cam = graph.getCam();

	double x, y;
	glfwGetCursorPos(win, &x, &y);

	int w, h;
	glfwGetWindowSize(win, &w, &h);

	double move_x = (x - old_x);
	double move_y = (y - old_y);

	if (move_x != 0 || move_y != 0)
		cam->look(angle_x * move_x * elapsed, angle_y * move_y * elapsed);

	old_x = x;
	old_y = y;
}

void myApp::walk(GLFWwindow* win, double elapsed)
{
	Camera* cam = graph.getCam();
	int r = (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS),
		l = (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS),
		d = (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS),
		u = (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS);

	double xaxis = (double) r - l,
		yaxis = (double) d - u;

	if (xaxis != 0 || yaxis != 0) {
		Vector3D dir = Vector3D(xaxis, 0, yaxis);
		dir.normalize();

		cam->move(dir, sprint_factor * speed * elapsed);
	}
}

void myApp::save(GLFWwindow* win)
{
	int w, h;
	glfwGetWindowSize(win, &w, &h);
	
	GLubyte* pixels = new GLubyte[3 * static_cast<size_t>(w * h)];

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, pixels);

	// Convert to FreeImage format & save to file
	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, w, h, 3 * w, 24, 0x0000FF, 0xFF0000, 0x00FF00, false);
	FreeImage_Save(FIF_PNG, image, "test.png", 0);

	// Free resources
	FreeImage_Unload(image);
	delete[] pixels;
}

void myApp::populateScene()
{
	// Camera init
	Camera* cam = new Camera(Vector3D(8, 8, 8), Vector3D(0, 0, 0), Vector3D(0, 1, 0));
	cam->perspectiveProjection(60, 4.0f / 3.0f, 1, 200);
	cam->init();

	graph.setCamera(cam);
	
	// Outline
	Shader* outline_shader = new Shader("res/shaders/outline_vs.glsl", "res/shaders/outline_fs.glsl");
	outline_shader->addUniformBlock("Matrices", 0);
	Material* outline_material = new Material(outline_shader);
	graph.setOutline(outline_material);

	//Asset Manager
	Manager* h = Manager::getInstance();

	// Meshes
	Mesh* cube_mesh = h->addMesh("cube_mesh", new Mesh("res/meshes/cube_smooth.obj"));
	//Mesh* torus_mesh = h->addMesh("torus_mesh", new Mesh("res/meshes/torus.obj"));

	// Shaders
	Shader* blinnphong_shader = h->addShader("blinnphong_shader", new Shader("res/shaders/blinn_phong_vs.glsl", "res/shaders/blinn_phong_fs.glsl"));
	blinnphong_shader->addUniformBlock("Matrices", 0);
	Shader* gooch_shader = h->addShader("gooch_shader", new Shader("res/shaders/gooch_vs.glsl", "res/shaders/gooch_fs.glsl"));
	gooch_shader->addUniformBlock("Matrices", 0);

	// Materials 
	Material* blinnphong_mat = h->addMaterial("blinnphong_mat", new Material(blinnphong_shader));
	blinnphong_mat->setUniformVec3("u_AlbedoColor", Vector3D(0.8f, 0.8f, 0.8f));

	Material* gooch_mat = h->addMaterial("gooch_mat", new Material(gooch_shader));
	gooch_mat->setUniformVec3("u_AlbedoColor", Vector3D(0.8f, 0.8f, 0.8f));

	//cube
	graph.addChild(gooch_mat, cube_mesh, "cube");

	//torus
	//graph.addChild(blinnphong_mat, torus_mesh, "torus");
	//graph.setTransforms("torus", { MxFactory::translate(Vector3D(0,0,-5)) });

	/* 
	IMPORTANT - This is a WIP. The grid needs to be the last thing drawn, always because it has transaparency
				In the future we should probably either move this somewhere else or garantee that transparent 
				objects are drawn after opaque objects. It also shouldn't be selectable...
	*/

	//grid
	Mesh* plane_mesh = h->addMesh("plane_mesh", new Mesh("res/meshes/plane.obj"));
	Shader* grid_shader = h->addShader("grid_shader", new Shader("res/shaders/grid_vs.glsl", "res/shaders/grid_fs.glsl"));
	grid_shader->addUniformBlock("Matrices", 0);
	Material* grid_mat = h->addMaterial("grid_mat", new Material(grid_shader));
	graph.setGrid(grid_mat, plane_mesh, MxFactory::scale(Vector3D(100, 100, 100)));

	//axis
	h->addMesh("translation_gizmo", new Mesh("res/meshes/Gizmos/TranslationGizmo.obj"));
	h->addMesh("scale_gizmo", new Mesh("res/meshes/Gizmos/ScaleGizmo.obj"));
	h->addMesh("rotation_gizmo", new Mesh("res/meshes/Gizmos/AltRotationGizmo.obj"));

	Shader* gizmo_shader = h->addShader("gizmo_shader", new Shader("res/shaders/gizmo_vs.glsl", "res/shaders/gizmo_fs.glsl"));
	gizmo_shader->addUniformBlock("Matrices", 0);
}

void myApp::keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	Camera* cam = graph.getCam();
	std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;
	if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_P:
			if (cam->projType == CameraProj::Parallel) {
				cam->perspectiveProjection(60, 4.0f / 3.0f, 1, 50);
			}
			else {
				cam->parallelProjection(-10, 10, -10, 10, 1, 50);
			}
			break;
		case GLFW_KEY_ESCAPE:
			if (cam->state == Working::On) {
				glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else {
				glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			cam->toggle();
			break;
		case GLFW_KEY_LEFT_SHIFT:
			sprint_factor = 1;
			break;
		case GLFW_KEY_F:
			animate_frame = true;
			break;
		case GLFW_KEY_R:
			if (!gizmoActive)
			graph.setGizmoType(GizmoType::Rotation);
			break;
		case GLFW_KEY_E:
			if (!gizmoActive)
			graph.setGizmoType(GizmoType::Scaling);
			break;
		case GLFW_KEY_G:
			if (!gizmoActive)
			graph.setGizmoType(GizmoType::Translation);
			break;
		case GLFW_KEY_I:
			save_img = true;
			break;
		case GLFW_KEY_M:
			add_mesh = true;
			break;
		case GLFW_KEY_N:
			new_mat = true;
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

void myApp::mouseButtonCallback(GLFWwindow* win, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		double xpos, ypos;
		int height, width;
		glfwGetCursorPos(win, &xpos, &ypos);
		int x = static_cast<int>(xpos);

		glfwGetWindowSize(win, &width, &height);
		int y = height - static_cast<int>(ypos);

		GLuint index;
		glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		if (action == GLFW_PRESS) {
			if (index >= 0xFD) {
				gizmoActive = true;
				graph.gizmoActive = true;
				std::cout << "activate" << std::endl;


				if (index == 0xFF) {
					worldDir = Vector4D(1, 0, 0, 1);
				}
				else if (index == 0xFE) {
					worldDir = Vector4D(0, 1, 0, 1);
				}
				else if (index == 0xFD) {
					worldDir = Vector4D(0, 0, 1, 1);
				}

				Camera* cam = graph.getCam();

				Matrix4 projView = cam->projection * cam->view;

				useful = { graph.getSelected()->transform, graph.getSelected()->inverse };

				Vector4D center = projView * useful.transform * Vector4D(0,0,0,1);
				center.divideByW();	
			
				Vector4D point;
				
				GizmoType gizType = graph.getGizmoType();

				if (gizType == GizmoType::Scaling) {
					gizmo_x = (center.x + 1) / 2 * width;
					gizmo_y = height - (center.y + 1) / 2 * height;

					Vector2D currDir = Vector2D(xpos - gizmo_x, ypos - gizmo_y);

					scale = 1 / currDir.length();
				}
				else if (gizType == GizmoType::Translation) {
					point = projView* ((useful.transform * Vector4D(0, 0, 0, 1)) + worldDir);
					point.divideByW();

					gizmo_x = xpos;
					gizmo_y = ypos;

					screenDir = point.to2D() - center.to2D();
					std::cout << "screen_dir: " << screenDir << std::endl;
				}
				else if (gizType == GizmoType::Rotation) {
					gizmo_x = (center.x + 1) / 2 * width;
					gizmo_y = height - (center.y + 1) / 2 * height;

					pos = (useful.transform * Vector4D(0, 0, 0, 1)).to3D();

					Vector3D relativeEye = cam->eye - cam->center;

					scale = relativeEye * worldDir.to3D();

					if (scale == 0) scale = 1;
					else scale /= fabs(scale);

					screenDir = Vector2D(xpos - gizmo_x, ypos - gizmo_y).normalize();
				}
			}
		}
		if (action == GLFW_RELEASE) {
			if (gizmoActive) {
				std::cout << "deactivate" << std::endl;
				gizmoActive = false;
				graph.gizmoActive = false;
			}
			else if (index < 0xFD) {
				if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
					graph.changeParent(index);
				}
				else {
					graph.setSelected(index);
				}
			}
		}
	}
}

void myApp::update(GLFWwindow *win, double elapsed)
{
	processInput(win, elapsed);
	graph.draw();
	if (save_img) {
		save(win);
		save_img = false;
	}
	if (add_mesh) {
		Manager* h = Manager::getInstance();
		Mesh* mesh = h->addMesh("new_mesh", new Mesh("res/meshes/AxisGizmo.obj"));
		mesh->init();

		Material* material = h->getMaterial("blinnphong_mat");

		graph.setCurrToRoot();
		graph.addChild(material, mesh, "new_guy", MxFactory::translation4(Vector3D(0,5,0)));
		add_mesh = false;
	}
	if (new_mat) {
		Manager* h = Manager::getInstance();
		SceneNode* node = graph.getNode("cube");

		Shader* toon_shader = h->addShader("toon_shader", new Shader("res/shaders/toon_vs.glsl", "res/shaders/toon_fs.glsl"));
		toon_shader->addUniformBlock("Matrices", 0);

		Texture* toon_ramp_texture = h->addTexture("toon_ramp_texture", new Texture("res/textures/toon_ramp_texture.png"));

		Material* test_mat_b = h->addMaterial("test_mat_b", new Material(toon_shader));
		test_mat_b->setUniformVec3("u_AlbedoColor", Vector3D(0, 0, 1));
		test_mat_b->setTexture(toon_ramp_texture);

		node->material = test_mat_b;
		new_mat = false;
	}
}
