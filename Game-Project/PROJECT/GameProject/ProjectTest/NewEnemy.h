#pragma once
#include"Enemy.h"
#include"Box2DSceneManager.h"
#include"time.h"
class NewEnemy : public Enemy
{
public:
	NewEnemy(float width, float height);
	~NewEnemy();
	b2BodyDef rectangleBD;
	b2PolygonShape rectangle;
	b2FixtureDef rectangleFD;
	int c;
	float x;
	float y;
	void RenderBox2D(b2World* world);
	void takeDame(float32 dame);
	void Die(b2World* world);
	bool outOfRange();
	void release();
	char* className() { return "NewEnemy"; }
};