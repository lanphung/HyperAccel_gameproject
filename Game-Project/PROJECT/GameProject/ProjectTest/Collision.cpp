#include"Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

void Collision::checkCollision(ObjectPhysic* obj1, ObjectPhysic* obj2)
{
	if(obj1->className() == "BulletType1"&& obj2->className() == "EnemyRectangle")
		Enemy_Bullet( obj1,  obj2);
	if(obj2->className() == "BulletType1"&& obj1->className() == "EnemyRectangle")
		Enemy_Bullet(obj2, obj1);
	if(obj1->className() == "MainCharacter"&& obj2->className() == "Enemy")
		Main_Enemy( obj1,  obj2);
	if (obj2->className() == "MainCharacter"&& obj1->className() == "Enemy")
		Main_Enemy(obj2, obj1);
	if (obj1->className() == "BulletType1"&& obj2->className() == "EnemyCircle")
		Enemy_Bullet(obj1, obj2);
	if (obj2->className() == "BulletType1"&& obj1->className() == "EnemyCircle")
		Enemy_Bullet(obj2, obj1);
}

void Collision::Enemy_Bullet(ObjectPhysic* obj1, ObjectPhysic* obj2)
{
	obj1->m_body = NULL;
	obj1->m_body->GetWorld()->DestroyBody(obj1->m_body);
	obj1->m_isRender = false;
	obj2->hp -= obj1->hp;
	if (obj2->hp <= 0)
	{
		obj2->m_body->GetWorld()->DestroyBody(obj2->m_body);
		obj2->m_isRender = false;
	}
	//Die(obj2->m_body->GetWorld(),obj2);
}

void Collision::Die(b2World* world, ObjectPhysic* obj)
{
	if (obj->hp <= 0)
	{
		world->DestroyBody(obj->m_body);
   }
}
void Collision::Main_Enemy(ObjectPhysic* obj1, ObjectPhysic* obj2)
{

	//obj2->m_body = NULL;
	obj2->m_body->GetWorld()->DestroyBody(obj2->m_body);
	obj2->m_isRender = false;
	obj1->hp -= obj2->hp;
	if (obj1->hp <= 0)
	{
		obj1->m_body->GetWorld()->DestroyBody(obj1->m_body);
		obj1->m_isRender = false;
	}
}