#include "Shaders_cube.h"

int Shaders_cube::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);
	positionAttribute = glGetAttribLocation(program, "aPos");
	uvAttributex = glGetAttribLocation(program, "TexCoords");
	wvpMatLoc = glGetUniformLocation(program, "wvp");
	return 0;
}

Shaders_cube::~Shaders_cube()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}