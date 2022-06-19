#pragma once
#include "../Utilities/utilities.h" 

class Lights
{
public:
	Lights();
	~Lights();
	int LightsCount;
	float RADIUS;
	float SPEED;
	Vector3 Dir;
	Vector3 COLOR;
	Vector3 AmbientColor;
	float AmbientWeight;
	char TYPE[20];
	char MOVING[20];
};
