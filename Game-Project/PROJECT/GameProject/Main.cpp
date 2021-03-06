#include <stddef.h>
#include "stdafx.h"
#include "conio.h"
#include "define.h"
#include "Globals.h"
#include "Game.h"
#include "log.h"
#include "StateManager.h"

#include <string>
#include "TextRender.h"
#include "PhysicsEngine.h"
#include "Box2D\Box2D.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

void Init(ESContext *esContext)
{
	Game::CreateInstance();
	Game::GetInstance()->Init(esContext);
	Game::GetInstance()->_enter(esContext);

}

void Update(ESContext *esContext, float deltaTime)
{
	Game::GetInstance()->dt = deltaTime;
	Game::GetInstance()->currentTime += deltaTime;
	Game::GetInstance()->_stateupdate(esContext, deltaTime);
}

void Draw(ESContext *esContext)
{
	Game::GetInstance()->Render(esContext);
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	KeyManager::GetInstance()->Key(key, bIsPressed);
	Game::GetInstance()->handleInput(KeyManager::GetInstance()->GetKey(), esContext, Vector2(1000.0f, 1000.0f));

}

void TouchActionUp(ESContext *esContext, int x, int y)
{
	TouchManager::GetInstance()->isTouchedDown = false;
}

void TouchActionMove(ESContext *esContext, int x, int y)
{
	TouchManager::GetInstance()->SetPosTouch(x, y);
	TouchManager::GetInstance()->isTouchedDown = true;
	Game::GetInstance()->handleInput(KeyManager::GetInstance()->GetKey(), esContext, Vector2(x, y));
}

void TouchActionDown(ESContext *esContext, int x, int y)
{
	TouchManager::GetInstance()->SetPosTouch(x, y);
	TouchManager::GetInstance()->isTouchedDown = true;
	Game::GetInstance()->handleInput(KeyManager::GetInstance()->GetKey(), esContext, Vector2(x, y));
	TouchManager::GetInstance()->MainCharDirUpdate(x, y);
}
void CleanUp()
{
	Game::GetInstance()->CleanUp();

}

int _tmain(int argc, _TCHAR* argv[])
{

	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "Hyper Accel", SCREEN_W, SCREEN_H, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
	Init(&esContext);
	esRegisterKeyFunc(&esContext, Key);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterDrawFunc(&esContext, Draw);
	esMainLoop(&esContext);
	CleanUp();
	MemoryDump();
	printf("Press any key...\n");
	_getch();
	return 0;
}

