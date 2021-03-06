#include "EnemyCircle.h"
#include "time.h"
#include "../Game.h"
#include "Box2DSceneManager.h"
EnemyCircle::EnemyCircle(float radius)
{
	render = 0;
	this->radius = radius;
	m_type = 2;
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

EnemyCircle::~EnemyCircle()
{
	//delete userData;
	//userData = NULL;
	//std::cout << "delete" << std::endl;
}

void EnemyCircle::release()
{
	delete userData;
	userData = NULL;
}

void EnemyCircle::takeDame(float32 dame)
{
	m_hp -= dame;
	Die(m_body->GetWorld());
}
void EnemyCircle::Die(b2World* world)
{
	if ((m_hp <= 0.0f ) || outOfRange())
	{
		if (m_hp <= 0)
		{
			fPoint tmp = fPoint((10 * m_body->GetPosition().x) / SCREEN_CENTER_W, (10 * m_body->GetPosition().y) / SCREEN_CENTER_H);
			Game::GetInstance()->psystem->AddEmiter(tmp, EmitterType::EMITTER_TYPE_WAVE_2);
			Box2DSceneManager* m = Box2DSceneManager::GetInstance();
			m->m_objectList.at(0)->m_point += POINT_ENEMYCIRCLE;
		}		
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
	}
}
void EnemyCircle::RenderBox2D(b2World *world)
{
	

	srand(time(NULL));
	c = rand() % 4 + 1;
	if (c == 1)
	{
		x = RandomFloat(-SCREEN_WIDTH / 2 + radius , SCREEN_WIDTH / 2 - radius);
		y = RandomFloat(SCREEN_HEIGHT / 2 - 30, SCREEN_HEIGHT / 2 - radius-5);
		circleBD.position.Set(x, y);
	}
	if (c == 2)
	{
		x = RandomFloat(-SCREEN_WIDTH / 2 + radius, SCREEN_WIDTH / 2 - radius);
		y = RandomFloat(-SCREEN_HEIGHT / 2 + radius, -SCREEN_HEIGHT / 2 + 30);
		circleBD.position.Set(x,y );
	}
	if (c == 3)
	{
		x = RandomFloat(-SCREEN_WIDTH / 2 + radius, -SCREEN_WIDTH / 2 + 30);
		y = RandomFloat(-SCREEN_HEIGHT / 2 + 30, SCREEN_HEIGHT / 2 - 30);
		circleBD.position.Set(x,y);
	}
	if (c == 4)
	{
		x = RandomFloat(SCREEN_WIDTH / 2 - 30, SCREEN_WIDTH / 2 - radius);
		y = RandomFloat(-SCREEN_HEIGHT / 2 + 30, SCREEN_HEIGHT / 2 - 30);
		circleBD.position.Set(x, y);
	}
	Box2DSceneManager *m = Box2DSceneManager::GetInstance();
	float x1 = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body->GetPosition().x; 
	float y1 = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body->GetPosition().y;
	b2Vec2 z = b2Vec2(x1-x, y1-y);
	z.Normalize();
	z.x *= speed;
	z.y *= speed;

	circleBD.linearVelocity = b2Vec2(z);
	m_hp = hp;
	
	m_isRender = true;
	m_body = world->CreateBody(&circleBD);

	m_body->CreateFixture(&circleFD);
	
	m_body->SetUserData(userData);
}

void EnemyCircle::hit(b2World *world)
{

}

bool EnemyCircle::outOfRange()
{
	float32 x = 50, y = 50;
	if (m_body == NULL)
		return true;
	x = m_body->GetPosition().x;
	y = m_body->GetPosition().y;
	if (x >= (MAX_RANGE_WIDTH / 2 -radius-1) || x <= (-MAX_RANGE_WIDTH / 2 +radius + 1))
		return true;
	if (y >= (MAX_RANGE_HEIGHT / 2 - radius - 1) || y <= (-MAX_RANGE_HEIGHT / 2 + radius + 1))
		return true;
	return false;
}
