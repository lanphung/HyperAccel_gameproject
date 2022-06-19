#pragma once
#include "Item.h"
class UpgradeBullet :
	public Item
{
public:
	UpgradeBullet();
	~UpgradeBullet();

	float radius;
	void RenderBox2D(b2World *world) ;
};

