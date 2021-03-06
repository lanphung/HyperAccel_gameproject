#include "Particle.h"
#include "ParticleSystem.h"
#include "define.h"
#include "Game.h"


Particle::Particle() :life(0) { }

void Particle::Init(fPoint pos, float startSpeed, float endSpeed, float angle, double rotSpeed, float startSize, float endSize, uint life, SPRITE_RECT textureRect, GL_COLOR startColor, GL_COLOR endColor, OPENGL_BLENDMODE blendMode, bool vortexSensitive)
{
	pState.pLive.pos = pos;
	pState.pLive.startVel.x = startSpeed * cos(DEG_2_RAD(angle));
	pState.pLive.startVel.y = -startSpeed * sin(DEG_2_RAD(angle));
	pState.pLive.endVel.x = endSpeed * cos(DEG_2_RAD(angle));
	pState.pLive.endVel.y = -endSpeed * sin(DEG_2_RAD(angle));
	pState.pLive.startRotSpeed = rotSpeed;
	pState.pLive.currentRotSpeed = rotSpeed;

	// Life properties
	this->life = pState.pLive.startLife = life;
	pState.pLive.currentSize = pState.pLive.startSize = startSize;
	pState.pLive.endSize = endSize;
	pState.pLive.t = 0.0f;

	// Color properties
	pState.pLive.startColor = startColor;
	pState.pLive.endColor = endColor;
	pState.pLive.blendMode = blendMode;
	pState.pLive.pRect = pState.pLive.rectSize = textureRect;

}

void Particle::MatUpdate()
{
	Matrix WorldMat, ViewMat, PerspectiveMat, ScaleMat, RotMat, RotXMat, RotYMat, RotZMat, TransMat;
	RotXMat.SetRotationX(0.0f); RotYMat.SetRotationY(0.0f); RotZMat.SetRotationZ(SceneManager::GetInstance()->GetObjwID(1)->Rot.z);
	RotMat = RotZMat * RotXMat * RotYMat;
	WVP = RotMat;
	/*ScaleMat.SetScale(pState.pLive.currentSize, pState.pLive.currentSize, 0.0f);
	TransMat.SetIdentity();
	WorldMat = ScaleMat * RotMat * TransMat;
	WVP = WorldMat * WVP::GetInstance()->getViewMat() *Game::GetInstance()->orthoMat;*/
}

void Particle::Update(float dt)
{

	// Age ratio is used to interpolate between particle properties
	pState.pLive.ageRatio = (float)life / (float)pState.pLive.startLife;

	// Particle size interpolation
	pState.pLive.currentSize = InterpolateBetweenRange(pState.pLive.startSize, pState.pLive.t, pState.pLive.endSize);

	// Particle velocity interpolation
	pState.pLive.currentVel.x = InterpolateBetweenRange(pState.pLive.startVel.x, pState.pLive.t, pState.pLive.endVel.x);
	pState.pLive.currentVel.y = InterpolateBetweenRange(pState.pLive.startVel.y, pState.pLive.t, pState.pLive.endVel.y);

	// Calculates new particle position.
	CalculateParticlePos(dt);

	//Matrix update
	MatUpdate();

	life--;
}

Vector2 Particle::GetPos()
{
	return Vector2(pState.pLive.pos.x, pState.pLive.pos.y);
}

GL_COLOR Particle::GetColor()
{
	GL_COLOR resColor;
	if (pState.pLive.startLife >= MIN_LIFE_TO_INTERPOLATE)
		resColor = RgbInterpolation(pState.pLive.startColor, pState.pLive.t, pState.pLive.endColor);
	return resColor;
}


bool Particle::Draw()
{
	bool ret = true;
	MatUpdate();
	// Calculating new rotation according to rotation speed
	pState.pLive.currentRotSpeed += pState.pLive.startRotSpeed;
	// Time step increment to interpolate colors
	pState.pLive.t += (1.0f / (float)pState.pLive.startLife);
	if (pState.pLive.t >= 1.0f)	pState.pLive.t = 0.0f;
	return ret;
}

bool Particle::IsAlive()
{
	return life > 0;
}

Particle* Particle::GetNext()
{
	return pState.next;
}

void Particle::SetNext(Particle* next)
{
	pState.next = next;
}

float Particle::InterpolateBetweenRange(float min, float timeStep, float max)
{
	return min + (max - min) * timeStep;
}

float Particle::GetSize()
{
	return pState.pLive.currentSize;
}

GL_COLOR Particle::RgbInterpolation(GL_COLOR startColor, float timeStep, GL_COLOR endColor)
{
	GL_COLOR finalColor;

	finalColor.r = startColor.r + (endColor.r - startColor.r) * timeStep;
	finalColor.g = startColor.g + (endColor.g - startColor.g) * timeStep;
	finalColor.b = startColor.b + (endColor.b - startColor.b) * timeStep;
	finalColor.a = startColor.a + (endColor.a - startColor.a) * timeStep;

	return finalColor;
}

void Particle::CalculateParticlePos(float dt)
{
	pState.pLive.pos.x += pState.pLive.currentVel.x * dt;
	pState.pLive.pos.y += pState.pLive.currentVel.y * dt;
}