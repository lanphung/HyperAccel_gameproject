#pragma once
#include"ObjectPhysic.h"

class Collision : public ObjectPhysic
{
public:
	Collision();
	~Collision();
	static void checkCollision(ObjectPhysic* obj1, ObjectPhysic* obj2);
	static void Die(b2World* world,ObjectPhysic* obj);
protected:
	static void Enemy_Bullet(ObjectPhysic* obj1, ObjectPhysic* obj2);
	static void Main_Enemy(ObjectPhysic* obj1, ObjectPhysic* obj2);
};