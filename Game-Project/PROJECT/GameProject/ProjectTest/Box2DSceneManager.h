#pragma once
#include "define.h"
#include "MainCharacter.h"
#include "BulletType1.h"
#include "EnemyCircle.h"
#include "EnemyRectangle.h"
#include "UpgradeBullet.h"
#include "bulletboss.h"
#include "boss.h"
#include"ItemBom.h"
#include"ItemHp.h"
#include"BulletNewenemy.h"
#include"NewEnemy.h"
#include <vector>
using namespace std;

class BulletType1;

class Box2DSceneManager
{
public:
	Box2DSceneManager();
	~Box2DSceneManager();
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new Box2DSceneManager;
	}
	static Box2DSceneManager * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		if (ms_pInstance != NULL)
		{
			//delete m_world;
			//delete body;
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}
	vector <ObjectPhysic*> m_objectList;
	vector <BulletType1*> m_bullet;
	int m_objectNum;
	void LoadData();
	void Update();
	void Release();


protected:
	static Box2DSceneManager* ms_pInstance;
};

