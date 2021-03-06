#pragma once
#include "define.h"
#include "KeyManager.h"
#include "Game.h"
#include "PhysicsEngine.h"
#include "../Utilities/utilities.h"

class StateManager 
	 {
	public:
		StateManager() {};
		virtual ~StateManager() {};
		virtual StateManager* handleInput(Game& state, int m_key, Vector2 m_touch);
		virtual void _stateupdate(ESContext *esContext, float deltaTime) {}
		virtual void enter(Game& state, ESContext *esContext) {}
		virtual void _render(ESContext* esContext) {};
	private:

	};

	class GS_WELCOME : public StateManager
	{
	public:
		 GS_WELCOME  () {};
		 ~GS_WELCOME() {};
		void enter(Game& state, ESContext *esContext);
		StateManager* handleInput(Game& state, int m_key, Vector2 m_touch);
		 void _stateupdate(ESContext *esContext, float deltaTime);
		 void _render(ESContext *esContext);
	private:
	};

	class GS_GAMEPLAY : public StateManager
	{
	public:
		
		GS_GAMEPLAY() : time_play(0) {};
		 ~GS_GAMEPLAY() {};
		void enter(Game& state, ESContext *esContext);
		StateManager* handleInput(Game& state, int m_key, Vector2 m_touch);
		void _stateupdate(ESContext *esContext, float deltaTime);
		void _render(ESContext *esContext);
		int ISPause=0;
		int IsEnd = 0;
		float time_play;
		int m_deltatime = 0;
		
	};

	class GS_MAINMENU : public StateManager
	{
	public:
		GS_MAINMENU() {};
		 ~GS_MAINMENU() {};
		 void enter(Game& state, ESContext *esContext);
		StateManager* handleInput(Game& state, int m_key, Vector2 m_touch);
		 void _stateupdate(ESContext *esContext, float deltaTime);
		 void _render(ESContext *esContext);
	};

	class GS_OPTION : public StateManager
	{
	public:
		GS_OPTION() {};
		 ~GS_OPTION() {};
		 void enter(Game& state, ESContext *esContext);
		StateManager* handleInput(Game& state, int m_key, Vector2 m_touch);
		 void _stateupdate(ESContext *esContext, float deltaTime);
		 void _render(ESContext *esContext);
	};

	class GS_CREDITS : public StateManager
	{
	public:
		GS_CREDITS() {};
		 ~GS_CREDITS() {};
		 void enter(Game& state, ESContext *esContext);
		StateManager* handleInput(Game& state, int m_key, Vector2 m_touch);
		 void _stateupdate(ESContext *esContext, float deltaTime);
		 void _render(ESContext *esContext);
	};
/*
	class GS_INTER : public StateManager
	{
	public:
		GS_INTER() {};
		~GS_INTER() {};
		virtual void handleInput(Game& state, int m_key) {}
		virtual void _stateupdate(Game& state) {}
	};

	class GS_OPTION : public StateManager
	{
	public:
		GS_OPTION() {};
		~GS_OPTION() {};
		virtual void handleInput(Game& state, int m_key) {}
		virtual void _stateupdate(Game& state) {}
	};
	class GS_CREDITS : public StateManager
	{
	public:
		GS_CREDITS() {};
		~GS_CREDITS() {};
		virtual void handleInput(Game& state, int m_key) {}
		virtual void _stateupdate(Game& state) {}
	};

	class GS_WELCOME : public StateManager
	{
	public:
	GS_WELCOME() {};
	~GS_WELCOME() {};
	StateManager* handleInput(Game& state, int m_key)
	{
	if (m_key&KeyUpMove) return new GS_GAMEPLAY();
	}
	//virtual void _stateupdate(Game& state) {}
	};

	class GS_PAUSE : public StateManager
	{
	public:
		GS_PAUSE() {};
		~GS_PAUSE() {};
		virtual void handleInput(Game& state, int m_key) {}
		virtual void _stateupdate(Game& state) {}
	};*/

