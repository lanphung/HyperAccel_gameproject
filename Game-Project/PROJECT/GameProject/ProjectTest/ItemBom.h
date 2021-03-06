#pragma once
#include"Enemy.h"
#include"define.h"
#include"time.h"
class ItemBom : public Enemy
{
public:
	ItemBom(float radius);
	~ItemBom();
	b2BodyDef circleBD;
	b2CircleShape circle;
	b2FixtureDef circleFD;
	float radius;
	int c;
	float x;
	float y;
	void RenderBox2D(b2World *world);
	void takeDame(float32 dame);
	void Die(b2World* world);
	bool outOfRange();
	char* className() { return "ItemBom"; }
	void release();
};