#pragma once

#include "p2Point.h"
#include "Emitter.h"
#include "define.h"
#include "pugixml-1.9/src/pugixml.hpp"
#include <list>
#include <string>
#include "../Utilities/utilities.h"


class Emitter;


struct EmitterData
{
	fPoint angleRange = { 0.0f, 0.0f };
	float startSpeed = 0.0f, endSpeed = 0.0f;
	float startSize = 0.0f, endSize = 0.0f;
	unsigned int emitNumber = 0u;
	unsigned int emitVariance = 0u;
	unsigned int maxParticleLife = 0u;
	SPRITE_RECT textureRect = { 0, 0 };
	double lifetime = -1.0f;
	GL_COLOR startColor = { 0, 0, 0, 0 };
	GL_COLOR endColor = { 0, 0, 0, 0 };
	OPENGL_BLENDMODE blendMode = OPENGL_BLENDMODE::ADDITIVE;
	double rotSpeed = 0;
	// Randoms
	fPoint rotSpeedRand = { 0.0f, 0.0f };
	fPoint startSpeedRand = { 0.0f, 0.0f };
	fPoint endSpeedRand = { 0.0f, 0.0f };
	fPoint emitVarianceRand = { 0.0f, 0.0f };
	fPoint lifeRand = { 0.0f, 0.0f };
	fPoint startSizeRand = { 0.0f, 0.0f };
	fPoint endSizeRand = { 0.0f, 0.0f };
	EmitterType type;
	// Vortex
	bool vortexSensitive = false;
};

class ParticleSystem
{
public:
	std::vector<fPoint*> emittersToRender;
	std::list<Emitter*> emittersList;
	std::list<Emitter*> emittersToDestroy;
	std::string nameParticleAtlas;
	// Static array that stores all the data of emitters
	EmitterData vecEmitterData[MAX_NUM_EMITTERS_TYPE];
	ParticleSystem() {};

	// Destructor
	virtual ~ParticleSystem() {};

	// Main character death effect
	void MainCharDeath();

	// Called when before render is available
	bool Awake();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Emitter methods
	Emitter* AddEmiter(fPoint pos, EmitterType type);
	bool RemoveEmitter(Emitter* emitter);
	bool RemoveAllEmitters();
	void LoadEmitterData(pugi::xml_node& config, EmitterType type);

};
