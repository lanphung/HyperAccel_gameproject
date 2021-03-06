#include "MainCharacter.h"
#include "../Game.h"


MainCharacter::MainCharacter()
{
	m_type = 1;
	m_isRender = false;
	//shield
	shield = MAX_SHIELD;
	maxShield = MAX_SHIELD;
	timeRegenShield = 5.0f;
	regenShield = 0.1f;
	bom = NUM_BOOM;
	m_point = 0;
}

void MainCharacter::takeDame(float32 dame)
{
	timeRegenShield = 3.0f;
	if (shield <= 0)
	{
		timeRegenShield = 5.0f;
		m_hp -= dame;
		Die(m_body->GetWorld());
	}
	else
	{
		shield -= dame + dame * 0.1f;
	}
}
void MainCharacter::Die(b2World* world)
{

	if (m_hp <= 0 )
	{
		Game::GetInstance()->psystem->MainCharDeath();
		world->DestroyBody(m_body);
		m_isRender = false;
		m_body = NULL;
		printf("Game over");
	}
}
MainCharacter::~MainCharacter()
{
}



void MainCharacter::RenderBox2D(b2World *world) {
	m_hp = hp;
	m_isRender = true;
	b2PolygonShape shape;
	shape.SetAsBox(width, height);
	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 10000000.0f;
	fd.filter.categoryBits = k_mainCategory;
	fd.filter.maskBits = k_mainMask;
	b2BodyDef bd;
	bd.type = b2_kinematicBody;
	bd.position.Set(posX, posY);
	b2Body* body = world->CreateBody(&bd);
	m_body = body;
	m_body->CreateFixture(&fd);
	m_body->SetGravityScale(0);
}

void MainCharacter::hit(b2World *world)
{
	DetectEnemy mainCharacterHitEnemy;
	mainCharacterHitEnemy.m_circle.m_radius = height + 1.5f;
	mainCharacterHitEnemy.m_circle.m_p = m_body->GetPosition();
	mainCharacterHitEnemy.m_transform.SetIdentity();

	b2AABB aabb;
	mainCharacterHitEnemy.m_circle.ComputeAABB(&aabb, mainCharacterHitEnemy.m_transform, 0);

	world->QueryAABB(&mainCharacterHitEnemy, aabb);
	if (mainCharacterHitEnemy.target != NULL)
	{
		UserData *eData = (UserData*)mainCharacterHitEnemy.target->GetUserData();
		EnemyRectangle *enemyTarget = (EnemyRectangle *)eData->thisEnemy;
		if (enemyTarget == NULL || enemyTarget->m_body == NULL)	return;
		enemyTarget->takeDame(enemyTarget->m_hp);
		takeDame(enemyTarget->hp);
	}
	else
	{
		timeRegenShield -= 0.016f;
	}
	if (timeRegenShield <= 0.0f)
	{
		if (shield < 0.0f)
			shield = 0.0f;
		if (shield < maxShield)
			shield += regenShield;
	}
}

float MainCharacter::GetShield()
{
	return shield;
}

