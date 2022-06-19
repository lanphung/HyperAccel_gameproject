#include "Object.h"
#include "Game.h"
#include "KeyManager.h"

Object::Object()
{

}

Object::~Object()
{

}

void Object::InputUpdate(float deltaTime)
{
	int m_key = KeyManager::GetInstance()->GetKey();
	if (m_key&KeyUpMove)
	{
	//	MoveForward(deltaTime);
	}
	if (m_key&KeyDownMove)
	{
//		MoveBackward(deltaTime);
	}
	if (m_key&KeyLeftMove)
	{
		MoveLeft(deltaTime);
	}
	if (m_key&KeyRightMove)
	{
		MoveRight(deltaTime);
	}
	if (m_key&KeyUpRota)
	{
		//glBlendFunc(GL_ONE, GL_ONE);
	}
	if (m_key&KeyDownRota)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	if (m_key&KeyLeftRota)
	{
		RotRight(deltaTime);
		
	}
	if (m_key&KeyRightRota)
	{
		RotLeft(deltaTime);
	}
	if (m_key&KeyUpRota)
	{
		glBlendFunc(GL_ONE, GL_ONE);
	}
	if (m_key&KeyDownRota)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void Object::MatUpdate()
{
	Matrix WorldMat, ViewMat, PerspectiveMat, ScaleMat, RotMat, RotXMat, RotYMat, RotZMat, TransMat;
	RotXMat.SetRotationX(Rot.x); RotYMat.SetRotationY(Rot.y); RotZMat.SetRotationZ(Rot.z);
	RotMat = RotZMat * RotXMat * RotYMat;
	ScaleMat.SetScale(Scale.x, Scale.y, Scale.z);
	TransMat.SetTranslation(Pos.x, Pos.y, Pos.z);
	WorldMat = ScaleMat * RotMat * TransMat;
	WVP = WorldMat * WVP::GetInstance()->getViewMat() *Game::GetInstance()->orthoMat;
	
}

void Object::Draw()
{
	u_Time += 0.001;
	u_Time -= floor(u_Time);
	MatUpdate();
	glUseProgram(theShader.program);
	for (int it = 0; it < TexturesCount; it++)
	{
		Texture* theTexture = ResourceManager::GetInstance()->getTexture(Texturelist[it]);
		glActiveTexture(GL_TEXTURE0 + it);
		glBindTexture(GL_TEXTURE_2D, theTexture->TextureID);
		glUniform1i(theShader.iTextureLoc[it], it);
	}
	///////////////
	glUniformMatrix4fv(theShader.wvpMatLoc, 1, GL_FALSE, &WVP.m[0][0]);
	glUniform1f(theShader.uTimeLoc, u_Time);
	glUniform1i(theShader.iSpriteFrameXLoc, currentFrameX);
	glUniform1i(theShader.iSpriteFrameYLoc, currentFrameY);
	//////////////
	ResourceManager::GetInstance()->Models.at(ModelID)->ModelDraw(&theShader);


}

void Object::SetPosition(float x, float y)
{
	
	Pos.x = x;
	Pos.y = y;
}

void Object::SetRotation(float z)
{
	Rot.z = z;
}

void Object::SetSpeed(float speed)
{
	Speed = speed;
}

void Object::SetScale(Vector2 tscale)
{
	Scale.x = tscale.x;
	Scale.y = tscale.y;
}

Vector2 Object::SetPosition()
{
	return Vector2(Pos.x, Pos.y);
}

float Object::GetRotation()
{
	return Rot.z;
}

float Object::GetSpeed()
{
	return Speed;
}

void Object::MoveForward(float deltaTime)
{
	Vector2 target;
	target.x = Pos.x + 2.0*deltaTime*cos(Rot.z);
	target.y = Pos.y + 2.0*deltaTime*sin(Rot.z);
	SetPosition(target.x, target.y);
}

void Object::MoveBackward(float deltaTime)
{
	Vector2 target;
	target.x = Pos.x - 2.0*deltaTime*cos(Rot.z);
	target.y = Pos.y - 2.0*deltaTime*sin(Rot.z);
	SetPosition(target.x, target.y);
}

void Object::MoveLeft(float deltaTime)
{
	Vector2 target;
	target.x = Pos.x - 200* deltaTime;
	target.y = Pos.y;
	if (target.x >= - Globals::screenWidth / 2)
		SetPosition(target.x, target.y);
}

void Object::MoveRight(float deltaTime)
{
	Vector2 target;
	target.x = Pos.x + 200*deltaTime;
	target.y = Pos.y;
	if (target.x <= Globals::screenWidth / 2)
		SetPosition(target.x, target.y);

}

void Object::RotLeft(float deltaTime)
{
	float temp = Rot.z - 10*deltaTime;
	temp = temp > -6.28319 ? temp : ( temp + 6.28319);
	SetRotation(temp);

}

void Object::RotRight(float deltaTime)
{
	float temp = Rot.z + 10*deltaTime;
	temp = temp < 6.28319 ? temp : (temp - 6.28319);
	SetRotation(temp);
}