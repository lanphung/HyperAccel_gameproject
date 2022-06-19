#pragma once
#include "ObjectPhysic.h"

class Bullet :
	public ObjectPhysic
{
public:
	Bullet();
	~Bullet();
	float bulletAngle;
	float radius;
	virtual void RenderBox2D(b2World *world) {};
};

