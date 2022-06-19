#include "EnemyRectangle.h"
#include "time.h"
#include "../Game.h"

EnemyRectangle::EnemyRectangle()
{

}

EnemyRectangle::EnemyRectangle(float width, float height)
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

EnemyRectangle::~EnemyRectangle()
{
}

void EnemyRectangle::release()
{
	delete userData;
	userData = NULL;
}

void EnemyRectangle::RenderBox2D(b2World* world)
{
	srand(time(NULL));
	c = rand() % 4 + 1;
	if (c == 1)
	{
		x = RandomFloat(-SCREEN_WIDTH / 2 + width / 2, SCREEN_WIDTH / 2 - width / 2);
		y = RandomFloat(SCREEN_HEIGHT / 2 - 30, SCREEN_HEIGHT / 2 - height / 2);
		rectangleBD.position.Set(x , y);
	}
	if (c == 2)
	{
		x = RandomFloat(-SCREEN_WIDTH / 2 + width / 2, SCREEN_WIDTH / 2 - width / 2);
		y = RandomFloat(-SCREEN_HEIGHT / 2 + height / 2, -SCREEN_HEIGHT / 2 + 30);
		rectangleBD.position.Set(x,y);
	}
	if (c == 3)
	{
		x = RandomFloat(-SCREEN_WIDTH / 2 + width / 2, -SCREEN_WIDTH / 2 + 30);
		y = RandomFloat(-SCREEN_HEIGHT / 2 + 30, SCREEN_HEIGHT / 2 - 30);
		rectangleBD.position.Set(x,y);
	}
	if (c == 4)
	{
		x = RandomFloat(SCREEN_WIDTH / 2 - 30, SCREEN_WIDTH / 2 - width / 2);
		y = RandomFloat(-SCREEN_HEIGHT / 2 + 30, SCREEN_HEIGHT / 2 - 30);
		rectangleBD.position.Set(x,y);
	}
	float x1 = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body->GetPosition().x;
	float y1 = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body->GetPosition().y;
	b2Vec2 z = b2Vec2(x1-x, y1-y);
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



void EnemyRectangle::takeDame(float32 dame)
{
	m_hp -= dame;
	Die(m_body->GetWorld());
}

void EnemyRectangle::Die(b2World* world)
{
	if ((m_hp <= 0 ) || outOfRange())
	{
		if (m_hp <= 0)
		{
			fPoint tmp = fPoint((10 * m_body->GetPosition().x) / SCREEN_CENTER_W, (10 * m_body->GetPosition().y) / SCREEN_CENTER_H);
			Game::GetInstance()->psystem->AddEmiter(tmp, EmitterType::EMITTER_TYPE_MID_EXPLOSION);
			Box2DSceneManager* m = Box2DSceneManager::GetInstance();
			m->m_objectList.at(0)->m_point += POINT_ENEMYRECTANGLE;
		}
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
	}
}

void EnemyRectangle::hit(b2World *world)
{

}

bool EnemyRectangle::outOfRange()
{
	float32 x, y;
	x = m_body->GetPosition().x;
	y = m_body->GetPosition().y;
	if (x >= (MAX_RANGE_WIDTH / 2 - width/2 - 1) || x <= (-MAX_RANGE_WIDTH / 2 + width/2 + 1))
		return true;
	if (y >= (MAX_RANGE_HEIGHT / 2 - width/2 - 1) || y <= (-MAX_RANGE_HEIGHT / 2 + width/2 +1))
		return true;
	return false;
}