#pragma once
#include"Bullet.h"
#include"Box2DSceneManager.h"
#include"define.h"
class BulletNewenemy : public Bullet
{
public:
	BulletNewenemy(float width,float height);
	~BulletNewenemy();

	b2BodyDef rectangleBD;
	b2PolygonShape rectangle;
	b2FixtureDef rectangleFD;
	void RenderBox2D(b2World *world);
	float x;
	float y;
	void takeDame(float32 dame);
	void Die(b2World* world);
	bool outOfRange();
	void release();
	char* className() { return "BulletNewenemy"; };

};