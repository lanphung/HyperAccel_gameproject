#pragma once
#include "SceneManager.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "SoundEngine.h"
#include "TouchManager.h"
#include "TextRender.h"
#include "SoundEngine.h"
#include "define.h"
#include "WVP.h"
#include <iostream>
#include "p2Log.h"
#include "ParticleSystem.h"
#include "../Utilities/utilities.h"
#include "PhysicsEngine.h"
class StateManager;
class Game
{
protected:
	Game() : currentTime(0) {}
	virtual ~Game() {}
	Game(const Game &) {}
	Game& operator =(const Game &) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new Game;
	}
	static Game * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		RELEASE(ms_pInstance->state_);
		RELEASE(ms_pInstance->psystem);
		RELEASE(ms_pInstance);
	}
	void CleanUp()
	{

		psystem->CleanUp();
		SceneManager::GetInstance()->CleanUp();
		ResourceManager::GetInstance()->CleanUp();
		SoundEngine::GetInstance()->CleanUp();
		KeyManager::DestroyInstance();
		TouchManager::DestroyInstance();
		WVP::DestroyInstance();
		TextRender::DestroyIntance();
		PhysicsEngine::GetInstance()->release();
		PhysicsEngine::DestroyInstance();
		SoundEngine::DestroyInstance();
		DestroyInstance();
		
	}
	
		
	///////////////////////////////////
	void Init(ESContext *esContext);
	///////////////////////////////////
	void _enter(ESContext *esContext);
	///////////////////////////////////
	void handleInput(int key, ESContext *esContext, Vector2 m_touch);
	void _stateupdate(ESContext *esContext, float deltaTime);
	void Render(ESContext* esContext);
	///////////ParticleStuff///////////
	pugi::xml_node /*Game::*/LoadEmitters(pugi::xml_document& psystem_file) const;
	///////////////////////////////////
	float currentTime;
	Matrix orthoMat;
	StateManager* state_;
	ParticleSystem*	 psystem = nullptr;
	float dt = 0.0f;
protected:
	static Game * ms_pInstance;
};
