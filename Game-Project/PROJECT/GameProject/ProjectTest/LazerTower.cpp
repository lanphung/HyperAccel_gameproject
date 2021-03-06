#include "LazerTower.h"
#include "../SceneManager.h"
#include "../PhysicsEngine.h"
LazerTower::LazerTower()
{

}

LazerTower::LazerTower(float32 positionX, float32 positionY)
{
	//tower range
	range = LASER_RANGE;

	damage = LASER_DAMAGE;

	//gun vertices
	b2Vec2 lazerTowerVertices[6];
	lazerTowerVertices[0].Set(0.4f, 1.8f);
	lazerTowerVertices[1].Set(0.4f, -1.8f);
	lazerTowerVertices[2].Set(-0.4f, -1.8f);
	lazerTowerVertices[3].Set(-0.4f, 1.8);
	lazerTowerVertices[4].Set(-0.1f, 2.0f);
	lazerTowerVertices[5].Set(0.1f, 2.0f);

	lazerTowerBodyDef.type = b2_kinematicBody;
	lazerTowerBodyDef.position.Set(positionX, positionY);
	lazerTowerBodyDef.angle = 0;

	//lt_polygon.SetAsBox(0.4f, 1.8f);
	lt_polygon.Set(lazerTowerVertices, 6);

	lazerTowerFixtureDef.shape = &lt_polygon;
	lazerTowerFixtureDef.density = 1;

	//enemyTarget = new EnemyL();
	enemyTarget = NULL;
	//enemyTarget->enemyBody = NULL;
	fireRate = 0.5f;
	reload = 0.0f;
	distanceToNearestEnemy = range * 2;

	missile = new Missile(positionX, positionY);

}

LazerTower::~LazerTower()
{
	delete missile;
}

void LazerTower::buildLazerTower(b2World* m_world)
{
	//create base
	b2BodyDef towerBodyDef;
	towerBodyDef.type = b2_staticBody;
	towerBodyDef.position.Set(0.0, 0.0);
	towerBodyDef.angle = 0;
	b2Body* towerBody = m_world->CreateBody(&towerBodyDef);

	b2PolygonShape polygon;
	polygon.SetAsBox(1.0f, 1.0f);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &polygon;
	boxFixtureDef.density = 1;

	lazerTowerBody = m_world->CreateBody(&lazerTowerBodyDef);
	lazerTowerBody->CreateFixture(&lazerTowerFixtureDef);

	missile->buildMissile(m_world);
}

void LazerTower::updateForLazer(b2World* m_world)
{
	DetectEnemy lazerTowerDetectEnemy;
	lazerTowerDetectEnemy.m_circle.m_radius = range;
	lazerTowerDetectEnemy.m_circle.m_p = lazerTowerBody->GetPosition();
	lazerTowerDetectEnemy.m_transform.SetIdentity();

	b2AABB aabb;
	lazerTowerDetectEnemy.m_circle.ComputeAABB(&aabb, lazerTowerDetectEnemy.m_transform, 0);

	m_world->QueryAABB(&lazerTowerDetectEnemy, aabb);

	if (hasOneEnemyInRange() == false)
	{
		detectEnemy(lazerTowerDetectEnemy.target);
	}

	if (enemyTarget != NULL)
		focusEnemy();

	//reload when tower has shot
	if (reload >= 0)
	{
		reload -= 0.1f;
	}
}

void LazerTower::updateForMissile(b2World *m_world)
{
	DetectEnemy missileDetectEnemy;
	missileDetectEnemy.m_circle.m_radius = range * 2;
	missileDetectEnemy.m_circle.m_p = lazerTowerBody->GetPosition();
	missileDetectEnemy.m_transform.SetIdentity();

	b2AABB aabb;
	missileDetectEnemy.m_circle.ComputeAABB(&aabb, missileDetectEnemy.m_transform, 0);

	m_world->QueryAABB(&missileDetectEnemy, aabb);

	if (isMissileLock() == false)
	{
		missile->detectEnemy(missileDetectEnemy.target);
	}

	if (missile->missileBody != NULL && missile->enemyTarget != NULL)
	{
		missile->focusEnemy();
		missile->launchMissile(missile->enemyTarget->m_body);
		missile->hit(m_world);
	}

	if (missile->missileBody == NULL)
	{
		missile->missileBodyDef.position.Set(lazerTowerBody->GetPosition().x, lazerTowerBody->GetPosition().y);
		missile->buildMissile(m_world);
	}

}

void LazerTower::detectEnemy(b2Body* target)
{
	//b2Vec2 distance;
	if (target != NULL)
	{
		//distance = target->GetPosition() - lazerTowerBody->GetPosition();
		//if (distance.Length() < distanceToNearestEnemy)
		{
			//UserData *eData = new UserData;
			UserData *eData;
			eData = (UserData*)target->GetUserData();
			enemyTarget = (EnemyRectangle *)eData->thisEnemy;
			if (enemyTarget == NULL)
				return;
			enemyTarget->m_body = target;
			//distanceToNearestEnemy = distance.Length()+1.0f;
		}
	}
}

void LazerTower::focusEnemy()
{
	if (enemyTarget->m_body == NULL)
		return;
	float32 bodyAngle = getLazerTowerAngle();
	b2Vec2 toTarget = enemyTarget->m_body->GetPosition() - getLazerTowerPosition();
	float32 rotationToTarget = atan2f(-toTarget.x, toTarget.y);
	float32 totalRotation = rotationToTarget - bodyAngle;
	////animation rotation
	float32 change = 20.0f * b2_pi / 180.0f;

	////avoid rotate more than 180 degrees
	while (totalRotation < -b2_pi) totalRotation += 2.0f * b2_pi;
	while (totalRotation > b2_pi) totalRotation -= 2.0f * b2_pi;

	float32 newAngle = bodyAngle + fmin(change, fmax(-change, totalRotation));
	lazerTowerBody->SetTransform(getLazerTowerPosition(), newAngle);
	if (reload <= 0)
	{
		Shoot();
		reload = 1.0f / fireRate;
	}

}

void LazerTower::Shoot()
{
	//printf("Launch missile - damage: %f\n", damage);
	enemyTarget->takeDame(damage);

}

float32 LazerTower::getLazerTowerAngle()
{
	return lazerTowerBody->GetAngle();
}

b2Vec2 LazerTower::getLazerTowerPosition()
{
	return lazerTowerBody->GetPosition();
}

float32 LazerTower::getRange()
{
	return range;
}

bool LazerTower::hasOneEnemyInRange()
{
	if (enemyTarget == NULL || enemyTarget->m_body == NULL)
		return false;
	b2Vec2 distance;
	distance = enemyTarget->m_body->GetPosition() - lazerTowerBody->GetPosition();
	if (distance.Length() > range)
	{
		enemyTarget = NULL;
		//distanceToNearestEnemy = range * 2;
		return false;
	}
	return true;
}

bool LazerTower::isMissileLock()
{
	if (missile->enemyTarget == NULL || missile->enemyTarget->m_body == NULL)
		return false;
	b2Vec2 distance;
	distance = missile->enemyTarget->m_body->GetPosition() - lazerTowerBody->GetPosition();
	if (distance.Length() > range * 3)
	{
		missile->enemyTarget = NULL;
		//distanceToNearestEnemy = range * 2;
		return false;
	}
	return true;
}