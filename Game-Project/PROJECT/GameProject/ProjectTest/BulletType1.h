#pragma once
#include "Bullet.h"
#include "Box2DSceneManager.h"
#include "DetectEnemy.h"
//#include "define.h"

class BulletType1 :
	public Bullet
{

public:
	b2Vec2 dir;
	BulletType1();
	~BulletType1();
	void RenderBox2D(b2World *world);
	void release();
	char* className();
	void hit(b2World *world);
	bool outOfRange();
	void bulletHit();
};

