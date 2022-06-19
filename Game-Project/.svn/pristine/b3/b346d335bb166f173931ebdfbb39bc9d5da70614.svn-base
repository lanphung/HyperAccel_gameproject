#pragma once
#include "Box2D/Box2D.h"
#include "DetectEnemy.h"
#include "EnemyRectangle.h"
#include "Missile.h"
#include <vector>

class LazerTower
{
private:
	float32 range;
	float32 fireRate;
	float32 reload;
	float32 damage;
	float32 distanceToNearestEnemy;	
public:
	LazerTower();
	LazerTower(float32 positionX, float32 positionY);
	~LazerTower();

	void buildLazerTower(b2World* m_world);
	void updateForLazer(b2World* m_world);
	void updateForMissile(b2World* m_world);
	void detectEnemy(b2Body* target);
	void focusEnemy();
	void Shoot();

	float32 getLazerTowerAngle();
	b2Vec2 getLazerTowerPosition();
	float32 getRange();
	bool hasOneEnemyInRange();
	bool isMissileLock();
	
	b2BodyDef lazerTowerBodyDef;
	b2Body* lazerTowerBody;
	b2FixtureDef lazerTowerFixtureDef;
	b2PolygonShape lt_polygon;
	//b2Body* enemyTarget;

	Missile *missile;

	EnemyRectangle* enemyTarget;
};