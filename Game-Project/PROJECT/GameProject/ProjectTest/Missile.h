#pragma once
#include "Box2D\Box2D.h"
#include "DetectEnemy.h"
#include "EnemyRectangle.h"
#include "Bullet.h"

class Missile : public Bullet
{
private:
	float32 dame;
public:
	Missile();
	Missile(float32 positionX, float32 positionY);
	void buildMissile(b2World* m_world);
	~Missile();

	void launchMissile(b2Body *target);
	void detectEnemy(b2Body* target);
	void focusEnemy();
	void hit(b2World *world);
	bool outOfRange();
	void bulletHit();

	b2BodyDef missileBodyDef;
	b2FixtureDef missileFixtureDef;
	b2PolygonShape missileShape;
	b2Body *missileBody;

	EnemyRectangle* enemyTarget;
};
