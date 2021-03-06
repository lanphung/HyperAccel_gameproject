#include"NewEnemy.h"
#include "../Game.h"

NewEnemy::NewEnemy(float width, float height)
{
	render = 0;
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

NewEnemy::~NewEnemy()
{

}

void NewEnemy::RenderBox2D(b2World* world)
{
	srand(time(NULL));
	c = rand() % 4 + 1;
	if (c == 1)
	{
		x = RandomFloat(-SCREEN_WIDTH / 2 + width / 2, SCREEN_WIDTH / 2 - width / 2);
		y = RandomFloat(SCREEN_HEIGHT / 2 - 30, SCREEN_HEIGHT / 2 - height / 2);
		rectangleBD.position.Set(x, y);
	}
	if (c == 2)
	{
		x = RandomFloat(-SCREEN_WIDTH / 2 + width / 2, SCREEN_WIDTH / 2 - width / 2);
		y = RandomFloat(-SCREEN_HEIGHT / 2 + height / 2, -SCREEN_HEIGHT / 2 + 30);
		rectangleBD.position.Set(x, y);
	}
	if (c == 3)
	{
		x = RandomFloat(-SCREEN_WIDTH / 2 + width / 2, -SCREEN_WIDTH / 2 + 30);
		y = RandomFloat(-SCREEN_HEIGHT / 2 + 30, SCREEN_HEIGHT / 2 - 30);
		rectangleBD.position.Set(x, y);
	}
	if (c == 4)
	{
		x = RandomFloat(SCREEN_WIDTH / 2 - 30, SCREEN_WIDTH / 2 - width / 2);
		y = RandomFloat(-SCREEN_HEIGHT / 2 + 30, SCREEN_HEIGHT / 2 - 30);
		rectangleBD.position.Set(x, y);
	}
	b2Vec2 z = b2Vec2(RandomFloat(-5,5), RandomFloat(-5,5));
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

void NewEnemy::takeDame(float32 dame)
{
	m_hp -= dame;
	Die(m_body->GetWorld());
}

void NewEnemy::Die(b2World* world)
{
	if ((m_hp <= 0) || outOfRange())
	{
		fPoint tmp = fPoint((10 * m_body->GetPosition().x) / SCREEN_CENTER_W, (10 * m_body->GetPosition().y) / SCREEN_CENTER_H);
		Game::GetInstance()->psystem->AddEmiter(tmp, EmitterType::EMITTER_TYPE_MID_EXPLOSION);
		if ((m_hp <= 0))
		{
			Box2DSceneManager* m = Box2DSceneManager::GetInstance();
			m->m_objectList.at(0)->m_point += POINT_NEWENEMY;
			//printf("diem:%d\n", m->m_objectList.at(0)->cout);
		}
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
		
	}
}

bool NewEnemy::outOfRange()
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

void NewEnemy::release()
{
	delete userData;
	userData = NULL;
}