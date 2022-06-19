#pragma once
#include "Box2D/Box2D.h"
const uint16 k_mainCategory = 0x0002;
const uint16 k_enemyCategory = 0x0004;
const uint16 k_bulletCategory = 0x0008;
const uint16 k_towerCategory = 0x0010;

const uint16 k_towerMask = 0xFFFF ^ k_towerCategory^ k_bulletCategory ^ k_mainCategory;
const uint16 k_mainMask = 0xFFFF ^ k_bulletCategory;
const uint16 k_enemyMask = 0xFFFF ^ k_enemyCategory;
const uint16 k_bulletMask = 0xFFFF  ^ k_mainCategory;
#include "define.h"
struct UserData
{
	char* name = "enemy";
	void *thisEnemy;
};

class ObjectPhysic 
{
protected:
	UserData *userData;
public:
	ObjectPhysic();
	~ObjectPhysic();
	b2Body *m_body;
	int m_id;
	int m_type;
	int m_life;
	float m_hp;
	float hp;
	int bom ;
	float speed;
	int render;
	bool m_isRender;
	bool renderboss;
	int m_point;
	inline float32 RandomFloat(float32 lo, float32 hi)
	{
		float32 r = (float32)(rand() & (32677));
		r /= 32677;
		r = (hi - lo) * r + lo;
		return r;
	}
	virtual char* className() { return 0; }
	float width, height, posX, posY, initialLife;
	virtual void RenderBox2D(b2World *world) {};
	virtual void Update(b2World *world) {};
	virtual void release() { };
	virtual void hit(b2World *world) {};
	virtual bool outOfRange() { return true; };
	virtual void takeDame(float32 dame) {};
	virtual void Die(b2World* world) {};
	virtual float GetHp() { return hp; };
	virtual float GetShield() { return 0; };
};

