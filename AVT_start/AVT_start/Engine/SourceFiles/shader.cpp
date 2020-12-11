#include "..\HeaderFiles\shader.h"

std::string Shader::parseShader(const std::string filename)
{
	std::ifstream stream(filename);
	std::string line;
	std::stringstream ss;

	while (getline(stream, line)) {
		ss << line << "\n";
	}

	return ss.str();
}

GLuint Shader::compileShader(GLuint type, const std::string& source)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		std::cerr << errorLog.data() << std::endl;

		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		return -1;
	}

	return id;
}

GLuint Shader::getUniformLocation(std::string name)
{
	if (uniforms.find(name) == uniforms.end()) 
		uniforms[name] = glGetUniformLocation(programId, name.c_str());
	return uniforms[name];
}

Shader::Shader(const std::string vertexFile, const std::string fragmentFile) : programId(0)
{
	std::string vShader = Shader::parseShader(vertexFile),
		fShader = Shader::parseShader(fragmentFile);

	GLuint vShaderId = Shader::compileShader(GL_VERTEX_SHADER, vShader),
		fShaderId = Shader::compileShader(GL_FRAGMENT_SHADER, fShader);

	programId = glCreateProgram();
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);

	glLinkProgram(programId);

	glDetachShader(programId, vShaderId);
	glDeleteShader(vShaderId);
	glDetachShader(programId, fShaderId);
	glDeleteShader(fShaderId);
}

Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(programId);
}

void Shader::bind()
{
	glUseProgram(programId);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::setUniformVec4(std::string uniformName, Vector4D vec)
{
	glUniform4f(getUniformLocation(uniformName), (float) vec.x, (float) vec.y, (float) vec.z, (float) vec.w);
}

void Shader::setUniformVec3(std::string uniformName, Vector3D vec)
{
	glUniform3f(getUniformLocation(uniformName), (float)vec.x, (float)vec.y, (float)vec.z);
}

void Shader::setUniformVec2(std::string uniformName, Vector2D vec)
{
	glUniform2f(getUniformLocation(uniformName), (float)vec.x, (float)vec.y);
}

void Shader::setUniformMat4(std::string uniformName, Matrix4 mat)
{
	glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, mat.toOpenGl());
}

void Shader::setUniform1int(std::string uniformName, int val)
{
	glUniform1i(getUniformLocation(uniformName), val);
}

void Shader::setUniform1float(std::string uniformName, float val)
{
	glUniform1f(getUniformLocation(uniformName), val);
}
