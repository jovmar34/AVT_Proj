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
	ret.hasTextures = (textInd.size() > 0);
	ret.hasNormals = (normInd.size() > 0);
}

void ObjLoader::processMeshData()
{
	for (unsigned int i = 0; i < posInd.size(); i++) {
		unsigned int vi = posInd[i];
		Vector3D v = posData[vi - 1];
		ret.positions.push_back(v);
		if (ret.hasTextures)
		{
			unsigned int ti = textInd[i];
			Vector2D t = textData[ti - 1];
			ret.textureCoords.push_back(t);
		}
		if (ret.hasNormals)
		{
			unsigned int ni = normInd[i];
			Vector3D n = normData[ni - 1];
			ret.normals.push_back(n);
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
	loadMeshData(filename);
	processMeshData();
	freeMeshData();
	return ret;
}
