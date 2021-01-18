#include "..\HeaderFiles\serializer.h"
#include <algorithm>

SceneSerializer::SceneSerializer(Camera* cam, Manager* man, SceneNode* par) {
	_camera = cam;
	_manager = man;
	_parent = par;
}

SceneSerializer::SceneSerializer(Camera* cam) {
	_camera = cam;
}

SceneSerializer::SceneSerializer(SceneNode* par) {
	_parent = par;
}

SceneSerializer::SceneSerializer() {
	_camera = nullptr;
	_manager = nullptr;
	_parent = nullptr;
}

SceneSerializer::~SceneSerializer()
{
//todo
}

void SceneSerializer::serializeCamera(std::ofstream& out)
{	
	out << "--- Camera ---\n";
	out << "Camera:\n" << "- Type: " << _camera->projTypeToString() << "\n- Eye, Center, Up: " << _camera->eye << ", " << _camera->center << ", " << _camera->up << "\n- Working State: " << _camera->workingStateToString() << "\n- View Matrix: " << _camera->getView().toString() << "\n- Projection Matrix: " << _camera->getProjection().toString() << "\n- InvView Matrix: " << _camera->getInvView().toString() << std::endl;
}

void SceneSerializer::serializeManager(std::ofstream& out)
{
	out << "--- Manager ---\n";
	out << "Manager:\n";

	std::unordered_map<std::string, Shader*> shaders = _manager->getShaders();
	std::unordered_map<std::string, Shader*>::iterator itShaders;
	std::unordered_map<std::string, Mesh*> meshes = _manager->getMeshes();
	std::unordered_map<std::string, Mesh*>::iterator itMeshes;
	std::unordered_map<std::string, Texture*> textures = _manager->getTextures();
	std::unordered_map<std::string, Texture*>::iterator itTextures;
	std::unordered_map<std::string, Material*> materials = _manager->getMaterials();
	std::unordered_map<std::string, Material*>::iterator itMaterials;

	for (itShaders = shaders.begin(); itShaders != shaders.end(); itShaders++)
	{
		std::string name = itShaders->first;
		out << "- Shader:\n\t- Name: " << name << "\n\t- Vertex Shader Filepath: " << _manager->getShader(name)->vertexShaderFilepath << "\n\t- Fragment Shader Filepath: " << _manager->getShader(name)->fragmentShaderFilepath << std::endl;
	}

	for (itMeshes = meshes.begin(); itMeshes != meshes.end(); itMeshes++)
	{
		std::string name = itMeshes->first;
		out << "- Mesh:\n\t- Name: " << name << "\n\t- Filepath: " << _manager->getMesh(name)->file_path << std::endl;
	}

	for (itTextures = textures.begin(); itTextures != textures.end(); itTextures++)
	{
		std::string name = itTextures->first;
		out << "- Texture:\n\t- Name: " << name << "\n\t- Filepath: " << _manager->getTexture(name)->file_path << std::endl;
	}

	for (itMaterials = materials.begin(); itMaterials != materials.end(); itMaterials++)
	{

		std::unordered_map<std::string, Vector4D> vals_Vec4 = itMaterials->second->getValsVec4();
		std::unordered_map<std::string, Vector4D>::iterator itUniformsV4;
		std::unordered_map<std::string, Vector3D> vals_Vec3 = itMaterials->second->getValsVec3();
		std::unordered_map<std::string, Vector3D>::iterator itUniformsV3;
		std::unordered_map<std::string, Vector2D> vals_Vec2 = itMaterials->second->getValsVec2();
		std::unordered_map<std::string, Vector2D>::iterator itUniformsV2;
		std::unordered_map<std::string, Matrix4> vals_Mat4 = itMaterials->second->getValsMat4();
		std::unordered_map<std::string, Matrix4>::iterator itUniformsM4;
		std::unordered_map<std::string, int> vals_1int = itMaterials->second->getVals1int();
		std::unordered_map<std::string, int>::iterator itUniformsI1;
		std::unordered_map<std::string, float> vals_1float = itMaterials->second->getVals1float();
		std::unordered_map<std::string, float>::iterator itUniformsF1;

		std::string name = itMaterials->first;
		out << "- Material:\n\t- Name: " << name << "\n\t- Shader: " << itMaterials->second->shader->name << "\n\t- Uniforms:\n\t\t- Vector4D:\n" << std::endl;
		//"\n\t- Filepath: " << _manager->getMaterial(name)

		//Uniforms4D
		for (itUniformsV4 = vals_Vec4.begin(); itUniformsV4 != vals_Vec4.end(); itUniformsV4++) 
		{
			out << "\t\t\t- Name: " << itUniformsV4->first << "\n\t\t\t- Values: " << itUniformsV4->second.toString() << std::endl;
		}

		//Uniforms3D
		out << "\t\t - Vector3D:\n";
		for (itUniformsV3 = vals_Vec3.begin(); itUniformsV3 != vals_Vec3.end(); itUniformsV3++)
		{
			out << "\t\t\t- Name: " << itUniformsV3->first << "\n\t\t\t- Values: " << itUniformsV3->second.toString() << std::endl;
		}

		//Uniforms2D
		out << "\t\t - Vector2D:\n";
		for (itUniformsV2 = vals_Vec2.begin(); itUniformsV2 != vals_Vec2.end(); itUniformsV2++)
		{
			out << "\t\t\t- Name: " << itUniformsV2->first << "\n\t\t\t- Values: " << itUniformsV2->second.toString() << std::endl;
		}

		//UniformsM4
		out << "\t\t - Matrix4:\n";
		for (itUniformsM4 = vals_Mat4.begin(); itUniformsM4!= vals_Mat4.end(); itUniformsM4++)
		{
			out << "\t\t\t- Name: " << itUniformsM4->first << "\n\t\t\t- Matrix: " << itUniformsM4->second.toString() << std::endl;
		}

		//Uniforms1int
		out << "\t\t - 1int:\n";
		for (itUniformsI1 = vals_1int.begin(); itUniformsI1 != vals_1int.end(); itUniformsI1++)
		{
			out << "\t\t\t- Name: " << itUniformsI1->first << "\n\t\t\t- Int: " << itUniformsI1->second << std::endl;
		}

		//Uniforms1float
		out << "\t\t - 1float:\n";
		for (itUniformsF1 = vals_1float.begin(); itUniformsF1 != vals_1float.end(); itUniformsF1++)
		{
			out << "\t\t\t- Name: " << itUniformsF1->first << "\n\t\t\t- Float: " << itUniformsF1->second << std::endl;
		}
	}

}

void SceneSerializer::serializeNode(SceneNode* node, std::ofstream& out)
{
	out << "Node:\n" << "- Name: " << node->getName() << "\n- Children: " << node->children.size()
		<< "\n- Material:" << "\n\t- Name: " << node->materialName << "\n- Texture:\n\t- Name: " << node->textureName
		<< "\n- Shaders:\n\t- Name: " << node->shaderName
		<< "\n- Mesh: \n\t- Name: " << node->meshName
		<< "\n- Transformation: " << node->getTransform().toString() << std::endl;
	SceneNode* n;
	for (int i = 0; i < node->children.size(); i++) {
		n = node->children[i];
		serializeNode(n, out);
	}
}

void SceneSerializer::serialize(const std::string& filepath)
{
	SceneNode* n;
	std::ofstream file(filepath);
	serializeCamera(file);
	serializeManager(file);
	file << "--- Graph ---\n";
	file << "Node:\n" << "- Name: " << _parent->getName() << "\n- Children: " << _parent->children.size() 
		<< "\n- Material:" << "\n\t- Name: " << _parent->materialName << "\n- Texture:\n\t Name: " << _parent->textureName 
		<< "\n- Shaders:\n\t- Name: " << _parent->shaderName
		<< "\n- Mesh: \n\t- Name: " << _parent->meshName
		<< "\n- Transformation: " << _parent->getTransform().toString() << std::endl;

	for (int i = 0; i < _parent->children.size(); i++) {
		n = _parent->children[i];
		serializeNode(n, file);
	}
	file.close();
}

//Auxiliar functions
double* extractVectorValues(std::string str)
{
	double* numbers = new double[16];
	std::fill_n(numbers, 16, 0);
	std::string temp;
	int j = 0;

	//Delete (, ) and ,
	str.erase(std::remove(str.begin(), str.end(), '('), str.end());
	str.erase(std::remove(str.begin(), str.end(), ')'), str.end());
	std::replace(str.begin(), str.end(), ',', ' ');
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			temp.push_back(str[i]);
		}
		else {
			if (str[i] == ' ' && str[i + 1] != ' ') {
				double number = std::stod(temp);
				numbers[j++] = number;
				temp.clear();
			}
		}
	}

	return numbers;
}

double* extractMatrixValues(std::string str)
{
	double* numbers = new double[16];
	std::fill_n(numbers, 16, 0);
	std::string temp;
	int j = 0;

	//Delete [ and ] 
	str.erase(std::remove(str.begin(), str.end(), '['), str.end());
	str.erase(std::remove(str.begin(), str.end(), ']'), str.end());
	
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			temp.push_back(str[i]);
		}
		else {
			double number = std::stod(temp);
			numbers[j++] = number;
			temp.clear();
		}
	}

	return numbers;
}


void SceneSerializer::deserialize(const std::string& filepath)
{
	std::ifstream file(filepath, ios::in);
	std::string line, delimiter, type, ecu, workingState, matrix;
	std::string shader_name, shaderV_path, shaderF_path, mesh_name, mesh_filepath, texture_name, texture_filepath, material_name;
	std::string vector_name, matrix_name, int_name, float_name, node_name;
	size_t pos = 0;
	int l, ind, children;
	double* numbers;
	double* aux = new double[16];
	Matrix4 invViewMatrix;

	//Creation objects
	Camera cam;
	Manager* man = Manager::getInstance();
	Material* mt;
	SceneGraph graph;

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		if (line == "Camera:") {
			//Type
			std::getline(file, type);
			delimiter = "- Type: ";
			pos = type.find(delimiter);
			type.erase(0, pos + delimiter.length());

			//Eye, Center, Up
			std::getline(file, ecu);
			delimiter = "- Eye, Center, Up: ";
			pos = ecu.find(delimiter);
			ecu.erase(0, pos + delimiter.length());
			//ecu = "(x, x, x), (y, y, y), (z, z, z)
			numbers = extractVectorValues(ecu);
			Vector3D eye(numbers[0], numbers[1], numbers[2]);
			Vector3D center(numbers[3], numbers[4], numbers[5]);
			Vector3D up(numbers[6], numbers[7], numbers[8]);

			//Working state
			std::getline(file, workingState);
			delimiter = "- Working State: ";
			pos = workingState.find(delimiter);
			workingState.erase(0, pos + delimiter.length());

			//View Matrix
			std::getline(file, matrix);
			l = 0;
			ind = 0;
			if (matrix == "- View Matrix: ") {
				int j = 0;
				while (l < 4) {
					std::getline(file, matrix);
					numbers = extractMatrixValues(matrix);
					aux[j] = numbers[0];
					aux[j + 1] = numbers[1];
					aux[j + 2] = numbers[2];
					aux[j + 3] = numbers[3];
					l++;
					j += 4;
				}
			}
			Matrix4 viewMatrix(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8], aux[9], aux[10], aux[11], aux[12], aux[13], aux[14], aux[15]);
			std::getline(file, matrix);

			//Projection Matrix
			std::getline(file, matrix);
			l = 0;
			ind = 0;
			if (matrix == "- Projection Matrix: ") {
				int j = 0;
				while (l < 4) {
					std::getline(file, matrix);
					numbers = extractMatrixValues(matrix);
					aux[j] = numbers[0];
					aux[j + 1] = numbers[1];
					aux[j + 2] = numbers[2];
					aux[j + 3] = numbers[3];
					l++;
					j += 4;
				}
			}
			Matrix4 projMatrix(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8], aux[9], aux[10], aux[11], aux[12], aux[13], aux[14], aux[15]);
			std::getline(file, matrix);

			//InvView Matrix
			std::getline(file, matrix);
			l = 0;
			if (matrix == "- InvView Matrix: ") {
				int j = 0;
				while (l < 4) {
					std::getline(file, matrix);
					numbers = extractMatrixValues(matrix);
					aux[j] = numbers[0];
					aux[j+1] = numbers[1];
					aux[j+2] = numbers[2];
					aux[j+3] = numbers[3];
					l++;
					j += 4;
				}
			}
			
			Matrix4 invViewMatrix(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8], aux[9], aux[10], aux[11], aux[12], aux[13], aux[14], aux[15]);

			//Camera creation
			cam = Camera(eye, center, up);
			if (type == "Parallel") cam.projType = CameraProj::Parallel;
			else if (type == "Perspective") cam.projType = CameraProj::Perspective;
			if (workingState == "On") cam.state = Working::On;
			cam.view = viewMatrix;
			cam.projection = projMatrix;
			cam.invView = invViewMatrix;
			
		}
		else if (line == "Manager:") {
			std::getline(file, line);

			//Shaders
			while (line == "- Shader:") {
				//Name
				std::getline(file, line);
				delimiter = "- Name: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				shader_name = line;

				//Vertex Shader Filepath
				std::getline(file, line);
				delimiter = "- Vertex Shader Filepath: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				shaderV_path = line;

				//Fragment Shader Filepath
				std::getline(file, line);
				delimiter = "- Fragment Shader Filepath: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				shaderF_path = line;

				Shader* s = new Shader(shader_name, shaderV_path, shaderV_path); //n esquecer destruir isto no fim
				man->addShader(shader_name, s);

				std::getline(file, line);

			}

			//Meshes
			while (line == "- Mesh:") {
				std::getline(file, line);

				//Name
				delimiter = "- Name: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				mesh_name = line;

				//Filepath
				std::getline(file, line);
				delimiter = "- Filepath: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				mesh_filepath = line;

				Mesh* m = new Mesh(mesh_name, mesh_filepath); //n esquecer destruir isto no fim
				man->addMesh(shader_name, m);

				std::getline(file, line);
			}

			//Textures
			while (line == "- Texture:") {
				std::getline(file, line);

				//Name
				delimiter = "- Name: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				texture_name = line;

				//Filepath
				std::getline(file, line);
				delimiter = "- Filepath: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				texture_filepath = line;

				Texture* t = new Texture(texture_name, texture_filepath); //n esquecer destruir isto no fim
				man->addTexture(texture_name, t);

				std::getline(file, line);
			}

			Material material;
			//Materials
			while (line == "- Material:") {
				std::getline(file, line);

				//Name
				delimiter = "- Name: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				material_name = line;

				//Name
				std::getline(file, line);
				delimiter = "- Shader: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				shader_name = line;

				Shader* s = man->getShader(shader_name);  //n esquecer destruir isto no fim
				mt = new Material(s);

				//Uniforms
				std::getline(file, line); //uniforms line
				std::getline(file, line);
				while (line == "- Vector4D:") {
					std::getline(file, line);
					//Name
					delimiter = "- Name: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					vector_name = line;

					//Values
					std::getline(file, line);
					delimiter = "- Values: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					//line = "(x, x, x, x)"
					numbers = extractVectorValues(line);
					Vector4D vec4(numbers[0], numbers[1], numbers[2], numbers[3]);
					mt->setUniformVec4(vector_name, vec4);

					std::getline(file, line);
				}

				while (line == "- Vector3D:") {
					std::getline(file, line);
					//Name
					delimiter = "- Name: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					vector_name = line;

					//Values
					std::getline(file, line);
					delimiter = "- Values: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					//line = "(x, x, x)"
					numbers = extractVectorValues(line);

					Vector3D vec3(numbers[0], numbers[1], numbers[2]);
					mt->setUniformVec3(vector_name, vec3);

					std::getline(file, line);
				}
				while (line == "- Vector2D:") {
					std::getline(file, line);
					//Name
					delimiter = "- Name: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					vector_name = line;

					//Values
					std::getline(file, line);
					delimiter = "- Values: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					//line = "(x, x)"
					numbers = extractVectorValues(line);
					Vector2D vec2(numbers[0], numbers[1]);
					mt->setUniformVec2(vector_name, vec2);

					std::getline(file, line);
				}
				while (line == "- Matrix4:") {
					std::getline(file, line);
					//Name
					delimiter = "- Name: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					matrix_name = line;

					//Values
					std::getline(file, line);
					delimiter = "- Matrix: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					int j = 0;
					while (l < 4) {
						std::getline(file, matrix);
						numbers = extractMatrixValues(matrix);
						aux[j] = numbers[0];
						aux[j + 1] = numbers[1];
						aux[j + 2] = numbers[2];
						aux[j + 3] = numbers[3];
						l++;
						j += 4;
					}
					Matrix4 mat(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8], aux[9], aux[10], aux[11], aux[12], aux[13], aux[14], aux[15]);
					mt->setUniformMat4(matrix_name, mat);
					std::getline(file, line);
				}
				while (line == "- 1int:") {
					std::getline(file, line);
					//Name
					delimiter = "- Name: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					int_name = line;

					//Values
					std::getline(file, line);
					delimiter = "- Int: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					mt->setUniform1int(int_name, stoi(line));

					std::getline(file, line);
				}
				while (line == "- 1float:") {
					std::getline(file, line);
					//Name
					delimiter = "- Name: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					float_name = line;

					//Values
					std::getline(file, line);
					delimiter = "- Float: ";
					pos = line.find(delimiter);
					line.erase(0, pos + delimiter.length());
					mt->setUniform1float(float_name, stof(line));

					std::getline(file, line);
				}
				std::getline(file, line);
			}

			man->addMaterial(material_name, mt);

		}
		else if (line == "Node:") {
			while (line == "Node:") {
				std::getline(file, line);

				//Name
				delimiter = "- Name: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				node_name = line;

				//Children
				std::getline(file, line);
				delimiter = "- Children: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				children = std::stoi(line);

				//Material
				std::getline(file, line);
				std::getline(file, line);
				delimiter = "- Name: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				material_name = line;
				Material* node_material = man->getMaterial(material_name);

				//Texture
				std::getline(file, line);
				std::getline(file, line);
				delimiter = "- Name: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				texture_name = line;

				//Shaders
				std::getline(file, line);
				std::getline(file, line);
				delimiter = "- Name: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				shader_name = line;

				//Mesh
				std::getline(file, line);
				std::getline(file, line);
				delimiter = "- Name: ";
				pos = line.find(delimiter);
				line.erase(0, pos + delimiter.length());
				mesh_name = line;
				Mesh* node_mesh = man->getMesh(mesh_name);

				//Transformation Matrix
				std::getline(file, line);
				std::getline(file, line);
				int j = 0;
				while (l < 4) {
					std::getline(file, matrix);
					numbers = extractMatrixValues(matrix);
					aux[j] = numbers[0];
					aux[j + 1] = numbers[1];
					aux[j + 2] = numbers[2];
					aux[j + 3] = numbers[3];
					l++;
					j += 4;
				}
				Matrix4 transformation_mat(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8], aux[9], aux[10], aux[11], aux[12], aux[13], aux[14], aux[15]);
				
				

				graph.addChild(node_material, node_mesh, "eu nsei que nome dar aqui help");
				std::getline(file, line);
}
		}

	}

	//chamar funçao desenho com as cenas criadas

	file.close();
}