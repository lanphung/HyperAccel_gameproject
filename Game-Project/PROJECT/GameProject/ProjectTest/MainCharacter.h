#pragma once
#include "ObjectPhysic.h"
#include "DetectEnemy.h"
#include "EnemyRectangle.h"
#include <iostream>

class EnemyRectangle;

class MainCharacter : public ObjectPhysic
{
private:
	float32 maxShield;
	float32 shield;
	float32 timeRegenShield;
	float32 regenShield;
public:
	MainCharacter();
	~MainCharacter();

	void RenderBox2D(b2World *world);
	void takeDame(float32 dame);
	void Die(b2World* world);
	void hit(b2World *world);
	float GetHp() { return hp; };
	//void release();
	char* className() { return "MainCharacter"; };
	float GetShield();
};

