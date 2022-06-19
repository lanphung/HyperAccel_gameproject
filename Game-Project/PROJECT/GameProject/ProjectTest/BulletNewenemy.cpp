#include"BulletNewenemy.h"

BulletNewenemy::BulletNewenemy(float width, float height)
{
	m_isRender = false;
	this->width = width;
	this->height = height;
	render = 0;
	rectangle.SetAsBox(this->width / 2, this->height / 2);

	rectangleBD.type = b2_dynamicBody;

	rectangleFD.shape = &rectangle;
	rectangleFD.density = 100.0f;
	rectangleFD.filter.categoryBits = k_enemyCategory;
	rectangleFD.filter.maskBits = k_enemyMask;
	userData = new UserData;
	userData->thisEnemy = this;
}

BulletNewenemy::~BulletNewenemy()
{

}

void BulletNewenemy::RenderBox2D(b2World* world)
{
	m_hp = hp;
	Box2DSceneManager* m = Box2DSceneManager::GetInstance();
	for (int i = 19; i < 22; i++)
	{
		if (m->m_objectList.at(i)->m_isRender == true && m->m_objectList.at(i)->m_body != NULL&&m->m_objectList.at(0)->m_isRender == true)
		{
			x = m->m_objectList.at(i)->m_body->GetPosition().x;
			y = m->m_objectList.at(i)->m_body->GetPosition().y;
			rectangleBD.position.Set(x, y);
			float x1 = m->m_objectList.at(0)->m_body->GetPosition().x;
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
}

void BulletNewenemy::takeDame(float32 dame)
{
	m_hp -= dame;
	Die(m_body->GetWorld());
}
void BulletNewenemy::Die(b2World* world)
{
	if ((m_hp <= 0.0f) || outOfRange())
	{
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
	}
}

bool BulletNewenemy::outOfRange()
{
	float32 x = 50, y = 50;
	if (m_body == NULL)
		return true;
	x = m_body->GetPosition().x;
	y = m_body->GetPosition().y;
	if (x >= (MAX_RANGE_WIDTH / 2 - radius - 1) || x <= (-MAX_RANGE_WIDTH / 2 + radius + 1))
		return true;
	if (y >= (MAX_RANGE_HEIGHT / 2 - radius - 1) || y <= (-MAX_RANGE_HEIGHT / 2 + radius + 1))
		return true;
	return false;
}

void BulletNewenemy::release()
{
	delete userData;
	userData = NULL;
}