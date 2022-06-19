#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Globals.h"
#include "Lights.h"
//#include "Sprite.h"
#include "ResourceManager.h"
#include <iostream>
#include "../Utilities/utilities.h"

class Object
{
	friend class Sprite;
	friend class CButton;

public:
	Object();
	~Object();
	/////////Graphics/////////
	virtual void SpriteInit(int ModelID, int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH) = 0;
	virtual int getSpriteX() = 0;
	virtual int getSpriteY() = 0;
	virtual int getSpriteW() = 0;
	virtual int getSpriteH() = 0;
	void MatUpdate();
	void InputUpdate(float deltaTime);
	void Draw();

	/////////Physics/////////
	void SetPosition(float x, float y);
	void SetRotation(float z);
	void SetSpeed(float speed);
	void SetScale(Vector2 scale);
	Vector2 SetPosition();
	float GetRotation();
	float GetSpeed();
	void MoveForward(float deltaTime);           // Will be moved to enemy subclasses
	void MoveBackward(float deltaTime);		  //
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void RotLeft(float deltaTime);
	void RotRight(float deltaTime);

	/////////Audio/////////

	/////////Misc/////////
	Vector3 Pos;
	Vector3 Rot;
	Vector3 Scale;
	char type[10];
	int ID;
	int TexturesCount;
	int ModelID;
	int ShaderID;
	float u_Time = 0;
	int currentFrameX = 0;
	int currentFrameY = 0;
	float Speed;
	int Isdraw = 0;
	std::vector <int> Texturelist;
	Matrix WVP;
	Shaders theShader;
};
