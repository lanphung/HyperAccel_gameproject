#pragma once
#include "Object.h"

class Sprite : public Object
{
public:
	Sprite();
	~Sprite();
	void SpriteInit(int ModelID, int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH);
	int spriteX;
	int spriteY;
	int spriteW;
	int spriteH;
	int getSpriteX();
	int getSpriteY();
	int getSpriteW();
	int getSpriteH();
	
};