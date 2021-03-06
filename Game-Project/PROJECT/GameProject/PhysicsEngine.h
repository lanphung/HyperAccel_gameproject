#pragma once
//#include "PhysEngine\Test.h"
#include <Box2D\Box2D.h>

//#include "ProjectTest\Box2DSceneManager.h"
#include "ProjectTest\Box2DSceneManager.h"
#include "ProjectTest\BulletType1.h"
#include "ProjectTest\EnemyCircle.h"
#include "ProjectTest\EnemyRectangle.h"
#include "ProjectTest\UpgradeBullet.h"
#include "ProjectTest\Lazertower.h"
#include "ProjectTest\define.h"

class PhysicsEngine
{
protected:
	PhysicsEngine() {}
	~PhysicsEngine() {
		delete m_world;
		delete lazerTower;
		//delete m_body;
	}
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	PhysicsEngine(const PhysicsEngine &) {}
	PhysicsEngine& operator =(const PhysicsEngine &) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new PhysicsEngine;
	}
	static PhysicsEngine * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		if (ms_pInstance)
		{

			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}

	b2World* m_world;
	float32 timeStep;
	float32 timeStepBase;
	int step = 0;
	int index = 0;
	int timeRenderEnemyCircle = 0;
	int timeRenderEnemyRectangle = 0;
	int timeRenderEnemyBulletboss = 0;
	int timeRenderEnemyBoss = 0;
	int timeRespawn = 0;
	int dam;
	int timeItem = 0;
	int timehp = 0;
	int timenew = 0;
	int timenewbullet = 0;
	int dead;
	int phase = 0;
	float isDetonated;
	//Box2DSceneManager* m_b2D = Box2DSceneManager::GetInstance();
	Box2DSceneManager* m_b2D;
	LazerTower *lazerTower;
	void Init();
	void Update(float deltaTime);
	void release();
	void Key(int key, float32 deltaTime,int Isdown);
	void TouchUp();
	void TouchDown(float angle);
protected:
	static PhysicsEngine * ms_pInstance;

};