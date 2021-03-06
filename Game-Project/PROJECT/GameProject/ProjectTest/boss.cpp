#include "boss.h"
#include "../Game.h"

boss::boss(float width, float height)
{
	m_isRender = false;
	this->width = width;
	this->height = height;
	renderboss = false;
	rectangle.SetAsBox(this->width / 2, this->height / 2);

	rectangleBD.type = b2_dynamicBody;

	rectangleFD.shape = &rectangle;
	rectangleFD.density = 100.0f;
	rectangleFD.filter.categoryBits = k_enemyCategory;
	rectangleFD.filter.maskBits = k_enemyMask;
	userData = new UserData;
	userData->thisEnemy = this;
	
}

boss::~boss()
{
}

void boss::RenderBox2D(b2World* world)
{
	int x = -26;
	int y = 30;
	rectangleBD.position.Set(-26, 30);
	m_hp = hp;
	m_isRender = true;
	m_body = world->CreateBody(&rectangleBD);
	m_body->CreateFixture(&rectangleFD);

	m_body->SetUserData(userData);
	m_body->SetLinearVelocity(b2Vec2(0.0, -0.2));
	fPoint tmp = fPoint((10 * m_body->GetPosition().x) / SCREEN_CENTER_W, (10 * m_body->GetPosition().y) / SCREEN_CENTER_H);
	Game::GetInstance()->psystem->AddEmiter(tmp, EmitterType::EMITTER_TYPE_BOSS_ENTRANCE);
}

void boss::release()
{
	delete userData;
	userData = NULL;
}

void boss::takeDame(float32 dame)
{
	m_hp -= dame;
	Die(m_body->GetWorld());
}

void boss::Die(b2World* world)
{
	if (m_hp <= 0.0f)
	{
		PhysicsEngine::GetInstance()->phase++;
		m_hp += 500;
		Game::GetInstance()->psystem->AddEmiter(fPoint(SceneManager::GetInstance()->GetObjwID(12)->Pos.x / SCREEN_CENTER_W, SceneManager::GetInstance()->GetObjwID(12)->Pos.y / SCREEN_CENTER_H), EmitterType::EMITTER_TYPE_BOSS_DEATH);
		Box2DSceneManager* m = Box2DSceneManager::GetInstance();
		m->m_objectList.at(0)->m_point += POINT_BOSS;
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
		//printf("Boss defeated");
	}
}

void boss::hit(b2World *world)
{

}