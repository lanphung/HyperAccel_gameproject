#include "stdafx.h"
#include "Game.h"
#include "StateManager.h"
#include "pugixml-1.9/src/pugixml.hpp"

Game * Game::ms_pInstance = NULL;

void Game::Init(ESContext *esContext)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ResourceManager::CreateInstance();
	SceneManager::CreateInstance();
	KeyManager::CreateInstance();
	TouchManager::CreateInstance();
	TextRender::CreateInstance();
	ResourceManager::GetInstance()->ResourceLoading();
	SceneManager::GetInstance()->SceneLoading();
	SceneManager::GetInstance()->Init();
	PhysicsEngine::CreateInstance();
	PhysicsEngine::GetInstance()->Init();
	SoundEngine::CreateInstance();
	SoundEngine::GetInstance()->Init("../Resources/Managers/AudioSpec.txt");
	TextRender::GetIntance()->InitShader("../Resources/Shaders/textVS.vs", "../Resources/Shaders/textFS.fs");
	WVP::CreateInstance();
	WVP::GetInstance()->createViewMat();
	SoundEngine::CreateInstance();
	orthoMat.SetOrtho(-SCREEN_CENTER_W, SCREEN_CENTER_W, SCREEN_CENTER_H, -SCREEN_CENTER_H, -1, 1);
	///////////////////////////////////////////////
	Game::GetInstance()->psystem = new ParticleSystem();
	psystem->Awake();
	Game::GetInstance()->psystem->AddEmiter(fPoint(2, 2), EmitterType::EMITTER_TYPE_LASER);
	Game::GetInstance()->psystem->AddEmiter(fPoint(2, 2), EmitterType::EMITTER_TYPE_EXHAUST);
	Game::GetInstance()->psystem->AddEmiter(fPoint(0, 0), EmitterType::EMITTER_TYPE_SHIELD);
	Game::GetInstance()->psystem->AddEmiter(fPoint(0, 0), EmitterType::EMITTER_TYPE_FIRE);
	//////////////////////////////////////////////
	TextRender::GetIntance()->SetFont("../Resources/Fonts/SaucerBB.ttf");
	state_ = new GS_WELCOME;
	state_->enter(*this, esContext);
}

void Game::_enter(ESContext *esContext)
{
	
	state_->enter(*this, esContext);
}

void Game::handleInput(int key, ESContext *esContext, Vector2 m_touch)
{
	
	StateManager* state = state_->handleInput(*this, key, m_touch); // create a state object when we transition to it (in case there are more than 2 state machine)
	if (state != NULL)
	{
		delete state_;
		state_ = state;
	}
	state_->enter(*this, esContext);
}

void Game::_stateupdate(ESContext *esContext, float deltaTime)
{
	

	state_->_stateupdate(esContext, deltaTime);
}

void Game::Render(ESContext *esContext)
{
	state_->_render(esContext);
}

pugi::xml_node Game::LoadEmitters(pugi::xml_document& psystem_file) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = psystem_file.load_file("../Resources/psystem_config.xml");

	if (result == NULL)
		LOG("Could not load xml file config.xml. Pugi error: %s", result.description());
	else
		ret = psystem_file.child("emitters");
	return ret;
}

