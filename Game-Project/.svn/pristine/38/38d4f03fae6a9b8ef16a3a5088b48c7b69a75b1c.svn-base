#pragma once

#include "Particle.h"
#include "Emitter.h"
#include "p2Point.h"
#include <vector>

class Emitter;

enum ParticleState
{
	PARTICLE_STATE_NOT_DEF,
	PARTICLE_ALIVE_DRAWN,
	PARTICLE_ALIVE_NOT_DRAWN,
	PARTICLE_DEAD
};

class ParticlePool
{
private:

	int poolSize = 0;
	Particle* firstAvailable;
	Particle* particleArray = nullptr;
	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
	GLfloat g_particule_position_size_data[4 * MaxParticles];
	GLfloat g_particule_color_data[4 * MaxParticles];
	Shaders theShader;
	EmitterType type;
public:

	ParticlePool(Emitter* emitter);
	virtual ~ParticlePool();
	// Generates a new particle each time it's called
	void Generate(fPoint pos, float startSpeed, float endSpeed, float angle, float rotSpeed, float startSize, float endSize, uint life, SPRITE_RECT textureRect, GL_COLOR startColor, GL_COLOR endColor, OPENGL_BLENDMODE blendMode, bool vortexSensitive);
	// Creating VBOs
	void BuffersCreation();
	void ShaderUpdate(int ParticlesCount);
	// Update (move and draw) particles in the pool.
	// IMPORTANT NOTE: This method returns:
	//		- PARTICLE_ALIVE_DRAWN: if the particle is still alive and has been drawn succesfully
	//      - PARTICLE_ALIVE_NOT_DRAWN:  if the particle is alive and has NOT been drawn succesfully
	//		- PARTICLE_DEAD: if is particle is no longer alive
	ParticleState Update(float dt);
};

