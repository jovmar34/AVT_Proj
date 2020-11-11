#include "..\HeaderFiles\shader.h"

Shader::Shader(const std::string& filepath)
	: m_shaderPath(filepath), m_shaderId(0)
{
	ShaderSource sources = parseShader(filepath);

	std::string VertexShader = sources.VertexSource,
		FragmentShader = sources.FragmentSource;

	GLuint VertexShaderId = CompileShader(GL_VERTEX_SHADER, VertexShader);

	GLuint FragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

	m_shaderId = glCreateProgram();
	glAttachShader(m_shaderId, VertexShaderId);
	glAttachShader(m_shaderId, FragmentShaderId);

	glDetachShader(m_shaderId, VertexShaderId);
	glDeleteShader(VertexShaderId);
	glDetachShader(m_shaderId, FragmentShaderId);
	glDeleteShader(FragmentShaderId);
}

Shader::~Shader()
{
	glDeleteProgram(m_shaderId);
}

void Shader::Bind()
{
	glUseProgram(m_shaderId);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::setUniformMatrix(const std::string& name, Matrix4 mat)
{
	GLuint location = getUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, mat.toOpenGl());
}

GLuint Shader::getUniformLocation(const std::string& name)
{
	return glGetUniformLocation(m_shaderId, name.c_str());
}

ShaderSource Shader::parseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

GLuint Shader::CompileShader(GLuint type, const std::string& source) {
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
};
