
//#include "p2Log.h"
#include "ParticleSystem.h"
#include "Game.h"

bool ParticleSystem::Awake()
{
	bool ret = true;
	pugi::xml_document	psystem_config;
	pugi::xml_node* node = &Game::GetInstance()->LoadEmitters(psystem_config);
	nameParticleAtlas = node->child("particleAtlas").attribute("name").as_string();

	for (pugi::xml_node emitters = node->child("particleAtlas").child("emitter"); emitters && ret; emitters = emitters.next_sibling("emitter"))
	{
		std::string emitterType = emitters.attribute("type").as_string();
		if (emitterType.compare("fire") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_FIRE);
		else if (emitterType.compare("wave_1") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_WAVE_1);
		else if (emitterType.compare("shield") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_SHIELD); 
		else if (emitterType.compare("wave_2") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_WAVE_2);
		else if (emitterType.compare("main_death") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_MAIN_DEATH);
		else if (emitterType.compare("boss_entrance") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_BOSS_ENTRANCE);
		else if (emitterType.compare("boss_death") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_BOSS_DEATH);
		else if (emitterType.compare("rocket_exploded") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_ROCKET_EXPLODED);
		else if (emitterType.compare("laser") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_LASER);
		else if (emitterType.compare("bullet") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_BULLET);
		else if (emitterType.compare("rocket_exhaust") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_EXHAUST);
		else if (emitterType.compare("mid_explosion") == 0)
			LoadEmitterData(emitters, EmitterType::EMITTER_TYPE_MID_EXPLOSION);
	}
	return ret;
}



bool ParticleSystem::Update(float dt)
{
	std::list<Emitter*>::const_iterator it;

	for (it = emittersList.begin(); it != emittersList.end(); ++it)
	{
		if (*it != nullptr)
			(*it)->Update(dt);
	}

	return true;
}

bool ParticleSystem::PostUpdate()
{
	bool ret = true;

	if (!emittersToDestroy.empty())
	{
		std::list<Emitter*>::const_iterator it;

		for (it = emittersToDestroy.begin(); it != emittersToDestroy.end(); ++it)
		{
			emittersList.remove(*it);
			delete (*it);
		}

		emittersToDestroy.clear();
	}

	ret = emittersToDestroy.size() <= 0;

	if (ret)
	{
		std::list<Emitter*>::iterator it;

		for (it = emittersList.begin(); it != emittersList.end() && ret; ++it)
		
			ret = (*it)->Draw(Game::GetInstance()->dt);
	}

	return ret;
}

void ParticleSystem::MainCharDeath()
{
	Game::GetInstance()->psystem->AddEmiter(fPoint(SceneManager::GetInstance()->GetObjwID(1)->Pos.x / SCREEN_CENTER_W, SceneManager::GetInstance()->GetObjwID(1)->Pos.y / SCREEN_CENTER_H), EmitterType::EMITTER_TYPE_MAIN_DEATH);
	std::list<Emitter*>::const_iterator it;

	for (it = emittersList.begin(); it != emittersList.end(); ++it)
	{
		if ((*it)->type == EMITTER_TYPE_FIRE || (*it)->type == EMITTER_TYPE_SHIELD)
		{
			(*it)->lifetime = 300;
		}
	}
}

bool ParticleSystem::CleanUp()
{
	LOG("Freeing emitters from the system.");

	std::list<Emitter*>::const_iterator it;

	for (it = emittersList.begin(); it != emittersList.end(); ++it)
	{
		if (*it != nullptr)
			delete *it;
	}

	emittersList.clear();


	return true;
}

Emitter* ParticleSystem::AddEmiter(fPoint pos, EmitterType type)
{
	Emitter* tmp_emitter = new Emitter(pos, vecEmitterData[type]);

	emittersList.push_back(tmp_emitter);

	return tmp_emitter;
}

bool ParticleSystem::RemoveEmitter(Emitter* emitter)
{
	bool ret = false;

	if (emitter != nullptr && !emittersList.empty())
	{
		emittersToDestroy.push_back(emitter);
		ret = true;
	}

	return ret;
}

bool ParticleSystem::RemoveAllEmitters()
{
	bool ret = false;
	if (!emittersList.empty())
	{
		std::list<Emitter*>::const_iterator it;
		for (it = emittersList.begin(); it != emittersList.end(); ++it)
		{
			if (*it != nullptr)
				emittersToDestroy.push_back(*it);
			ret = true;
		}
	}
	return ret;
}


void ParticleSystem::LoadEmitterData(pugi::xml_node & emitter, EmitterType type)
{
	EmitterData tmp;

	// Angle range
	tmp.angleRange.x = emitter.child("angleRange").attribute("min").as_float();
	tmp.angleRange.y = emitter.child("angleRange").attribute("max").as_float();

	// Particle speeds
	tmp.rotSpeed = emitter.child("rotSpeed").attribute("value").as_double();
	tmp.startSpeed = emitter.child("startSpeed").attribute("value").as_float();
	tmp.endSpeed = emitter.child("endSpeed").attribute("value").as_float();

	// Random controls
	tmp.startSpeedRand.x = emitter.child("startSpeed").attribute("randMin").as_float();
	tmp.startSpeedRand.y = emitter.child("startSpeed").attribute("randMax").as_float();

	tmp.endSpeedRand.x = emitter.child("endSpeed").attribute("randMin").as_float();
	tmp.endSpeedRand.y = emitter.child("endSpeed").attribute("randMax").as_float();

	tmp.rotSpeedRand.x = emitter.child("rotSpeed").attribute("randMin").as_float();
	tmp.rotSpeedRand.y = emitter.child("rotSpeed").attribute("randMax").as_float();

	tmp.emitVarianceRand.x = emitter.child("emitVariance").attribute("randMin").as_float();
	tmp.emitVarianceRand.y = emitter.child("emitVariance").attribute("randMax").as_float();

	tmp.lifeRand.x = emitter.child("maxParticleLife").attribute("randMin").as_float();
	tmp.lifeRand.y = emitter.child("maxParticleLife").attribute("randMax").as_float();

	tmp.startSizeRand.x = emitter.child("startSize").attribute("randMin").as_float();
	tmp.startSizeRand.y = emitter.child("startSize").attribute("randMax").as_float();

	tmp.endSizeRand.x = emitter.child("endSizeRand").attribute("randMin").as_float();
	tmp.endSizeRand.y = emitter.child("endSizeRand").attribute("randMax").as_float();

	// Particle size
	tmp.startSize = emitter.child("startSize").attribute("value").as_float();
	tmp.endSize = emitter.child("endSize").attribute("value").as_float();

	// Emission properties
	tmp.emitNumber = emitter.child("emitNumber").attribute("value").as_uint();
	tmp.emitVariance = emitter.child("emitVariance").attribute("value").as_uint();

	// Particle life
	tmp.maxParticleLife = emitter.child("maxParticleLife").attribute("value").as_uint();

	// Rect from particle atlas
	tmp.textureRect.x = emitter.child("textureRect").attribute("x").as_int();
	tmp.textureRect.y = emitter.child("textureRect").attribute("y").as_int();
	tmp.textureRect.w = emitter.child("textureRect").attribute("w").as_int();
	tmp.textureRect.h = emitter.child("textureRect").attribute("h").as_int();

	// Lifetime of emitter
	tmp.lifetime = emitter.child("lifetime").attribute("value").as_double();

	// Start color
	tmp.startColor.r = emitter.child("startColor").attribute("r").as_uint();
	tmp.startColor.g = emitter.child("startColor").attribute("g").as_uint();
	tmp.startColor.b = emitter.child("startColor").attribute("b").as_uint();
	tmp.startColor.a = emitter.child("startColor").attribute("a").as_uint();

	// End color
	tmp.endColor.r = emitter.child("endColor").attribute("r").as_uint();
	tmp.endColor.g = emitter.child("endColor").attribute("g").as_uint();
	tmp.endColor.b = emitter.child("endColor").attribute("b").as_uint();
	tmp.endColor.a = emitter.child("endColor").attribute("a").as_uint();

	// Blend mode
	std::string blendModeString = emitter.child("blendMode").attribute("mode").as_string();

	if (blendModeString == "add")
		tmp.blendMode = OPENGL_BLENDMODE::ADDITIVE;

	// Vortex
	tmp.vortexSensitive = emitter.child("vortexSensitive").attribute("state").as_bool();
	tmp.type = type;
	vecEmitterData[type] = tmp;
}