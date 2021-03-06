#include "PhysicsEngine.h"
#include "define.h"
#include "Game.h"
PhysicsEngine * PhysicsEngine::ms_pInstance = NULL;

void PhysicsEngine::Init()
{
	b2Vec2 gravity(0.0f,0.0f);
	m_world = new b2World(gravity);
	Box2DSceneManager::CreateInstance();
	m_b2D = Box2DSceneManager::GetInstance();
	m_b2D->LoadData();
	
	m_b2D->m_objectList.at(0)->RenderBox2D(m_world);
	lazerTower = new LazerTower(0.0f, 0.0f);
	lazerTower->buildLazerTower(m_world);
	b2Vec2 v(0.0, -8.0);
	m_b2D->m_objectList.at(0)->posY = -8.0f;
	lazerTower->lazerTowerBody->SetTransform(lazerTower->lazerTowerBody->GetPosition() + v, lazerTower->lazerTowerBody->GetAngle());
	isDetonated = false;
	timeStep = 0.0f;
	timeStepBase = 0.0f;
	dead = 1;
}

void PhysicsEngine::release()
{
	m_b2D->Release();
	m_b2D->DestroyInstance();
}

void PhysicsEngine::Key(int key, float32 deltaTime,int Isdown)
{
	
	if (m_b2D->m_objectList.at(0)->m_body != NULL)
		if (m_b2D->m_objectList.at(0)->m_isRender = true)
		{
			b2Vec2 v(1.0* deltaTime, 0.0);
			v.Normalize();
			v.x *= 0.5f;
			v.y *= 0.5f;
			if (key&KeyRightMove && m_b2D->m_objectList.at(0)->m_body->GetPosition().x + v.x <= (float)SCREEN_WIDTH / 2)
			{
				m_b2D->m_objectList.at(0)->m_body->SetTransform(m_b2D->m_objectList.at(0)->m_body->GetPosition() + v, m_b2D->m_objectList.at(0)->m_body->GetAngle());
				lazerTower->lazerTowerBody->SetTransform(lazerTower->lazerTowerBody->GetPosition() + v, lazerTower->lazerTowerBody->GetAngle());
			}
			if (key&KeyLeftMove && m_b2D->m_objectList.at(0)->m_body->GetPosition().x - v.x >= - (float)SCREEN_WIDTH / 2)
			{
				m_b2D->m_objectList.at(0)->m_body->SetTransform(m_b2D->m_objectList.at(0)->m_body->GetPosition() - v, m_b2D->m_objectList.at(0)->m_body->GetAngle());
				lazerTower->lazerTowerBody->SetTransform(lazerTower->lazerTowerBody->GetPosition() - v, lazerTower->lazerTowerBody->GetAngle());
			}
			if ((key&KeyBom)&&(Isdown==1))
			{
				if (m_b2D->m_objectList.at(0)->bom > 0)
				{
					isDetonated = true;
					//printf("so bom %d", m_b2D->m_objectList.at(0)->bom);
					for (int i = 1; i < m_b2D->m_objectList.size(); i++)
					{
						if (m_b2D->m_objectList.at(i)->m_isRender == true && m_b2D->m_objectList.at(i)->m_body != NULL)
						{

							float x = m_b2D->m_objectList.at(i)->m_body->GetPosition().x;
							float y = m_b2D->m_objectList.at(i)->m_body->GetPosition().y;
							float x1 = m_b2D->m_objectList.at(0)->m_body->GetPosition().x;
							float y1 = m_b2D->m_objectList.at(0)->m_body->GetPosition().y;
							if (pow(x1-x, 2) + pow(y1-y, 2) <= pow(50, 2))
							{
								m_b2D->m_objectList.at(i)->takeDame(500);
							}
						}
					}
					m_b2D->m_objectList.at(0)->bom--;
					KeyManager::GetInstance()->m_Isdown = 0;
				}
			
				
			}
			if (!((key&KeyLeftMove )|| (key&KeyRightMove)))
			{
				//cout << "STand" << endl;
				m_b2D->m_objectList.at(0)->m_body->SetLinearVelocity(b2Vec2(0.0, 0.0));
				lazerTower->lazerTowerBody->SetLinearVelocity(b2Vec2(0.0, 0.0));
			}
		}
}
void PhysicsEngine::TouchUp()
{
	if(m_b2D->m_objectList.at(0)->m_body!=NULL)
	if(m_b2D->m_objectList.at(0)->m_isRender=true)
	m_b2D->m_objectList.at(0)->m_body->SetAngularVelocity(0.0);
}

void PhysicsEngine::TouchDown(float angle)
{
	if (m_b2D->m_objectList.at(0)->m_body != NULL)
	if (m_b2D->m_objectList.at(0)->m_isRender = true)
	{
		b2Vec2 pos = m_b2D->m_objectList.at(0)->m_body->GetPosition();
		m_b2D->m_objectList.at(0)->m_body->SetTransform(pos, angle);
	}
}

void PhysicsEngine::Update(float deltaTime)
{
	
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
		if (timeRenderEnemyCircle >= 100+(int)(deltaTime*1000))
		{
			for (int i = 0; i < MAX_ENEMYCIRCLE; i++)
			{
				if (m_b2D->m_objectList.at(i + 1)->m_isRender == false && m_b2D->m_objectList.at(i + 1)->className() == "EnemyCircle")
				{
					m_b2D->m_objectList.at(i + 1)->RenderBox2D(m_world);
					break;
				}
			}
			
			timeRenderEnemyCircle = -1;
		}
		timeRenderEnemyCircle++;
		if (timeRenderEnemyRectangle >= 420 + (int)(deltaTime * 1000))
		{
			for (int i = 0; i < MAX_ENEMYRECTANGLE; i++)
			{
				if (m_b2D->m_objectList.at(i + MAX_ENEMYCIRCLE + 1)->m_isRender == false && m_b2D->m_objectList.at(i + MAX_ENEMYCIRCLE + 1)->className() == "EnemyRectangle")
				{
					m_b2D->m_objectList.at(i + MAX_ENEMYCIRCLE + 1)->RenderBox2D(m_world);
					break;
				}
			}
			timeRenderEnemyRectangle = 0;
		}
		timeRenderEnemyRectangle++;

		if (timeRenderEnemyBulletboss >= 80 + (int)(deltaTime * 1000))
		{
			for (int i = 0; i < MAX_ENEMYBULLET; i++)
			{
				if (m_b2D->m_objectList.at(i + MAX_ENEMYCIRCLE + MAX_ENEMYRECTANGLE + 1)->m_isRender == false && m_b2D->m_objectList.at(i + MAX_ENEMYCIRCLE + MAX_ENEMYRECTANGLE + 1)->className() == "BulletBoss"
					&& m_b2D->m_objectList.at(MAX_ENEMYCIRCLE + MAX_ENEMYRECTANGLE + MAX_ENEMYBULLET + 1)->m_isRender)
				{
					m_b2D->m_objectList.at(i + MAX_ENEMYCIRCLE + MAX_ENEMYRECTANGLE + 1)->RenderBox2D(m_world);
					break;
				}
			}

			timeRenderEnemyBulletboss = 0;
		}

		timeRenderEnemyBulletboss++;

		/////////////////////BOSS/////////// 
		if (timeRenderEnemyBoss >= 3400 + (int)(deltaTime * 1000) && dead != 0 )
		{
			
			{
				if (m_b2D->m_objectList.at(ENEMYBOSS)->m_isRender == false && m_b2D->m_objectList.at(ENEMYBOSS)->className() == "Boss"
					)
				{
					//printf("return");
					m_b2D->m_objectList.at(ENEMYBOSS)->RenderBox2D(m_world);
					dead = 0;
				}
			}
		}

		timeRenderEnemyBoss ++;
		////////////////////////////////////////
		if (m_b2D->m_objectList.at(ENEMYBOSS)->m_isRender && m_b2D->m_objectList.at(ENEMYBOSS)->m_body != NULL)
		{
			if (m_b2D->m_objectList.at(ENEMYBOSS)->m_body->GetPosition().x > 25)
				m_b2D->m_objectList.at(ENEMYBOSS)->m_body->SetLinearVelocity(b2Vec2(-10, 0));
			if (m_b2D->m_objectList.at(ENEMYBOSS)->m_body->GetPosition().x < -25)
				m_b2D->m_objectList.at(ENEMYBOSS)->m_body->SetLinearVelocity(b2Vec2(10, 0));
		}
		int boss = ENEMYBOSS;
		if (timeItem >= 700 + (int)(deltaTime * 1000))
		{
			for (int i = 0; i < MAX_ITEMHP; i++)
			{
				//std::cout << m->m_objectList.at(i + 1)->render << std::endl;
				if (m_b2D->m_objectList.at(boss + 1 + i)->render == 0 && m_b2D->m_objectList.at(boss + 1 + i)->m_isRender == false && m_b2D->m_objectList.at(boss + 1 + i)->className() == "ItemHp")
				{
					//std::cout << "CIRCLE RESPAWN" << std::endl;
					m_b2D->m_objectList.at(boss + 1 + i)->RenderBox2D(m_world);
					//break;
				}
			}

			timeItem = 0;
		}
		timeItem++;
		if (timehp >= 400 + (int)(deltaTime * 1000))
		{
			for (int i = 0; i < MAX_ITEMBOM; i++)
			{
				//std::cout << m->m_objectList.at(i + 1)->render << std::endl;
				if (m_b2D->m_objectList.at(boss + 1 + MAX_ITEMHP + i)->render == 0 && m_b2D->m_objectList.at(boss + 1 + MAX_ITEMHP + i)->m_isRender == false && m_b2D->m_objectList.at(boss + 1 + MAX_ITEMHP + i)->className() == "ItemBom")
				{
					//std::cout << "CIRCLE RESPAWN" << std::endl;
					m_b2D->m_objectList.at(boss + 1 + MAX_ITEMHP + i)->RenderBox2D(m_world);
				}
			}

			timehp = 0;
		}

		timehp++;
		if (timenew >= 1000 + (int)(deltaTime * 1000))
		{
			for (int i = 0; i < MAX_NEWENEMY; i++)
			{
				if (m_b2D->m_objectList.at(i + 19)->render == 0 && m_b2D->m_objectList.at(i + 19)->m_isRender == false && m_b2D->m_objectList.at(i + 19)->className() == "NewEnemy"  && m_b2D->m_objectList.at(0)->m_isRender == true)
				{
					m_b2D->m_objectList.at(i + 19)->RenderBox2D(m_world);
					break;
				}
			}

			timenew = 0;
		}

		timenew++;

		if (timenewbullet >= 250 + (int)(deltaTime * 1000))
		{
			for (int i = 0; i < MAX_BULLETNEWENEMY; i++)
			{
				if (m_b2D->m_objectList.at(i + 22)->m_isRender == false && m_b2D->m_objectList.at(i + 22)->className() == "BulletNewenemy"  && m_b2D->m_objectList.at(0)->m_isRender == true)
				{
					m_b2D->m_objectList.at(i + 22)->RenderBox2D(m_world);
					break;
				}
			}

			timenewbullet = 0;
		}

		timenewbullet++;
		
		///////////////////////BOSS
		if (dead == 0)
		{
			//printf("d = %d", dead);
			if (m_b2D->m_objectList.at(ENEMYBOSS)->m_body == NULL  && m_b2D->m_objectList.at(ENEMYBOSS)->m_isRender == false)
			{
				m_b2D->m_objectList.at(ENEMYBOSS)->m_hp *= 1.2;
				timeRenderEnemyBoss = -1;
				for (int i = 1; i < MAX_ENEMYCIRCLE + MAX_ENEMYRECTANGLE + 1; i++)
				{
					m_b2D->m_objectList.at(i)->speed *= 1.1;
					m_b2D->m_objectList.at(i)->m_hp *= 1.1;
				}
				for (int i = 0; i < MAX_BULLET; i++)
				{
					m_b2D->m_bullet.at(i)->m_hp *= 1.1;
				}
				dead = 1;
			}
		}
		///////////////////////////////

		int tmp = 10 / FIRING_SPEED;
		if (step % tmp == 0)
		{
			for (int i = 0; i < MAX_BULLET; i++)
			{
				
				if (m_b2D->m_bullet.at(i)->m_isRender == false && m_b2D->m_objectList.at(0)->m_isRender == true)
				{
					SoundEngine::GetInstance()->playSound("MAIN_BULLET");
					m_b2D->m_bullet.at(i)->RenderBox2D(m_world);
					break;
				}

			}
		}
		step++;



		for (int i = 0; i < MAX_BULLET; i++)
		{
			if (m_b2D->m_bullet.at(i)->m_isRender == true)
			{
				if (m_b2D->m_bullet.at(i)->m_body != NULL)
					m_b2D->m_bullet.at(i)->hit(m_world);
			}
		}
		if (phase >= 1) lazerTower->updateForLazer(m_world);
		if (phase >= 2) lazerTower->updateForMissile(m_world);

		if (m_b2D->m_objectList.at(0)->m_body != NULL)
		{
			m_b2D->m_objectList.at(0)->hit(m_world);
		}

		for (int i = 1; i <= MAX_ENEMYCIRCLE + MAX_ENEMYRECTANGLE + MAX_ENEMYBULLET; i++)
		{
			if (m_b2D->m_objectList.at(i)->m_isRender == true && m_b2D->m_objectList.at(i)->m_body != NULL)
				m_b2D->m_objectList.at(i)->Die(m_world);
		}

		if (timeStep >= timeStepBase + 1.0 / LIMIT_FPS)
		{
			m_world->Step(1.0f / LIMIT_FPS, velocityIterations, positionIterations);
			//timeStep = 0.0f;
			timeStepBase = timeStep;
			for (int i = 0; i < MAX_BULLET; i++)
			{
				if (m_b2D->m_bullet.at(i)->m_isRender == true)
				{
					if (m_b2D->m_bullet.at(i)->m_body != NULL)
						m_b2D->m_bullet.at(i)->hit(m_world);
				}
			}
		}
		timeStep += deltaTime*10.0f;
		
}

