#include "../HeaderFiles/objLoader.h"

void ObjLoader::loadMeshData(std::string& filename)
{
	std::ifstream ifile(filename);
	std::string line;
	while (std::getline(ifile, line))
	{
		std::stringstream sline(line);
		parseLine(sline);
	}
	ret->hasTextures = (textData.size() > 0);
	ret->hasNormals = (normData.size() > 0);
}

void ObjLoader::processMeshData()
{
	GLuint idx_ctr = 0;
	for (unsigned int i = 0; i < posInd.size(); i++) {
		unsigned int vi = posInd[i], ti = 0, ni = 0;
		if (ret->hasTextures) ti = textInd[i];
		if (ret->hasNormals) ni = normInd[i];

		stringstream keystream;
		keystream << vi << "." << ti << "." << ni;
		std::string key = keystream.str();
		if (verticeIdx.find(key) != verticeIdx.end()) {
			ret->indices.push_back(verticeIdx[key]);
		} else {
			Vector3D v = posData[vi - 1];
			ret->positions.push_back(v);
			if (ret->hasTextures)
			{
				Vector2D t = textData[ti - 1];
				ret->textureCoords.push_back(t);
			}
			if (ret->hasNormals)
			{
				Vector3D n = normData[ni - 1];
				ret->normals.push_back(n);
			}

			verticeIdx[key] = idx_ctr;
			ret->indices.push_back(idx_ctr);
			idx_ctr++;
		}
	}

}

void ObjLoader::freeMeshData()
{
	posData.clear();
	textData.clear();
	normData.clear();
	posInd.clear();
	textInd.clear();
	normInd.clear();
	verticeIdx.clear();
}

void ObjLoader::parseLine(std::stringstream& sin)
{
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parseVertex(sin);
	else if (s.compare("vt") == 0) parseTexture(sin);
	else if (s.compare("vn") == 0) parseNormal(sin);
	else if (s.compare("f") == 0) parseFace(sin);
}

void ObjLoader::parseVertex(std::stringstream& sin)
{
	Vector3D vi;
	sin >> vi;
	posData.push_back(vi);
}

void ObjLoader::parseTexture(std::stringstream& sin)
{
	Vector2D ti;
	sin >> ti;
	textData.push_back(ti);
}

void ObjLoader::parseNormal(std::stringstream& sin)
{
	Vector3D ni;
	sin >> ni;
	normData.push_back(ni);

}

void ObjLoader::parseFace(std::stringstream& sin)
{
	std::string token;
	if (normData.empty() && textData.empty())
	{
		for (int i = 0; i < 3; i++)
		{
			sin >> token;
			posInd.push_back(std::stoi(token));
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			std::getline(sin, token, '/');
			if (token.size() > 0) posInd.push_back(std::stoi(token));
			std::getline(sin, token, '/');
			if (token.size() > 0) textInd.push_back(std::stoi(token));
			std::getline(sin, token, ' ');
			if (token.size() > 0) normInd.push_back(std::stoi(token));
		}
	}
}

LoaderInfo ObjLoader::readFromFile(std::string& filename)
{
	ret = new LoaderInfo();

	loadMeshData(filename);
	processMeshData();
	freeMeshData();
	return *ret;
}
