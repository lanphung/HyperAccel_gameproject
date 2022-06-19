#pragma once
#include "Enemy.h"
#include <iostream>

class EnemyCircle : public Enemy
{
public:
	EnemyCircle(float radius);
	~EnemyCircle();
	
	b2BodyDef circleBD;
	b2CircleShape circle;
	b2FixtureDef circleFD;
	float radius;
	int c;
	float x;
	float y;
	void RenderBox2D(b2World *world);
	void release();
	void takeDame(float32 dame);
	float GetHp() { return hp; }
	void Die(b2World* world);
	void hit(b2World* world);
	bool outOfRange();
	char* className() { return "EnemyCircle"; }
};