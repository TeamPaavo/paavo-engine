#include "..\include\Shader.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace pv;

// Public methods

Shader::Shader()
{
}

Shader::~Shader()
{
	glDeleteShader(_vertexShaderId);
	glDeleteShader(_fragmentShaderId);
	if (_programId != 0) {
		glDeleteProgram(_programId);
		_programId = 0;
	}
}

Shader::Shader(const std::string& vertexFileName, const std::string& fragmentFileName)
{
	load(vertexFileName, fragmentFileName);
	
}

bool Shader::load(const std::string& vertexFileName, const std::string& fragmentFileName)
{
	std::ifstream vertexfile(vertexFileName);
	std::ifstream fragmentfile(fragmentFileName);
	std::stringstream vertexshaderbuffer;
	std::stringstream fragmentshaderbuffer;

	std::string vertexsource;
	std::string fragmentsource;

	_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	
	bool returnvalue = true;
	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile vertex shader
	vertexshaderbuffer << vertexfile.rdbuf();
	vertexsource = vertexshaderbuffer.str();
	const char* vertexSourcePtr = vertexsource.c_str();
	glShaderSource(_vertexShaderId, 1, &vertexSourcePtr, NULL);
	glCompileShader(_vertexShaderId);

	// Did it work?
	glGetShaderiv(_vertexShaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(_vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> vertexErrorMsg(infoLogLength);
	glGetShaderInfoLog(_vertexShaderId, infoLogLength, NULL, &vertexErrorMsg[0]);
	fprintf(stdout, "%s\n", &vertexErrorMsg[0]);

	if (result == GL_FALSE)
		returnvalue = false;

	// Compile fragment shader
	fragmentshaderbuffer << fragmentfile.rdbuf();
	fragmentsource = fragmentshaderbuffer.str();
	const char* fragmentSourcePtr = fragmentsource.c_str();
	glShaderSource(_fragmentShaderId, 1, &fragmentSourcePtr, NULL);
	glCompileShader(_fragmentShaderId);

	// Did it work?
	glGetShaderiv(_fragmentShaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(_fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> fragmentErrorMsg(infoLogLength);
	glGetShaderInfoLog(_fragmentShaderId, infoLogLength, NULL, &fragmentErrorMsg[0]);
	fprintf(stdout, "%s\n", &fragmentErrorMsg[0]);

	if (result == GL_FALSE)
		returnvalue = false;

	// Linking
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);
	glLinkProgram(_programId);

	// Final check
	glGetProgramiv(_programId, GL_LINK_STATUS, &result);
	glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> programErrorMsg(std::max(infoLogLength, int(1)));
	glGetProgramInfoLog(_programId, infoLogLength, NULL, &programErrorMsg[0]);
	fprintf(stdout, "%s\n", &programErrorMsg[0]);

	if (result == GL_FALSE)
		returnvalue = false;

	return returnvalue;

}

void Shader::use(glm::mat4 projection)
{
	_projectionId = glGetUniformLocation(_programId, "projection");
	assert(_projectionId >= 0);

	glUseProgram(_programId);
	glUniformMatrix4fv(_projectionId, 1, GL_FALSE, reinterpret_cast<const float*>(&projection));
}

void Shader::use()
{
	glUseProgram(_programId);
}

GLuint Shader::getProgram()
{
	return _programId;
}

// Private methods