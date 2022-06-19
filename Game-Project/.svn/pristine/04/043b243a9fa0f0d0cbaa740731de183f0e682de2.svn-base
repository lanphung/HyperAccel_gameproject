#pragma once
#include "Box2D\Box2D.h"
#include "ObjectPhysic.h"
#include <iostream>

class DetectEnemy : public b2QueryCallback
{
public:

	enum
	{
		e_maxCount = 1
	};

	DetectEnemy()
	{
		m_count = 0;
	}

	/// Called for each fixture found in the query AABB.
	/// @return false to terminate the query.
	bool ReportFixture(b2Fixture* fixture) override
	{
		if (m_count == e_maxCount)
		{
			return false;
		}

		b2Body* body = fixture->GetBody();
		b2Shape* shape = fixture->GetShape();

		bool overlap = b2TestOverlap(shape, 0, &m_circle, 0, body->GetTransform(), m_transform);
		//EnemyData data;
//		e = new UserData;
		e =  (UserData*)body->GetUserData();
		//std::cout << body->GetUserData() << std::endl;
		if (overlap && body->GetType() == b2_dynamicBody)
		{
			if (e->name == "enemy")
			{
				target = body;
				++m_count;
			}			
		}
		else
			target = NULL;

		return true;
	}

	b2CircleShape m_circle;
	b2Transform m_transform;
	int32 m_count;
	b2Body* target;
	UserData *e;
};