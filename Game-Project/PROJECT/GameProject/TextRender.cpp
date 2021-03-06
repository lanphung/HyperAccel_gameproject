#include "stdafx.h"
#include "TextRender.h"

TextRender::TextRender()
{
}

TextRender::~TextRender()
{
	delete m_Shader;
	ms_Instance = NULL;
}

TextRender*TextRender::ms_Instance = NULL;
TextRender * TextRender::GetIntance()
{
	return ms_Instance;
}

void TextRender::DestroyIntance()
{
	if (ms_Instance != NULL)
		delete ms_Instance;
	ms_Instance = NULL;
}

void TextRender::InitShader(char * filevs, char * filefs)
{
	/*
	orthor.
	*/
	projection.SetOrtho(-1.0f, 1.0f, 1.0f, -1.0f, 0.1f, 200.0f);


	/*
	shader
	*/
	m_Shader = new Shaders();
	int k = m_Shader->Init(filevs, filefs);
	if (k != 0) printf(" read shader TextRender fail !\n");

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/* unpack alignment */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &m_vboId);
}

void TextRender::SetFont(char * font)
{

	if (FT_Init_FreeType(&m_ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	if (FT_New_Face(m_ft, font, 0, &m_face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	FT_Set_Pixel_Sizes(m_face, 0, 48);
	m_glyphSlot = m_face->glyph;
}

void TextRender::RenderString(char *text, Vector4 color, float x, float y, float scaleX, float scaleY)
{
	// use glProgram, bind texture & pass color uniform here
	glUseProgram(m_Shader->program);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUniformMatrix4fv(m_Shader->wvpMatLoc, 1, GL_FALSE, (GLfloat*)projection.m);
	glUniform4f(m_Shader->utextColor, color.x, color.y, color.z, color.w);

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glUniform1i(m_Shader->iTextureLoc[0], 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	if (m_Shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_Shader->positionAttribute);
		glVertexAttribPointer(m_Shader->positionAttribute, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	float sx = 1.0f / Globals::screenWidth * scaleX;
	float sy = 1.0f / Globals::screenHeight * scaleY;
	//x = -1.0f + 2.0f * x / Globals::screenWidth;
	//y = -1.0f + 2.0f * y / Globals::screenHeight;
	//x = m_pos.x; y = m_pos.y;
	x = 2.0f * x / Globals::screenWidth;
	y = 2.0f * y / Globals::screenHeight;

	for (const char *p = text; *p; p++)
	{
		if (FT_Load_Char(m_face, *p, FT_LOAD_RENDER))
		{
			continue;
		}

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			m_glyphSlot->bitmap.width,
			m_glyphSlot->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			m_glyphSlot->bitmap.buffer
		);

		float x2 = x + m_glyphSlot->bitmap_left * sx;
		float y2 = -y - m_glyphSlot->bitmap_top * sy;
		float w = m_glyphSlot->bitmap.width * sx;
		float h = m_glyphSlot->bitmap.rows * sy;
		GLfloat box[4][4] = {
			{ x2, -y2 , 0, 0 },
			{ x2 + w, -y2 , 1, 0 },
			{ x2, -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};
		//buffer object

		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);

		x += (m_glyphSlot->advance.x >> 6) * sx;
		y += (m_glyphSlot->advance.y >> 6) * sy;

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void TextRender::Update(float deltaTime)
{
	/*m_MVP->View = Camera::GetInstance()->GetCamView();
	m_MVP->CalMVP();*/
}
