#include "bulletboss.h"

bulletboss::bulletboss(float width, float height)
{
	m_type = 2;
	m_isRender = false;
	this->width = width;
	this->height = height;

	rectangle.SetAsBox(this->width / 2, this->height / 2);

	rectangleBD.type = b2_dynamicBody;

	rectangleFD.shape = &rectangle;
	rectangleFD.density = 10000.0f;
	rectangleFD.filter.categoryBits = k_enemyCategory;
	rectangleFD.filter.maskBits = k_enemyMask;
	userData = new UserData;
	userData->thisEnemy = this;
}

bulletboss::~bulletboss()
{
	//delete userData;
	//userData = NULL;
}

void bulletboss::RenderBox2D(b2World* world)
{
	/*if (m_body == NULL)
	{
	return;
	}*/
	Box2DSceneManager* m = Box2DSceneManager::GetInstance();
	if (m->m_objectList.at(MAX_ENEMYCIRCLE + MAX_ENEMYRECTANGLE + MAX_ENEMYBULLET + 1)->m_body != NULL)
		if (m->m_objectList.at(0)->m_body != NULL)
	{
		
		float x1 = m->m_objectList.at(0)->m_body->GetPosition().x;
		x = m->m_objectList.at(MAX_ENEMYCIRCLE + MAX_ENEMYRECTANGLE + MAX_ENEMYBULLET + 1)->m_body->GetPosition().x;
		y = m->m_objectList.at(MAX_ENEMYCIRCLE + MAX_ENEMYRECTANGLE + MAX_ENEMYBULLET + 1)->m_body->GetPosition().y;
		rectangleBD.position.Set(x,y);
		b2Vec2 z = b2Vec2(x1 - x, -y);
		z.Normalize();
		z.x *= speed;
		z.y *= speed;
		rectangleBD.linearVelocity = b2Vec2(z);
		m_hp = hp;
		m_isRender = true;
		m_body = world->CreateBody(&rectangleBD);
		m_body->CreateFixture(&rectangleFD);

		m_body->SetUserData(userData);
	}
}

void bulletboss::release()
{
	delete userData;
	userData = NULL;
}

void bulletboss::takeDame(float32 dame)
{
	m_hp -= dame;
	Die(m_body->GetWorld());
}

void bulletboss::Die(b2World* world)
{
	if ((m_hp <= 0.0f) || outOfRange())
	{
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
	}

}

void bulletboss::hit(b2World * world)
{

}

bool bulletboss::outOfRange()
{
	float32 x, y;
	x = m_body->GetPosition().x;
	y = m_body->GetPosition().y;
	if (x > (MAX_RANGE_WIDTH / 2 - width / 2) || x < (-MAX_RANGE_WIDTH / 2 + width / 2))
		return true;
	if (y >(MAX_RANGE_HEIGHT / 2 - width / 2) || y < (-MAX_RANGE_HEIGHT / 2 + width / 2))
		return true;
	return false;
}