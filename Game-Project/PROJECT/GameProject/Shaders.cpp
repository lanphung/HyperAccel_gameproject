#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
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
	positionAttribute = glGetAttribLocation(program, "a_posL");	 /// get the attribute index of a_posL in the shader program
	particlePosAttribute = glGetAttribLocation(program, "a_pos");
	particleColorAttribute = glGetAttribLocation(program, "a_Color");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	iTextureLoc[0]  = glGetUniformLocation(program, "u_texture");
	wvpMatLoc	 = glGetUniformLocation(program, "u_wvp");
	uTimeLoc = glGetUniformLocation(program, "u_Time");
	iSpriteFrameXLoc = glGetUniformLocation(program, "iSpriteFrameX");
	iSpriteFrameYLoc = glGetUniformLocation(program, "iSpriteFrameY");
	utextColor = glGetUniformLocation(program, "textColor");
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}