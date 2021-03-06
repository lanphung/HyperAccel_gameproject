#include"ItemBom.h"
#include"Box2DSceneManager.h"

/// This is actually HP item

ItemBom::ItemBom(float radius)
{
	render = 0;
	this->radius = radius;
	m_isRender = false;
	circle.m_radius = this->radius;
	circleBD.type = b2_dynamicBody;

	circleFD.shape = &circle;
	circleFD.density = 100.0f;
	circleFD.filter.categoryBits = k_enemyCategory;
	circleFD.filter.maskBits = k_enemyMask;
	userData = new UserData;
	userData->thisEnemy = this;
}

ItemBom::~ItemBom()
{

}
void ItemBom::takeDame(float32 dame)
{
	m_hp -= dame;
	Die(m_body->GetWorld());
}
void ItemBom::Die(b2World* world)
{
	if (m_hp < 0.0f)
	{
		Box2DSceneManager* m = Box2DSceneManager::GetInstance();
		if (m->m_objectList.at(0)->m_hp + 100 <= 1000) m->m_objectList.at(0)->m_hp += 100;
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
		//printf("hp: %f", m->m_objectList.at(0)->m_hp);
	}
	else if (outOfRange())
	{
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
	}
}

void ItemBom::RenderBox2D(b2World* world)
{
	
		x = RandomFloat(-50, 50);
		y = 40;
		circleBD.position.Set(x, y);
	
	b2Vec2 z = b2Vec2(0, -y);
	z.Normalize();
	z.x *= 5;
	z.y *= 5;
	circleBD.linearVelocity = b2Vec2(z);
	m_hp = hp;

	m_isRender = true;
	m_body = world->CreateBody(&circleBD);

	m_body->CreateFixture(&circleFD);
	
	m_body->SetUserData(userData);
}

bool ItemBom::outOfRange()
{
	float32 x, y;
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

void ItemBom::release()
{
		delete userData;
		userData = NULL;
}