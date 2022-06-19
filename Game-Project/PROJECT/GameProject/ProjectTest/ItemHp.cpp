#include"ItemHp.h"

/// This is actually rocket item

ItemHp::ItemHp(float width, float height)
{
	render = 0;
	m_type = 2;
	m_isRender = false;
	this->width = width;
	this->height = height;

	rectangle.SetAsBox(this->width / 2, this->height / 2);

	rectangleBD.type = b2_dynamicBody;

	rectangleFD.shape = &rectangle;
	rectangleFD.density = 100.0f;
	rectangleFD.filter.categoryBits = k_enemyCategory;
	rectangleFD.filter.maskBits = k_enemyMask;
	userData = new UserData;
	userData->thisEnemy = this;
}
ItemHp::~ItemHp()
{

}

void ItemHp::takeDame(float32 dame)
{
	m_hp -= dame;
	Die(m_body->GetWorld());
}
void ItemHp::Die(b2World* world)
{
	Box2DSceneManager* m = Box2DSceneManager::GetInstance();
	if (m_hp < 0.0f)
	{
		if (m->m_objectList.at(0)->bom + 1 <= 10) m->m_objectList.at(0)->bom++;
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
		//printf("so bom %d", m->m_objectList.at(0)->bom);
	}
	else if (outOfRange())
	{
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
	}
}

void ItemHp::RenderBox2D(b2World* world)
{
	x = RandomFloat(-50, 50);
	y = 40;
	rectangleBD.position.Set(x, y);


	/*Box2DSceneManager* m = Box2DSceneManager::GetInstance();
	float x1 = m->m_objectList.at(0)->m_body->GetPosition().x;*/
	b2Vec2 z = b2Vec2(0, -y);
	z.Normalize();
	z.x *= 5;
	z.y *= 5;
	rectangleBD.linearVelocity = b2Vec2(z);
	m_hp = hp;
	m_isRender = true;
	m_body = world->CreateBody(&rectangleBD);
	m_body->CreateFixture(&rectangleFD);
	
	m_body->SetUserData(userData);
}

bool ItemHp::outOfRange()
{
	float32 x, y;
	if (m_body == NULL)
		return true;
	x = m_body->GetPosition().x;
	y = m_body->GetPosition().y;
	if (x >= (MAX_RANGE_WIDTH / 2 - width / 2 - 1) || x <= (-MAX_RANGE_WIDTH / 2 + width / 2 + 1))
		return true;
	if (y >= (MAX_RANGE_HEIGHT / 2 - width / 2 - 1) || y <= (-MAX_RANGE_HEIGHT / 2 + width / 2 + 1))
		return true;
	return false;
}

void ItemHp::release()
{
	delete userData;
	userData = NULL;
}