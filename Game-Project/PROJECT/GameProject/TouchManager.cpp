#include "stdafx.h"
#include "TouchManager.h"
#include "Globals.h"
#include "define.h"
#include <iostream>

TouchManager * TouchManager::ms_pInstance = NULL;

void CoordConvert(Vector2* Coords)
{
	float x = SCREEN_W;
	float y = SCREEN_H;
	if (Coords->x <= x/2 && Coords->y <= y/2)
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

float TouchManager::AngleCalc(Vector2 pos, Vector2 target)
{
	CoordConvert(&target);
	float sign = (target.y < pos.y) ? -1.0 : 1.0;
	float result = 0.0;
	if (target.x >= pos.x) result = sign * atan(abs(target.y - pos.y) / abs(target.x - pos.x));
	else result =  sign * (PI - atan(abs(target.y - pos.y) / abs(target.x - pos.x)));
	return result;
	
}

void TouchManager::MainCharDirUpdate(int x, int y)
{
	Vector3 pos = SceneManager::GetInstance()->GetObjwID(1)->Pos;
	SceneManager::GetInstance()->GetObjwID(1)->SetRotation(AngleCalc(Vector2(pos.x, pos.y), Vector2(float(x), float(y))));	
}

void TouchManager::SetPosTouch(float x, float y)
{
	m_touch = Vector2(x, y);
}
