#pragma once
#include "Box2DSceneManager.h"
#include"Enemy.h"
#include"EnemyCircle.h"
#include "define.h"
class bulletboss : public Enemy
{
public:
		bulletboss(float width,float height);
	    ~bulletboss();


		b2BodyDef rectangleBD;
		b2PolygonShape rectangle;
		b2FixtureDef rectangleFD;
		void RenderBox2D(b2World *world);
		float x;
		float y;
		void takeDame(float32 dame);
		void release();
		void Die(b2World* world);
		void hit(b2World* world);
		bool outOfRange();
		char* className() { return "BulletBoss"; };
};