#pragma once
#include "ObjectPhysic.h"
#include "define.h"
#include <vector>

using namespace std;

class Enemy : public ObjectPhysic
{
public:
	Enemy();
	~Enemy();

	virtual void RenderBox2D(b2World* world) {};
	virtual void takeDame(float32 dame) {};
	virtual bool outOfRange() { return 0; };
};
