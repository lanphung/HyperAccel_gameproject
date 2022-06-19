#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

void Sprite::SpriteInit(int ModelID, int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH)
{
	ResourceManager::GetInstance()->Models.at(ModelID)->Vertices[0].uv = Vector2((float)spriteX / textureW, (float)(spriteY + spriteH) /
		textureH);
	ResourceManager::GetInstance()->Models.at(ModelID)->Vertices[1].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(spriteY +
		spriteH) / textureH);
	ResourceManager::GetInstance()->Models.at(ModelID)->Vertices[2].uv = Vector2((float)spriteX / textureW, (float)spriteY / textureH);
	ResourceManager::GetInstance()->Models.at(ModelID)->Vertices[3].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)spriteY /
		textureH);
}

int Sprite::getSpriteX()
{
	return spriteX;
}

int Sprite::getSpriteY()
{
	return spriteY;
}

int Sprite::getSpriteW()
{
	return spriteW;
}

int Sprite::getSpriteH()
{
	return spriteH;
}

