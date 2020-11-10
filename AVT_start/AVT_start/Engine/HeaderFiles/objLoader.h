#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "vector.h"

struct LoaderInfo {
	vector<Vector3D> positions;
	vector<Vector2D> textureCoords;
	vector<Vector3D> normals;
	bool hasTextures, hasNormals;
};

class ObjLoader {
	vector<int> posInd, textInd, normInd;
	vector<Vector3D> posData, normData;
	vector<Vector2D> textData;

	void loadMeshData(std::string& filename);
	void processMeshData();
	void freeMeshData();
	void parseLine(std::stringstream& sin);
	void parseVertex(std::stringstream& sin);
	void parseTexture(std::stringstream& sin);
	void parseNormal(std::stringstream& sin);
	void parseFace(std::stringstream& sin);
public:
	LoaderInfo ret;
	LoaderInfo readFromFile(std::string& filename);
};