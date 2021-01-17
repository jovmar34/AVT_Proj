#include "..\HeaderFiles\serializer.h"

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
		out << "- Material:\n\t- Name: " << name << "\n\t- Uniforms:\n\t\t- Vector4D:\n" << std::endl;
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
			out << "\t\t\t- Name: " << itUniformsF1->first << "\n\t\t\t- Int: " << itUniformsF1->second << std::endl;
		}
	}

}

void SceneSerializer::serializeNode(SceneNode* node, std::ofstream& out)
{
	out << "Node:\n" << "- Name: " << node->getName() << "\n- Children: " << node->children.size() 
		<< "\n- Material:" << "\n\t- Name: " << node->materialName << "\n\t- Texture:\n\t\t- Name: " << node->textureName << "\n\t\t- FilePath: " << node->textureFile
		<< "\n\t- Shaders:\n\t\t- Name: " << node->shaderName << "\n\t\t- Vertex Shader Filepath: " << node->vertexShaderFile << "\n\t\t- Fragment Shader Filepath: " << node->fragmentShaderFile
		<< "\n\t- Outline: " << node->outline
		<< "\n- Mesh: \n\t- Name: "<< node->meshName <<"\n\t- Filepath: " << node->meshFile 
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
		<< "\n- Material:" << "\n\t- Name: " << _parent->materialName << "\n\t- Texture:\n\t\t- Name: " << _parent->textureName << "\n\t\t- FilePath: " << _parent->textureFile
		<< "\n\t- Shaders:\n\t\t- Name: " << _parent->shaderName << "\n\t\t- Vertex Shader Filepath: " << _parent->vertexShaderFile << "\n\t\t- Fragment Shader Filepath: " << _parent->fragmentShaderFile
		<< "\n\t- Outline: " << _parent->outline
		<< "\n- Mesh: \n\t- Name: " << _parent->meshName << "\n\t- Filepath: " << _parent->meshFile 
		<< "\n- Transformation: " << _parent->getTransform().toString() << std::endl;

	for (int i = 0; i < _parent->children.size(); i++) {
		n = _parent->children[i];
		serializeNode(n, file);
	}
	file.close();
}

double* extractNumbers(std::string str)
{
	int num, i = 0;
	double* numbers = new double[16];
	std::fill_n(numbers, 16, 0);

	std::string temp;
	for (int x = 0; x < str.length(); x++ ) {
		if (isdigit(str[x])) {
			temp.push_back(str[x]);
			numbers[i] = std::stoi(temp);
			cout << "part a: ";
			cout << numbers[i] << endl;
			for (int y = x + 1; y < str.length(); y++) {
				if (y >= str.length()) break;
				else if (isdigit(str[y]) || str[y] == '.') {
					if (isdigit(str[y])) {
						temp.push_back(str[y]);
							//numbers[i] = numbers[i] * 10 + std::stoi(temp);
							numbers[i] = numbers[i] + std::stoi(temp);
							cout << "part b: ";
							cout << numbers[i] << endl;
					}
					x = y;
				}
				else break;
			}
			i++;
			temp.clear();
		}
	}

	return numbers;
}

void SceneSerializer::deserialize(const std::string& filepath)
{
	std::ifstream file(filepath, ios::in);
	std::string line, delimiter, type, ecu, workingState, matrix;
	size_t pos = 0;
	int l;
	double* numbers;
	double* values;
	Matrix4 invViewMatrix;
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
			numbers = extractNumbers(ecu);
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
			if (matrix == "- View Matrix: ") {
				while (l < 4) {
					std::getline(file, matrix);
					numbers = extractNumbers(matrix);
					l++;
				}
			}
			Matrix4 viewMatrix(numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9], numbers[10], numbers[11], numbers[12], numbers[13], numbers[14], numbers[15]);
			std::getline(file, matrix);

			//Projection Matrix
			std::getline(file, matrix);
			l = 0;
			if (matrix == "- Projection Matrix: ") {
				while (l < 4) {
					std::getline(file, matrix);
					numbers = extractNumbers(matrix);
					l++;
				}
			}
			Matrix4 projMatrix(numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7], numbers[8], numbers[9], numbers[10], numbers[11], numbers[12], numbers[13], numbers[14], numbers[15]);
			std::getline(file, matrix);

			//InvView Matrix
			std::getline(file, matrix);
			l = 0;
			if (matrix == "- InvView Matrix: ") {
				while (l < 4) {
					std::getline(file, matrix);
					values = extractNumbers(matrix);
					l++;
				}
				Matrix4 invViewMatrix(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7], values[8], values[9], values[10], values[11], values[12], values[13], values[14], values[15]);
				cout << invViewMatrix.toString();
			}
			//Matrix4 invViewMatrix(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7], values[8], values[9], values[10], values[11], values[12], values[13], values[14], values[15]);
			

			Camera cam = Camera(eye, center, up);
			if (type == "Parallel") {
				cam.projType = CameraProj::Parallel;

			}
			else if (type == "Perspective") {
				cam.projType = CameraProj::Perspective;

			}
			if (workingState == "On") {
				cam.state = Working::On;
			}
			
		}
		else if (line == "Manager:") {
			//cout << "manager queennnnnn\n";
			//shaders
			//meshes
			//textures
			//materials
		}
		else if(line == "Node:"){
			//cout << "node slayyyy bitch\n";
			//name
			//children
			//material
			//texture
			//mesh
			//transformation matrix
		}
		//cout << line << endl;
	}

	file.close();
}