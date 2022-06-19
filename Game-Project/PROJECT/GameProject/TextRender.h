#pragma once
#include"ft2build.h"
#include FT_FREETYPE_H
#include"Shaders.h"
#include"Globals.h"
#include<string>
#include<iostream>
using namespace std;

class TextRender
{
protected:
	TextRender();
	~TextRender();
	static TextRender* ms_Instance;
public:
	static TextRender*GetIntance();
	static void CreateInstance()
	{
		if (ms_Instance == NULL)
			ms_Instance = new TextRender;
	}
	static void DestroyIntance();
	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glyphSlot;
	Shaders * m_Shader;
	GLuint m_texture;
	GLuint m_vboId;
	Matrix projection;
	void InitShader(char *filevs, char *filefs);
	void SetFont(char *font);
	void RenderString(char *text, Vector4 color, float x, float y, float scaleX, float scaleY);
	void Update(float deltaTime);

};