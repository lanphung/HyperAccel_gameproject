#pragma once
#include "Enemy.h"



class boss : public Enemy
{

public:
	boss(float width, float height);
	~boss();

	b2BodyDef rectangleBD;
	b2PolygonShape rectangle;
	b2FixtureDef rectangleFD;
	int c;
	float x;
	float y;
	void RenderBox2D(b2World* world);
	void release();
	void takeDame(float32 dame);
	void Die(b2World* world);
	void hit(b2World* world);
	char* className() { return "Boss"; }
};