#pragma once
#include "../Utilities/utilities.h"
#define __MAX_STATES 100

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[100];
	char fileFS[100];
	int ID;
	GLint positionAttribute;
	GLint particlePosAttribute;
	GLint particleColorAttribute;
	GLint uvAttribute;
	GLint wvpMatLoc;
	GLint iTextureLoc[5];
	GLint uTimeLoc;
	GLint iSpriteFrameXLoc;
	GLint iSpriteFrameYLoc;
	GLint utextColor;
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};