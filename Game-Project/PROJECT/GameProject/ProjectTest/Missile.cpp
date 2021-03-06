#include "Missile.h"
#include "../Game.h"
Missile::Missile()
{

}

Missile::Missile(float32 positionX, float32 positionY)
{
	missileBodyDef.position.Set(positionX, positionY);
	missileBodyDef.angle = 0;
	missileBodyDef.type = b2_kinematicBody;

	missileShape.SetAsBox(0.5f, 1.0f);

	missileFixtureDef.shape = &missileShape;
	missileFixtureDef.density = 1.0f;

	enemyTarget = NULL;


	m_isRender = true;
	//dame missile
	dame = 50.0f;
}

Missile::~Missile()
{

}

void Missile::launchMissile(b2Body *target)
{
	b2Vec2 dir(1.0f, 1.0f);
	if (target != NULL)
	{
		dir = target->GetPosition() - missileBody->GetPosition();
		dir.Normalize();
	}
	else
	{
		dir = missileBody->GetPosition();
		dir.Normalize();
	}
	dir.x /= 4;
	dir.y /= 4;
	missileBody->SetTransform(missileBody->GetPosition() + dir, missileBody->GetAngle());
}

//void Missile::update(b2World* m_world)
//{
//	DetectEnemy missileDetectEnemy;
//	missileDetectEnemy.m_circle.m_radius = 20.0f;
//	missileDetectEnemy.m_circle.m_p = missileBody->GetPosition();
//	missileDetectEnemy.m_transform.SetIdentity();
//
//	b2AABB aabb;
//	missileDetectEnemy.m_circle.ComputeAABB(&aabb, missileDetectEnemy.m_transform, 0);
//	m_world->QueryAABB(&missileDetectEnemy, aabb);
//
//	if (enemyTarget == NULL)
//		detectEnemy(missileDetectEnemy.target);
//
//	if (enemyTarget != NULL)
//		focusEnemy();
//
//}

void Missile::detectEnemy(b2Body* target)
{
	if (target != NULL)
	{
		{
			//UserData *eData = new UserData;
			UserData *eData;
			eData = (UserData*)target->GetUserData();
			enemyTarget = (EnemyRectangle *)eData->thisEnemy;
			if (enemyTarget == NULL)
				return;
			enemyTarget->m_body = target;
		}
	}
}

void Missile::focusEnemy()
{
	if (enemyTarget == NULL || enemyTarget->m_body == NULL)
		return;
	float32 bodyAngle = missileBody->GetAngle();
	b2Vec2 toTarget = enemyTarget->m_body->GetPosition() - missileBody->GetPosition();
	float32 rotationToTarget = atan2f(-toTarget.x, toTarget.y);
	float32 totalRotation = rotationToTarget - bodyAngle;
	////animation rotation
	float32 change = 20.0f * b2_pi / 180.0f;

	////avoid rotate more than 180 degrees
	while (totalRotation < -b2_pi) totalRotation += 2.0f * b2_pi;
	while (totalRotation > b2_pi) totalRotation -= 2.0f * b2_pi;

	float32 newAngle = bodyAngle + fmin(change, fmax(-change, totalRotation));
	toTarget.Normalize();
	toTarget *= 0.5f;
	missileBody->SetTransform(missileBody->GetPosition(), newAngle);
}

void Missile::hit(b2World* m_world)
{
	if (outOfRange())
	{
		bulletHit();
		return;
	}
	DetectEnemy missileHitEnemy;
	missileHitEnemy.m_circle.m_radius = 1.3f;
	missileHitEnemy.m_circle.m_p = m_body->GetPosition();
	missileHitEnemy.m_transform.SetIdentity();

	b2AABB aabb;
	missileHitEnemy.m_circle.ComputeAABB(&aabb, missileHitEnemy.m_transform, 0);

	m_world->QueryAABB(&missileHitEnemy, aabb);
	if (missileHitEnemy.target != NULL)
	{
		SoundEngine::GetInstance()->playSound("MISSILE");
		Game::GetInstance()->psystem->AddEmiter(fPoint(10 * m_body->GetPosition().x / SCREEN_CENTER_W, 10 * m_body->GetPosition().y / SCREEN_CENTER_H), EmitterType::EMITTER_TYPE_ROCKET_EXPLODED);
		UserData *eData;
		eData = (UserData*)missileHitEnemy.target->GetUserData();
		EnemyRectangle *enemyTarget = (EnemyRectangle *)eData->thisEnemy;
		enemyTarget->m_body = missileHitEnemy.target;
		if (enemyTarget == NULL || enemyTarget->m_body == NULL)
			return;
		enemyTarget->takeDame(dame);
		bulletHit();
	}
}

bool Missile::outOfRange()
{
	float32 x, y;
	m_body = missileBody;
	x = m_body->GetPosition().x;
	y = m_body->GetPosition().y;
	if (x > MAX_RANGE_WIDTH / 2 || x < -MAX_RANGE_WIDTH / 2)
		return true;
	if (y > MAX_RANGE_HEIGHT / 2 || y < -MAX_RANGE_HEIGHT / 2)
		return true;
	return false;
}

void Missile::buildMissile(b2World* m_world)
{
	missileBody = m_world->CreateBody(&missileBodyDef);
	missileBody->CreateFixture(&missileFixtureDef);
	missileBody->SetUserData(userData);
}

void Missile::bulletHit()
{
	missileBody->GetWorld()->DestroyBody(missileBody);
	missileBody = NULL;
	m_isRender = false;
}
