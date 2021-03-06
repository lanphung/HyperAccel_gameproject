#include "stdafx.h"

#include "CButton.h"
CButton::CButton()
{
}

CButton::~CButton()
{
}


void CoordConvert1(Vector2* Coords)
{
	float x = SCREEN_W;
	float y = SCREEN_H;
	if (Coords->x <= x / 2 && Coords->y <= y / 2)
	{
		Coords->x = -(x / 2 - Coords->x);
		Coords->y = y / 2 - Coords->y;
	}
	else if (Coords->x >= x / 2 && Coords->y <= y / 2)
	{
		Coords->x = Coords->x - x / 2;
		Coords->y = y / 2 - Coords->y;
	}
	else if (Coords->x <= x / 2 && Coords->y >= y / 2)
	{
		Coords->x = -(x / 2 - Coords->x);
		Coords->y = -(Coords->y - y / 2);
	}
	else
	{
		Coords->x = Coords->x - x / 2;
		Coords->y = -(Coords->y - y / 2);
	}
}
int CButton::InButton(Vector2 tou)
{
	CoordConvert1(&tou);
	//printf("%f , %f\n", tou.x, tou.y);
	float x = this->Pos.x - this->Scale.x;
	float y = Pos.y + this->Scale.y;
	float w = this->Scale.x * 2;
	float h = this->Scale.y * 2;
	if ((tou.x < x) || (tou.x > x + w) || (tou.y > y) || (tou.y < y - h))
		return 0;
	return 1;
}
void CButton::DrawTexts()
{
	u_Time += 0.01;
	u_Time -= floor(u_Time);
	MatUpdate();
	Shaders* theShader = ResourceManager::GetInstance()->ShadersList.at(ShaderID);
	glUseProgram(theShader->program);
	for (int it = 0; it < TexturesCount; it++)
	{
		Texture* theTexture = ResourceManager::GetInstance()->getTexture(Texturelist[it]);
		glActiveTexture(GL_TEXTURE0 + it);
		glBindTexture(GL_TEXTURE_2D, theTexture->TextureID);
		glUniform1i(theShader->iTextureLoc[it], it);
	}
	ResourceManager::GetInstance()->Models.at(ModelID)->ModelDraw(theShader);
	///////////////
	glUniformMatrix4fv(theShader->wvpMatLoc, 1, GL_FALSE, &WVP.m[0][0]);
	glUniform1f(theShader->uTimeLoc, u_Time);
}
