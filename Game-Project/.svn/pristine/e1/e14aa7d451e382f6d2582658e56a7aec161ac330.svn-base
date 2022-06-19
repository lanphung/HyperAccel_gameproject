#pragma once
#include "Enemy.h"
#include <iostream>



class EnemyRectangle : public Enemy
{

public:
	EnemyRectangle(float width, float height);
	EnemyRectangle();
	~EnemyRectangle();

	b2BodyDef rectangleBD;
	b2PolygonShape rectangle;
	b2FixtureDef rectangleFD;
	int c;
	float x;
	float y;
	void RenderBox2D(b2World* world);
	void takeDame(float32 dame);
	void release();
	void Die(b2World* world);
	void hit(b2World* world);
	bool outOfRange();
	float GetHp() { return hp; }
	char* className() { return "EnemyRectangle"; }
};