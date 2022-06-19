#pragma once
#include "p2Point.h"
#include "Sprite.h"
#define MIN_LIFE_TO_INTERPOLATE 1


class Particle 
{
private:

	/*  This is the only variable we care about no matter if
	the particle is alive or dead */
	uint life = 0;
	union ParticleInfo
	{
		struct ParticleState
		{
			uint startLife;
			fPoint pos;
			fPoint startVel;
			fPoint endVel;
			fPoint currentVel;
			float currentSize, startSize, endSize;
			float ageRatio;
			float angle;
			double startRotSpeed;
			double currentRotSpeed;
			SPRITE_RECT pRect;
			SPRITE_RECT rectSize;
			GL_COLOR startColor;
			GL_COLOR endColor;
			OPENGL_BLENDMODE blendMode;
			float t;
			ParticleState() {}
		} pLive;

		/* If the particle is dead, then the 'next' member comes
		into play and the struct it's not used. This pointer
		called 'next' holds a pointer to the next available
		particle after this one. */
		Particle* next;
		ParticleInfo() {}
	} pState;

public:

	Particle();
	void Init(fPoint pos, float startSpeed, float endSpeed, float angle, double rotSpeed, float startSize, float endSize, uint life, SPRITE_RECT textureRect, GL_COLOR startColor, GL_COLOR endColor, OPENGL_BLENDMODE blendMode, bool vortexSensitive);
	void Update(float dt);
	bool Draw();
	bool IsAlive();
	void MatUpdate();
	Matrix WVP;
	Vector2 GetPos();
	GL_COLOR GetColor();
	Particle* GetNext();
	void SetNext(Particle* next);
	// Color interpolation
	GL_COLOR RgbInterpolation(GL_COLOR startColor, float timeStep, GL_COLOR endColor);
	// Generic interpolating method
	float InterpolateBetweenRange(float min, float timeStep, float max);
	float GetSize();
	// Calculates particle position
	void CalculateParticlePos(float dt);
};

