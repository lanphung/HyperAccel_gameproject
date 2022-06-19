#include "UpgradeBullet.h"



UpgradeBullet::UpgradeBullet()
{
	m_body = NULL;
	m_isRender = false;
	userData = new UserData;
	m_body->SetUserData(userData);
}


UpgradeBullet::~UpgradeBullet()
{
	delete userData;
	userData = NULL;
}

void UpgradeBullet::RenderBox2D(b2World *world) {
	if (m_body != NULL)
	{
		world->DestroyBody(m_body);
		m_body = NULL;
	}
	/*m_isRender = true;
	b2CircleShape shape;
	shape.m_radius = radius;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 0.00001f;
	fd.filter.categoryBits = k_itemCategory;
	fd.filter.maskBits = k_itemMask;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.bullet = true;
	bd.position.Set(posX, posY);
	b2Body* body = world->CreateBody(&bd);
	m_body = body;
	m_body->CreateFixture(&fd);
	m_body->SetGravityScale(0);
	body->SetLinearVelocity(b2Vec2(0.0f, -10.0f));*/
}


