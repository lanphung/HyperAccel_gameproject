#include "BulletType1.h"
#include "../SceneManager.h"
#include "../SoundEngine.h"
#include "../Game.h"
BulletType1::BulletType1()
{
	m_body = NULL;
	m_type = 3;
	m_isRender = false;
	userData = new UserData;
	userData->name = "Bullet";
	userData->thisEnemy = this;
	
}


BulletType1::~BulletType1()
{
	//delete userData;
	//userData = NULL;
	//printf("deletebxcvbxcvbxcvb\n");
}

void BulletType1::release()
{
	delete userData;
	userData = NULL;
}

void BulletType1::RenderBox2D(b2World *world) 
{
	
	m_hp = hp;
	m_isRender = true;
	b2CircleShape shape;
	shape.m_radius = radius;
	bulletAngle = SceneManager::GetInstance()->GetObjwID(1)->Rot.z;
	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 0.00001f;
	fd.filter.categoryBits = k_bulletCategory;
	fd.filter.maskBits = k_bulletMask;

	b2BodyDef bd;
	bd.type = b2_kinematicBody;
	bd.bullet = true;

	if (Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body == NULL)
		return;
	float angle = Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetAngle();
	float x = Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().x;
	float y = Box2DSceneManager::GetInstance()->m_objectList.at(0)->m_body->GetPosition().y;
	
		bd.position.Set(5*cos(angle) + x,5*sin(angle) + y);
		b2Body* body = world->CreateBody(&bd);
		m_body = body;
		m_body->CreateFixture(&fd);
		m_body->SetGravityScale(0);
		
		
		{
			b2Vec2 x = b2Vec2(cos(angle), sin(angle));
			x.Normalize();
			dir = x;
			x.x *= 50;
			x.y *= 50;
			//body->SetLinearVelocity(x);
		}
		m_body->SetUserData(userData);
}


char* BulletType1::className()
{
	return "BulletType1";
}

void BulletType1::hit(b2World *world)
{
	m_body->SetTransform(m_body->GetPosition() + dir, m_body->GetAngle());
	if (outOfRange())
	{
		bulletHit();
		return;
	}
	DetectEnemy bulletHitEnemy;
	bulletHitEnemy.m_circle.m_radius = radius+2.0f;
	bulletHitEnemy.m_circle.m_p = m_body->GetPosition();
	bulletHitEnemy.m_transform.SetIdentity();

	b2AABB aabb;
	bulletHitEnemy.m_circle.ComputeAABB(&aabb, bulletHitEnemy.m_transform, 0);

	world->QueryAABB(&bulletHitEnemy, aabb);
	if (bulletHitEnemy.target != NULL)
	{

		Game::GetInstance()->psystem->AddEmiter(fPoint(10 * m_body->GetPosition().x / SCREEN_CENTER_W, 10 * m_body->GetPosition().y / SCREEN_CENTER_H), EmitterType::EMITTER_TYPE_BULLET);

		UserData *eData  = (UserData*)bulletHitEnemy.target->GetUserData();
		EnemyRectangle *enemyTarget = (EnemyRectangle *)eData->thisEnemy;
		enemyTarget->m_body = bulletHitEnemy.target;
		if (enemyTarget == NULL || enemyTarget->m_body == NULL)
			return;
		enemyTarget->takeDame(m_hp);
		bulletHit();
	}
}

bool BulletType1::outOfRange()
{
	float32 x, y;
	x = m_body->GetPosition().x;
	y = m_body->GetPosition().y;
	if (x > MAX_RANGE_WIDTH/2 || x < -MAX_RANGE_WIDTH/2)
		return true;
	if (y > MAX_RANGE_HEIGHT/2 || y < -MAX_RANGE_HEIGHT/2)
		return true;
	return false;
}

void BulletType1::bulletHit()
{
	m_body->GetWorld()->DestroyBody(m_body);
	m_body = NULL;
	m_isRender = false;
	//userData = NULL;
}

