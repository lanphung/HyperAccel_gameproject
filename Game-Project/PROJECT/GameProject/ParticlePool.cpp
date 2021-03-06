#include "ParticlePool.h"
//#include <assert.h>
#include "SceneManager.h"

#include "Brofiler\Brofiler.h"


// This pool constructor sets our particles to available
ParticlePool::ParticlePool(Emitter* emitter)
{
	type = emitter->type;
	// Fill the pool according to poolSize needed for the emitter
	poolSize = emitter->GetPoolSize();
	particleArray = new Particle[poolSize];

	// The first particle is available
	firstAvailable = &particleArray[0];
	theShader = *ResourceManager::GetInstance()->ShadersList.at(5);
	theShader.Init(theShader.fileVS, theShader.fileFS);
	// Each particle points to the next one
	for (int i = 0; i < poolSize - 1; i++)
		particleArray[i].SetNext(&particleArray[i + 1]);

	// The last particle points to nullptr indicating the end of the vector
	particleArray[poolSize - 1].SetNext(nullptr);

	// Buffer creation
	BuffersCreation();
}

ParticlePool::~ParticlePool()
{
	delete[] particleArray;
	particleArray = nullptr;
}

void ParticlePool::Generate(fPoint pos, float startSpeed, float endSpeed, float angle, float rotSpeed, float startSize, float endSize, uint life, SPRITE_RECT textureRect, GL_COLOR startColor, GL_COLOR endColor, OPENGL_BLENDMODE blendMode, bool vortexSensitive)
{
	Particle* newParticle = firstAvailable;
	firstAvailable = newParticle->GetNext();
	newParticle->Init(pos, startSpeed, endSpeed, angle, rotSpeed, startSize, endSize, life, textureRect, startColor, endColor, blendMode, vortexSensitive);
}

void ParticlePool::BuffersCreation()
{
	// The VBO containing the positions and sizes of the particles
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STATIC_DRAW); 	// Initialize with empty (NULL) buffer : it will be updated later, each frame.

																								// The VBO containing the colors of the particles
	glGenBuffers(1, &particles_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STATIC_DRAW);    // Initialize with empty (NULL) buffer : it will be updated later, each frame.
}

void ParticlePool::ShaderUpdate(int ParticlesCount)
{
	glUseProgram(theShader.program);
	GLubyte ID;
	switch (type)
	{
	case EMITTER_TYPE_FIRE: ID = 12; break;
	case EMITTER_TYPE_WAVE_1: ID = 9; break;
	case EMITTER_TYPE_SHIELD: ID = 13; break;
	case EMITTER_TYPE_WAVE_2: ID = 14; break;
	case EMITTER_TYPE_MAIN_DEATH: ID = 15; break;
	case EMITTER_TYPE_BOSS_ENTRANCE: ID = 26; break;
	case EMITTER_TYPE_BOSS_DEATH: ID = 15; break;
	case EMITTER_TYPE_ROCKET_EXPLODED: ID = 34; break;
	case EMITTER_TYPE_LASER: ID = 14; break;
	case EMITTER_TYPE_BULLET: ID = 9; break;
	case EMITTER_TYPE_EXHAUST: ID = 12; break;
	case EMITTER_TYPE_MID_EXPLOSION: ID = 14; break;
	default: std::cout << "Emitter type not available :(" << std::endl; break;
	}
	Texture* theTexture = ResourceManager::GetInstance()->getTexture(ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, theTexture->TextureID);
	glUniform1i(theShader.iTextureLoc[0], 0);

	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	if (theShader.particlePosAttribute != -1)
	{
		glEnableVertexAttribArray(theShader.particlePosAttribute);
		glVertexAttribPointer(theShader.particlePosAttribute, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	if (theShader.particleColorAttribute != -1)
	{
		glEnableVertexAttribArray(theShader.particleColorAttribute);
		glVertexAttribPointer(theShader.particleColorAttribute, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ParticleState ParticlePool::Update(float dt)
{
	ParticleState retState = ParticleState::PARTICLE_STATE_NOT_DEF;
	int ParticlesCount = 0;
	for (int i = 0; i < poolSize; i++)
	{
		//Particle& p = particleArray[i];
		if (particleArray[i].IsAlive())
		{
			particleArray[i].Update(dt);
			g_particule_position_size_data[4 * ParticlesCount + 0] = particleArray[i].GetPos().x;
			g_particule_position_size_data[4 * ParticlesCount + 1] = particleArray[i].GetPos().y;
			g_particule_position_size_data[4 * ParticlesCount + 2] = 0.0f;
			g_particule_position_size_data[4 * ParticlesCount + 3] = particleArray[i].GetSize();
			GL_COLOR tmpColor = particleArray[i].GetColor();
			g_particule_color_data[4 * ParticlesCount + 0] = tmpColor.r / 255.0;
			g_particule_color_data[4 * ParticlesCount + 1] = tmpColor.g / 255.0;
			g_particule_color_data[4 * ParticlesCount + 2] = tmpColor.b / 255.0;
			g_particule_color_data[4 * ParticlesCount + 3] = tmpColor.a / 255.0;
			particleArray[i].Draw();
			retState = ParticleState::PARTICLE_ALIVE_DRAWN;
			ParticlesCount++;
		}
		else
		{
			particleArray[i].SetNext(firstAvailable);
			firstAvailable = &particleArray[i];
			retState = ParticleState::PARTICLE_DEAD;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_position_size_data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_color_data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	ShaderUpdate(ParticlesCount);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDrawArrays(GL_POINTS, 0, ParticlesCount);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return retState;
}