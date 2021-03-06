#include "Box2DSceneManager.h"



Box2DSceneManager* Box2DSceneManager::ms_pInstance = NULL;

Box2DSceneManager::Box2DSceneManager()
{
}


Box2DSceneManager::~Box2DSceneManager()
{

}

void Box2DSceneManager::LoadData() {
	FILE *fp = fopen("../Resources/Managers/Box2D_SM.txt", "r");
	if (fp == NULL) {
		printf("the fuck");
		return;
	}
	fscanf(fp, "#Objects: %d\n\n", &m_objectNum);
	for (int i = 0; i < m_objectNum; i++)
	{
		int id;
		char type[50];
		float h;
		fscanf(fp, "ID %d %s\n", &id, type);
		if (strcmp(type, "MainCharacter") == 0)
		{
			ObjectPhysic *o = new MainCharacter();
			fscanf(fp, "POS:  %f %f\n", &o->posX, &o->posY);
			fscanf(fp, "SIZE: %f %f\n", &o->width, &o->height);
			fscanf(fp, "LIFE: %d\n", &o->m_life);
			fscanf(fp, "HP: %f\n\n", &h);
			o->hp = h;
			m_objectList.push_back(o);
			//delete o;
		}
		if (id == 1)
		{
			char hitbox[50];
			fscanf(fp, "HITBOX: %s\n", hitbox);
			if (strcmp(hitbox, "CIRCLE") == 0)
			{
				float radius;
				float dame;
				fscanf(fp, "RADIUS: %f\n", &radius);
				fscanf(fp, "DAME: %f\n\n", &dame);
				if (strcmp(hitbox, "CIRCLE") == 0)
				{
					for (int i = 0; i < MAX_BULLET; i++)
					{
						BulletType1 *b = new BulletType1();
						b->radius = radius;
						b->hp = dame;
						m_bullet.push_back(b);
						//delete b;
					}
				}
			}
		}
		if (id == 2)
		{
			char hitbox[50];
			float spe;
			fscanf(fp, "HITBOX: %s\n", hitbox);
			if (strcmp(hitbox, "CIRCLE") == 0)
			{
				float radius;
				float hp;
				fscanf(fp, "RADIUS: %f\n", &radius);
				fscanf(fp, "HP: %f\n", &hp);
				fscanf(fp, "SPEED: %f\n\n", &spe);
				for (int i = 0; i < MAX_ENEMYCIRCLE; i++)
				{
					ObjectPhysic* enemyCircle = new EnemyCircle(radius);
					enemyCircle->hp = hp;
					enemyCircle->speed = spe;
					enemyCircle->width = radius;
					enemyCircle->height = radius;
					m_objectList.push_back(enemyCircle);
					//delete enemyCircle;
				}
			}
			if (strcmp(hitbox, "RECTANGLE") == 0)
			{
				float width, height;
				float hp;
				fscanf(fp, "SIZE %f %f\n", &width, &height);
				fscanf(fp, "HP: %f\n", &hp);
				fscanf(fp, "SPEED: %f\n\n", &spe);
				for (int i = 0; i < MAX_ENEMYRECTANGLE; i++)
				{
					ObjectPhysic* enemyRectangle = new EnemyRectangle(width,height);
					enemyRectangle->hp = hp;
					enemyRectangle->speed = spe;
					m_objectList.push_back(enemyRectangle);
					//delete enemyRectangle;
				}
			}
		}
		if (id == 3)
		{
			char hitbox[50];
			fscanf(fp, "HITBOX: %s\n", hitbox);
			if (strcmp(hitbox, "RECTANGLE") == 0)
			{
				float width, height;
				float hp;
				float spe;
				fscanf(fp, "SIZE %f %f\n", &width, &height);
				fscanf(fp, "HP: %f\n", &hp);
				fscanf(fp, "SPEED: %f\n\n", &spe);
				for (int i = 0; i < MAX_ENEMYBULLET; i++)
				{
					ObjectPhysic* bossbullet = new bulletboss(width, height);
					bossbullet->hp = hp;
					bossbullet->speed = spe;
					m_objectList.push_back(bossbullet);
					//delete enemyRectangle;
				}
			}
		}
		if (id == 4)
		{
			char hitbox[50];
			fscanf(fp, "HITBOX: %s\n", hitbox);
			if (strcmp(hitbox, "RECTANGLE") == 0)
			{
				float width, height;
				float hp;

				fscanf(fp, "SIZE %f %f\n", &width, &height);
				fscanf(fp, "HP: %f\n\n", &hp);
				
				ObjectPhysic* bos = new boss(width, height);
				bos->hp = hp;
				m_objectList.push_back(bos);
				//delete bos;
				
			}
		}
		if (id == 5)
		{
			char hitbox[50];
			fscanf(fp, "HITBOX: %s\n", hitbox);
			if (strcmp(hitbox, "RECTANGLE") == 0)
			{
				float width, height;
				float hp;
				fscanf(fp, "SIZE %f %f\n", &width, &height);
				fscanf(fp, "HP: %f\n\n", &hp);
				for (int i = 0; i < MAX_ITEMBOM ; i++)
				{
					ObjectPhysic* item = new ItemHp(width, height);
					item->hp = hp;
					m_objectList.push_back(item);
				}

			}
		}
		if (id == 6)
		{
			char hitbox[50];
			fscanf(fp, "HITBOX: %s\n", hitbox);
			if (strcmp(hitbox, "CIRCLE") == 0)
			{
				float radius;
				float hp;
				fscanf(fp, "RADIUS: %f\n", &radius);
				fscanf(fp, "HP: %f\n\n", &hp);
				for (int i = 0; i < MAX_ITEMHP; i++)
				{
					ObjectPhysic* itemhp = new ItemBom(radius);
					itemhp->hp = hp;
					itemhp->width = radius;
					itemhp->height = radius;
					m_objectList.push_back(itemhp);
				}
			}
		}
		if (id == 7)
		{
			char hitbox[50];
			fscanf(fp, "HITBOX: %s\n", hitbox);
			if (strcmp(hitbox, "RECTANGLE") == 0)
			{
				float width, height;
				float hp;
				float spe;
				fscanf(fp, "SIZE %f %f\n", &width, &height);
				fscanf(fp, "HP: %f\n", &hp);
				fscanf(fp, "SPEED: %f\n\n", &spe);
				for (int i = 0; i < MAX_NEWENEMY; i++)
				{
					ObjectPhysic* newenemy = new NewEnemy(width, height);
					newenemy->hp = hp;
					newenemy->speed = spe;
					m_objectList.push_back(newenemy);
				}

			}
		}
		if (id == 8)
		{
			char hitbox[50];
			fscanf(fp, "HITBOX: %s\n", hitbox);
			if (strcmp(hitbox, "RECTANGLE") == 0)
			{
				float width, height;
				float hp;
				float spe;
				fscanf(fp, "SIZE %f %f\n", &width, &height);
				fscanf(fp, "HP: %f\n", &hp);
				fscanf(fp, "SPEED: %f\n\n", &spe);
				for (int i = 0; i < MAX_BULLETNEWENEMY; i++)
				{
					ObjectPhysic* newbullet = new BulletNewenemy(width, height);
					newbullet->hp = hp;
					newbullet->speed = spe;
					m_objectList.push_back(newbullet);
				}

			}
		}
	}
	fclose(fp);

	
}
void Box2DSceneManager::Update()
{

}

void Box2DSceneManager::Release()
{
	for (int i = 0; i < m_objectList.size(); i++)
	{
		m_objectList.at(i)->release();
		delete m_objectList.at(i);
		m_objectList.at(i) = NULL;
	}
	for (int i = 0; i < m_bullet.size(); i++)
	{
		if (m_bullet.at(i) != NULL)
		{
			m_bullet.at(i)->release();
			delete m_bullet.at(i);
			m_bullet.at(i) = NULL;
		}
	}
}



