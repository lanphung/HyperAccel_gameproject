#pragma once
#include"Enemy.h"
#include"Box2DSceneManager.h"
#include"define.h"
#include"time.h"
class ItemHp : public Enemy
{
public:
	ItemHp(float width, float height);
	~ItemHp();


	b2BodyDef rectangleBD;
	b2PolygonShape rectangle;
	b2FixtureDef rectangleFD;
	float x;
	float y;
	int c;
	void takeDame(float32 dame);
	void Die(b2World* world);
	char* className() { return "ItemHp"; }
	void RenderBox2D(b2World* world);
	bool outOfRange();
	void release();
};