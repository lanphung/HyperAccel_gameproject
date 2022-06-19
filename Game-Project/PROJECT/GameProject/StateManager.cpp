#include "stdafx.h"
#include "SoundEngine.h"
#include "StateManager.h"
StateManager* StateManager::handleInput(Game& state, int m_key, Vector2 m_touch)
{
	return NULL;
}

///////////////////////////GS_WELCOME/////////////////////////////


void GS_WELCOME::enter(Game& state, ESContext *esContext)
{
	SoundEngine::GetInstance()->playMusic("WELCOME_BG");
}

void GS_WELCOME::_stateupdate(ESContext * esContext, float deltaTime)
{

}

void GS_WELCOME::_render(ESContext * esContext)
{
	SceneManager::GetInstance()->GetObjwID(3)->Draw();
	SceneManager::GetInstance()->GetObjwID(4)->Draw();

	TextRender::GetIntance()->RenderString("CLICK TO ENTER", Vector4(0.772, 0.631, 0.149, 1.0f), -100.0f, -100.0f, 1.0f, 1.0f);
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

StateManager* GS_WELCOME::handleInput(Game& state, int m_key, Vector2 m_touch)
{

		TextRender::GetIntance()->SetFont("../Resources/Fonts/SaucerBB.ttf");
		return  new GS_MAINMENU();
}

///////////////////////////GS_GAMEPLAY/////////////////////////////

void GS_GAMEPLAY::enter(Game& state, ESContext *esContext)
{
	if (PhysicsEngine::GetInstance()->phase%3 == 0) SoundEngine::GetInstance()->playMusic("LVL_01");
	else if (PhysicsEngine::GetInstance()->phase%3 == 1) SoundEngine::GetInstance()->playMusic("LVL_02");
	else if (PhysicsEngine::GetInstance()->phase%3 == 2) SoundEngine::GetInstance()->playMusic("LVL_03");
}

StateManager* GS_GAMEPLAY::handleInput(Game& state, int m_key, Vector2 m_touch)
{

	int k = SceneManager::GetInstance()->GetButtonID(5)->InButton(m_touch);
	if (k == 1)
	{
		ISPause = 1;
	}
	if (TouchManager::GetInstance()->isTouchedDown)
	{
		Vector2 touch = TouchManager::GetInstance()->m_touch;
		float angle = TouchManager::GetInstance()->AngleCalc(Vector2(SceneManager::GetInstance()->GetObjwID(1)->Pos.x, SceneManager::GetInstance()->GetObjwID(1)->Pos.y), touch);
		PhysicsEngine::GetInstance()->TouchDown(angle);
	}
	else
	{
		PhysicsEngine::GetInstance()->TouchUp();
	}
	if (ISPause == 1)
	{
		int h = SceneManager::GetInstance()->GetButtonID(7)->InButton(m_touch);
		if (h == 1)
		{
			SoundEngine::GetInstance()->VolumeMusicDow();
		}
		h = SceneManager::GetInstance()->GetButtonID(8)->InButton(m_touch);
		if (h == 1)
		{
			SoundEngine::GetInstance()->VolumeMusicUp();
		}
		h = SceneManager::GetInstance()->GetButtonID(9)->InButton(m_touch);
		if (h == 1)
		{
			SoundEngine::GetInstance()->VolumeSoundDow();
		}
		h = SceneManager::GetInstance()->GetButtonID(10)->InButton(m_touch);
		if (h == 1)
		{
			SoundEngine::GetInstance()->VolumeSoundUp();
		}
		int k = SceneManager::GetInstance()->GetButtonID(6)->InButton(m_touch);
		if (k == 1)
		{
			ISPause = 0;
		}
		k = SceneManager::GetInstance()->GetButtonID(4)->InButton(m_touch);
		if (k == 1)
		{
			ISPause = 0;
			Game::GetInstance()->psystem->RemoveAllEmitters();
			Game::GetInstance()->psystem->AddEmiter(fPoint(2, 2), EmitterType::EMITTER_TYPE_LASER);
			Game::GetInstance()->psystem->AddEmiter(fPoint(2, 2), EmitterType::EMITTER_TYPE_EXHAUST);
			Game::GetInstance()->psystem->AddEmiter(fPoint(0, 0), EmitterType::EMITTER_TYPE_SHIELD);
			Game::GetInstance()->psystem->AddEmiter(fPoint(0, 0), EmitterType::EMITTER_TYPE_FIRE);
			PhysicsEngine::GetInstance()->release();
			PhysicsEngine::DestroyInstance();
			PhysicsEngine::CreateInstance();
			PhysicsEngine::GetInstance()->Init();

			time_play = 0;
		}
		k = SceneManager::GetInstance()->GetButtonID(11)->InButton(m_touch);
		if (k == 1)
		{
			TextRender::GetIntance()->SetFont("../Resources/Fonts/SaucerBB.ttf");
			SoundEngine::GetInstance()->playMusic("WELCOME_BG");
			return new GS_MAINMENU();
		}
	}
	if (IsEnd == 1)
	{
		k = SceneManager::GetInstance()->CButtons.at(4)->InButton(m_touch);
		if (k == 1)
		{
			IsEnd = 0;
			Game::GetInstance()->psystem->RemoveAllEmitters();
			Game::GetInstance()->psystem->AddEmiter(fPoint(2, 2), EmitterType::EMITTER_TYPE_LASER);
			Game::GetInstance()->psystem->AddEmiter(fPoint(2, 2), EmitterType::EMITTER_TYPE_EXHAUST);
			Game::GetInstance()->psystem->AddEmiter(fPoint(0, 0), EmitterType::EMITTER_TYPE_SHIELD);
			Game::GetInstance()->psystem->AddEmiter(fPoint(0, 0), EmitterType::EMITTER_TYPE_FIRE);
			PhysicsEngine::GetInstance()->release();
			PhysicsEngine::DestroyInstance();
			PhysicsEngine::CreateInstance();
			PhysicsEngine::GetInstance()->Init();
			SoundEngine::GetInstance()->playMusic("WELCOME_BG");
			time_play = 0;
		}
		k = SceneManager::GetInstance()->CButtons.at(11)->InButton(m_touch);
		if (k == 1)
		{
			TextRender::GetIntance()->SetFont("../Resources/Fonts/SaucerBB.ttf");
			SoundEngine::GetInstance()->playMusic("WELCOME_BG");
			return new GS_MAINMENU();
		}
	}
	return NULL;
}

void GS_GAMEPLAY::_stateupdate(ESContext *esContext, float deltaTime)
{
	if ((DWORD)deltaTime < 1.0 / LIMIT_FPS) Sleep(1.0 / LIMIT_FPS - (DWORD)deltaTime);
	
	if (!PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_isRender)
	{
		IsEnd = 1;
		return;
	}

	if ((ISPause != 1)&&(IsEnd!=1))
	{
		if (deltaTime != 0)
		{
			m_deltatime = 1 / deltaTime;
		}
		time_play = time_play + deltaTime;
		PhysicsEngine::GetInstance()->Update(deltaTime);
		PhysicsEngine::GetInstance()->Key(KeyManager::GetInstance()->GetKey(), deltaTime,KeyManager::GetInstance()->m_Isdown);
	}
	if (PhysicsEngine::GetInstance()->isDetonated)
	{
		Game::GetInstance()->psystem->AddEmiter(fPoint(SceneManager::GetInstance()->GetObjwID(1)->Pos.x / SCREEN_CENTER_W, SceneManager::GetInstance()->GetObjwID(1)->Pos.y / SCREEN_CENTER_H), EmitterType::EMITTER_TYPE_WAVE_1);
		SoundEngine::GetInstance()->playSound("BOMB");
		PhysicsEngine::GetInstance()->isDetonated = false;
	}
	if (Game::GetInstance()->currentTime - SceneManager::GetInstance()->latestTime >= SPF)
	{

		SceneManager::GetInstance()->GetObjwID(9)->currentFrameX += 1;
		SceneManager::GetInstance()->GetObjwID(9)->currentFrameX %= 4;
		if (SceneManager::GetInstance()->GetObjwID(9)->currentFrameX == 0)
		{
			SceneManager::GetInstance()->GetObjwID(9)->currentFrameY += 1;
			SceneManager::GetInstance()->GetObjwID(9)->currentFrameY %= 3;
		}
		SceneManager::GetInstance()->latestTime = Game::GetInstance()->currentTime;
	}
	SceneManager::GetInstance()->Update(deltaTime);
	if (PhysicsEngine::GetInstance()->lazerTower->enemyTarget != NULL && PhysicsEngine::GetInstance()->lazerTower->enemyTarget->m_body != NULL &&  PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body != NULL)
	{
		b2Vec2 P_laze = PhysicsEngine::GetInstance()->lazerTower->enemyTarget->m_body->GetPosition();
		Vector3 tmp = SceneManager::GetInstance()->GetObjwID(1)->Pos;
		b2Vec2 p_main = b2Vec2(tmp.x/10.0f, tmp.y/10.0f);
		b2Vec2 Sub = P_laze - p_main;
		float32 sub = Sub.Length();
		b2Vec2 Sum = P_laze + p_main;
		SceneManager::GetInstance()->GetObjwID(9)->SetPosition(5 * Sum.x, 5 * Sum.y);
		SceneManager::GetInstance()->GetObjwID(9)->SetScale(Vector2(5 * sub, 40));
		float32 angl_main = PhysicsEngine::GetInstance()->lazerTower->getLazerTowerAngle();
		SceneManager::GetInstance()->GetObjwID(9)->SetRotation(angl_main + DEG_2_RAD(90));
		sub -= 2;
		std::list<Emitter*>::const_iterator it;
		for (it = Game::GetInstance()->psystem->emittersList.begin(); it != Game::GetInstance()->psystem->emittersList.end(); ++it)
			if ((*it)->type == EMITTER_TYPE_LASER)
			{
				(*it)->MoveEmitter(fPoint((5 * Sum.x + 5 * sub * cos(angl_main + DEG_2_RAD(90))) 
					/ SCREEN_CENTER_W, (5 * Sum.y + 5  * sub * cos(-angl_main)) / SCREEN_CENTER_H)); break;
			}

	}


	if (PhysicsEngine::GetInstance()->lazerTower->missile->enemyTarget != NULL && PhysicsEngine::GetInstance()->lazerTower->missile->enemyTarget->m_body != NULL &&  PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body != NULL)
	{
		b2Vec2 P_missile = 10.0f * PhysicsEngine::GetInstance()->lazerTower->missile->m_body->GetPosition();
		SceneManager::GetInstance()->GetObjwID(15)->SetPosition(P_missile.x, P_missile.y);
		float P_angle = PhysicsEngine::GetInstance()->lazerTower->missile->m_body->GetAngle();
		SceneManager::GetInstance()->GetObjwID(15)->SetRotation(P_angle+1.57f);
		std::list<Emitter*>::const_iterator it;
		for (it = Game::GetInstance()->psystem->emittersList.begin(); it != Game::GetInstance()->psystem->emittersList.end(); ++it)
			if ((*it)->type == EMITTER_TYPE_EXHAUST)
			{
				(*it)->MoveEmitter(fPoint(P_missile.x / SCREEN_CENTER_W, P_missile.y / SCREEN_CENTER_H)); 
				(*it)->angleRange.x = (180 - RAD_2_DEG(SceneManager::GetInstance()->GetObjwID(15)->Rot.z)) - 15;
				(*it)->angleRange.y = (180 - RAD_2_DEG(SceneManager::GetInstance()->GetObjwID(15)->Rot.z)) + 15;
				break;
			}
	}

	std::list<Emitter*>::const_iterator it;
	for (it = Game::GetInstance()->psystem->emittersList.begin(); it != Game::GetInstance()->psystem->emittersList.end(); ++it)
	{
		if ((*it)->type == EMITTER_TYPE_FIRE || ((*it)->type == EMITTER_TYPE_SHIELD && PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->GetShield() > 0) || (*it)->type == EMITTER_TYPE_WAVE_1)
		{
			(*it)->MoveEmitter(fPoint((SceneManager::GetInstance()->GetObjwID(1)->Pos.x) / SCREEN_CENTER_W, (SceneManager::GetInstance()->GetObjwID(1)->Pos.y) / SCREEN_CENTER_H));;
			if ((*it)->type == EMITTER_TYPE_FIRE)
			{
				(*it)->angleRange.x = (180 - RAD_2_DEG(SceneManager::GetInstance()->GetObjwID(1)->Rot.z)) - 15;
				(*it)->angleRange.y = (180 - RAD_2_DEG(SceneManager::GetInstance()->GetObjwID(1)->Rot.z)) + 15;
			}
		}
	}
}

void GS_GAMEPLAY::_render(ESContext *esContext)
{
	SceneManager::GetInstance()->Draws();
	SceneManager::GetInstance()->GetObjwID(0)->Draw(); ///////Background
	
	//pause
	SceneManager::GetInstance()->GetButtonID(5)->Draw();

	///////////////////////Rendering enemies////////////////////////////

	float32 angl; b2Vec2 p_main; Vector2 scale;

	///main
	if (PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_isRender && PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->hp > 0)
	{
		p_main = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body->GetPosition();
		SceneManager::GetInstance()->GetObjwID(1)->SetPosition(10 * p_main.x , 10 * p_main.y);
		scale = Vector2(10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->width, 10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->height);
		SceneManager::GetInstance()->GetObjwID(1)->SetScale(scale);
		angl = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body->GetAngle();
		SceneManager::GetInstance()->GetObjwID(1)->SetRotation(angl);
		SceneManager::GetInstance()->GetObjwID(1)->Draw();
	}
	if (PhysicsEngine::GetInstance()->lazerTower->enemyTarget != NULL && PhysicsEngine::GetInstance()->lazerTower->enemyTarget->m_body != NULL &&PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body != NULL)
	{
		SceneManager::GetInstance()->GetObjwID(9)->Draw();
		SoundEngine::GetInstance()->playSound("LASER");

	}
	if (PhysicsEngine::GetInstance()->lazerTower->missile->enemyTarget != NULL && PhysicsEngine::GetInstance()->lazerTower->missile->enemyTarget->m_body != NULL &&  PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body != NULL)
	{
		SceneManager::GetInstance()->GetObjwID(15)->Draw();
	}
	// enemycircle
	for (int i = 1; i < 1 + MAX_ENEMYCIRCLE; i++)
	{
		if (PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_isRender)
		{
			b2Vec2 hi = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_body->GetPosition();
			SceneManager::GetInstance()->GetObjwID(7)->SetPosition(10 * hi.x, 10 * hi.y);
			scale = Vector2(10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->width, 10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->height);
			SceneManager::GetInstance()->GetObjwID(7)->SetScale(scale);
			SceneManager::GetInstance()->GetObjwID(7)->Draw();
		}

	}
	
	// enemy2
	
	for (int i = MAX_ENEMYCIRCLE+1; i < MAX_ENEMYCIRCLE + 1 + MAX_ENEMYRECTANGLE; i++)
	{
		if (PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_isRender)
		{
			b2Vec2 hi = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_body->GetPosition();
			angl = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_body->GetAngle();
			SceneManager::GetInstance()->GetObjwID(2)->SetPosition(10 * hi.x, 10 * hi.y);
			scale = Vector2(10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->width, 10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->height);
			SceneManager::GetInstance()->GetObjwID(2)->SetScale(scale);
			SceneManager::GetInstance()->GetObjwID(2)->Draw();
		}

	}
	//////////////boss bullets
	int boss = MAX_ENEMYCIRCLE + 1 + MAX_ENEMYRECTANGLE + MAX_ENEMYBULLET;
	for (int i = MAX_ENEMYCIRCLE + MAX_ENEMYRECTANGLE + 1; i < MAX_ENEMYCIRCLE + 1 + MAX_ENEMYRECTANGLE + MAX_ENEMYBULLET; i++)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		if (PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_isRender && PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(boss)->m_isRender)
		{
			b2Vec2 hi = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_body->GetPosition();
			SceneManager::GetInstance()->GetObjwID(13)->SetPosition(10 * hi.x, 10 * hi.y);
			scale = Vector2(10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->width, 10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->height);
			SceneManager::GetInstance()->GetObjwID(13)->SetScale(scale);	
			SceneManager::GetInstance()->GetObjwID(13)->Draw();
			
		}
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	//////////////boss

	if (PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(boss)->m_isRender &&PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(boss)->m_body != NULL)
	{
		p_main = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(boss)->m_body->GetPosition();
		SceneManager::GetInstance()->GetObjwID(12)->SetPosition(10 * p_main.x, 10 * p_main.y);
		scale = Vector2(10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(boss)->width, 10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(boss)->height);
		SceneManager::GetInstance()->GetObjwID(12)->SetScale(scale);
		angl = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(boss)->m_body->GetAngle();
		SceneManager::GetInstance()->GetObjwID(12)->SetRotation(angl);
		SceneManager::GetInstance()->GetObjwID(12)->Draw();

	}
	//itembom

	for (int i = boss + 1; i <= boss + MAX_ITEMBOM; i++)
	{
		if (PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_isRender)
		{
			b2Vec2 hi = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_body->GetPosition();
			SceneManager::GetInstance()->GetObjwID(17)->SetPosition(10 * hi.x, 10 * hi.y);
			scale = Vector2(10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->width, 10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->height);
			SceneManager::GetInstance()->GetObjwID(17)->SetScale(scale);
			SceneManager::GetInstance()->GetObjwID(17)->Draw();
		}

	}
	//itemhp

	for (int i = boss + 1 + MAX_ITEMBOM; i < boss + 1 + MAX_ITEMBOM + MAX_ITEMHP; i++)
	{
		if (PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_isRender)
		{
			b2Vec2 hi = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_body->GetPosition();
			SceneManager::GetInstance()->GetObjwID(16)->SetPosition(10 * hi.x, 10 * hi.y);
			scale = Vector2(10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->width, 10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->height);
			SceneManager::GetInstance()->GetObjwID(16)->SetScale(scale);
			SceneManager::GetInstance()->GetObjwID(16)->Draw();
		}

	}
	// newenemy 
	for (int i = boss  + MAX_ITEMBOM + MAX_ITEMHP + 1; i < boss + 1 + MAX_ITEMBOM + MAX_ITEMHP + MAX_NEWENEMY; i++)
	{
		if (PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_isRender)
		{
			b2Vec2 hi = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_body->GetPosition();
			SceneManager::GetInstance()->GetObjwID(18)->SetPosition(10 * hi.x, 10 * hi.y);
			scale = Vector2(10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->width, 10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->height);
			SceneManager::GetInstance()->GetObjwID(18)->SetScale(scale);
			SceneManager::GetInstance()->GetObjwID(18)->Draw();
		}
	}

	//bulletenemy
	for (int i = boss  + MAX_ITEMBOM + MAX_ITEMHP + MAX_NEWENEMY + 1; i < boss + 1 + MAX_ITEMBOM + MAX_ITEMHP + MAX_NEWENEMY + MAX_BULLETNEWENEMY; i++)
	{
		if (PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_isRender)
		{
			b2Vec2 hi = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->m_body->GetPosition();
			SceneManager::GetInstance()->GetObjwID(23)->SetPosition(10 * hi.x, 10 * hi.y);
			scale = Vector2(10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->width, 10 * PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(i)->height);
			SceneManager::GetInstance()->GetObjwID(23)->SetScale(scale);
			SceneManager::GetInstance()->GetObjwID(23)->Draw();
		}
	}

	//bullet


	for (int i = 0; i < MAX_BULLET; i++)
	{
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);		
		if (PhysicsEngine::GetInstance()->m_b2D->m_bullet.at(i)->m_isRender && PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_isRender)
		{
			b2Vec2 hi = PhysicsEngine::GetInstance()->m_b2D->m_bullet.at(i)->m_body->GetPosition();
			SceneManager::GetInstance()->GetObjwID(8)->SetPosition(10 * hi.x, 10 * hi.y);
			SceneManager::GetInstance()->GetObjwID(8)->SetRotation(PhysicsEngine::GetInstance()->m_b2D->m_bullet.at(i)->bulletAngle);
			SceneManager::GetInstance()->GetObjwID(8)->Draw();
		}
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	//laser and missle
	
	if (PhysicsEngine::GetInstance()->lazerTower->enemyTarget != NULL && PhysicsEngine::GetInstance()->lazerTower->enemyTarget->m_body != NULL &&PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body != NULL)
	{
		SceneManager::GetInstance()->Objects.at(9)->Draw();
	}
	if (PhysicsEngine::GetInstance()->lazerTower->missile->enemyTarget != NULL && PhysicsEngine::GetInstance()->lazerTower->missile->enemyTarget->m_body != NULL &&  PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_body != NULL)
	{
		//std::cout << "yes" << std::endl;
		SceneManager::GetInstance()->Objects.at(15)->Draw();
	}
	// GUI(bomb,hp.shield)
	float topx = 580;
	float topy = 450;
	///////  HP
	SceneManager::GetInstance()->GetObjwID(19)->SetPosition(-topx - 20, topy - 10);
	SceneManager::GetInstance()->GetObjwID(19)->Draw();
	char vhp[15];
	float valueHP = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_hp;
	if (valueHP < 0) valueHP = 0;
	itoa(valueHP, vhp, 10);
	TextRender::GetIntance()->RenderString(vhp, Vector4(1.0f, 1.0f, 1.0f, 1.0f), -topx + 20, topy + 10, 1.2f, 1.2f);

	//////  ROCKETS
	SceneManager::GetInstance()->GetObjwID(20)->SetPosition(-topx - 20, topy - 60);
	SceneManager::GetInstance()->GetObjwID(20)->Draw();
	char vbomb[15];
	itoa(PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->bom, vbomb, 10);
	TextRender::GetIntance()->RenderString(vbomb, Vector4(1.0f, 1.0f, 1.0f, 1.0f), -topx + 20, topy - 40, 1.2f, 1.2f);

	///////  SHIELD
	SceneManager::GetInstance()->GetObjwID(21)->SetPosition(-topx - 20, topy - 105);
	SceneManager::GetInstance()->GetObjwID(21)->Draw();
	float valueShield = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->GetShield();
	if (valueShield < 0) valueShield = 0;
	char vshield[15];
	itoa(valueShield, vshield, 10);
	TextRender::GetIntance()->RenderString(vshield, Vector4(1.0f, 1.0f, 1.0f, 1.0f), -topx + 20, topy - 90, 1.2f, 1.2f);

	///////  TIME COUNTER
	SceneManager::GetInstance()->GetObjwID(22)->SetPosition(-topx - 20, topy - 150);
	SceneManager::GetInstance()->GetObjwID(22)->Draw();
	char vtime[15];
	int t = time_play / 60;
	if (t < 1)
	{
		sprintf(vtime, "%.2f", time_play);
		strcat(vtime, " s");
		TextRender::GetIntance()->RenderString(vtime, Vector4(1.0f, 1.0f, 1.0f, 1.0f), -topx + 20, (topy - 140), 1.2f, 1.2f);
	}
	else
	{
		char vtime_s[10];
		int time_s = time_play - t * 60;

		itoa(t, vtime, 10);
		itoa(time_s, vtime_s, 10);
		strcat(vtime, " m ");
		strcat(vtime, vtime_s);
		strcat(vtime, " s");

		//strcat(vtime, " s");
		TextRender::GetIntance()->RenderString(vtime, Vector4(1.0f, 1.0f, 1.0f, 1.0f), -topx + 20, topy - 140, 1.2f, 1.2f);
	}

	//fps
	char vfps[15];
	itoa(m_deltatime, vfps, 10);
	char Ifps[20];
	memset(Ifps, 0, 20);
	strcat(Ifps, "fps: ");
	strcat(Ifps, vfps);

	TextRender::GetIntance()->RenderString(Ifps, Vector4(1.0f, 1.0f, 1.0f, 1.0f), -SCREEN_CENTER_W + 50, -(SCREEN_CENTER_H)+5, 0.7f, 0.7f);
	//score
	char vpoint[15];
	int point = PhysicsEngine::GetInstance()->m_b2D->m_objectList.at(0)->m_point;
	itoa(point, vpoint, 10);
	char score[20];
	memset(score, 0, 20);
	strcat(score, "SCORE: ");
	strcat(score, vpoint);
	TextRender::GetIntance()->RenderString(score, Vector4(1.0f, 1.0f, 1.0f, 1.0f), topx - 680, topy + 10, 1.2f, 1.2f);
	Game::GetInstance()->psystem->PostUpdate();
	Game::GetInstance()->psystem->Update(Game::GetInstance()->dt);
	std::list<Emitter*>::const_iterator it;
	for (it = Game::GetInstance()->psystem->emittersList.begin(); it != Game::GetInstance()->psystem->emittersList.end(); ++it)
		if ((*it)->type == EMITTER_TYPE_LASER || (*it)->type == EMITTER_TYPE_EXHAUST)
		{
			(*it)->MoveEmitter(fPoint(2, 2));
		}
		else if ((*it)->type == EMITTER_TYPE_SHIELD && valueShield <= 0)
		{
			(*it)->MoveEmitter(fPoint(2, 2));
		}
	if (ISPause == 1)
	{

		SceneManager::GetInstance()->GetObjwID(11)->SetPosition(300, 0);
		SceneManager::GetInstance()->GetObjwID(14)->Draw();
		//SceneManager::GetInstance()->GetObjwID(10)->Draw();
		SceneManager::GetInstance()->GetObjwID(11)->Draw();
		SceneManager::GetInstance()->GetButtonID(6)->Draw();
		SceneManager::GetInstance()->GetButtonID(7)->Draw();
		SceneManager::GetInstance()->GetButtonID(8)->Draw();
		SceneManager::GetInstance()->GetButtonID(9)->Draw();
		SceneManager::GetInstance()->GetButtonID(10)->Draw();
		SceneManager::GetInstance()->GetObjwID(11)->SetPosition(-300, 0);
		SceneManager::GetInstance()->GetObjwID(11)->Draw();
		TextRender::GetIntance()->RenderString("OPTIONS", Vector4(1.0f, 1.0f, 0.0f, 1.0f), 200, 150, 2.0f, 2.0f);
		TextRender::GetIntance()->RenderString("Music", Vector4(1.0f, 1.0f, 0.0f, 1.0f), 250, 50, 1.3f, 1.3f);
		char vmusic[15]; char vsound[15];
		itoa(SoundEngine::GetInstance()->GetVolumeMusic(), vmusic, 10);
		TextRender::GetIntance()->RenderString(vmusic, Vector4(1.0f, 1.0f, 0.0f, 1.0f), 275, 0, 1.3f, 1.3f);
		TextRender::GetIntance()->RenderString("SFX", Vector4(1.0f, 1.0f, 0.0f, 1.0f), 250, -120, 1.3f, 1.3f);
		itoa(SoundEngine::GetInstance()->GetVolumeSound(), vsound, 10);
		TextRender::GetIntance()->RenderString(vsound, Vector4(1.0f, 1.0f, 0.0f, 1.0f), 275, -170, 1.3f, 1.3f);
		TextRender::GetIntance()->RenderString("OPTIONS", Vector4(1.0f, 1.0f, 0.0f, 1.0f), -400, 150, 2.0f, 2.0f);
		TextRender::GetIntance()->RenderString("New game", Vector4(1.0f, 1.0f, 0.0f, 1.0f), -400, 25, 1.3f, 1.3f);
		TextRender::GetIntance()->RenderString("Main menu", Vector4(1.0f, 1.0f, 0.0f, 1.0f), -400, -145, 1.3f, 1.3f);
	}
	if (IsEnd == 1)
	{
		SceneManager::GetInstance()->Objects.at(14)->Draw();
		SceneManager::GetInstance()->Objects.at(11)->SetPosition(-300, 0);
		SceneManager::GetInstance()->Objects.at(11)->Draw();
		TextRender::GetIntance()->RenderString("OPTIONS", Vector4(1.0f, 1.0f, 0.0f, 1.0f), -400, 150, 2.0f, 2.0f);
		TextRender::GetIntance()->RenderString("New game", Vector4(1.0f, 1.0f, 0.0f, 1.0f), -400, 25, 1.3f, 1.3f);
		TextRender::GetIntance()->RenderString("Main menu", Vector4(1.0f, 1.0f, 0.0f, 1.0f), -400, -145, 1.3f, 1.3f);
		TextRender::GetIntance()->RenderString("GAME OVER", Vector4(1.0f, 0.0f, 0.0f, 1.0f), 0, 100, 3.0f, 3.0f);
		TextRender::GetIntance()->RenderString(score, Vector4(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 1.5f, 1.5f);
	}
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);


}

void GS_MAINMENU::enter(Game & state, ESContext * esContext)
{

	SceneManager::GetInstance()->GetObjwID(3)->Draw();
	SceneManager::GetInstance()->GetObjwID(6)->Draw();
	SceneManager::GetInstance()->GetButtonID(0)->Draw();
	TextRender::GetIntance()->RenderString("Play ", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -50.0f, 100.0f, 1.0f, 1.0f);
	SceneManager::GetInstance()->GetButtonID(1)->Draw();
	TextRender::GetIntance()->RenderString("Options", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -50.0f, 35.0f, 1.0f, 1.0f);
	SceneManager::GetInstance()->GetButtonID(2)->Draw();
	TextRender::GetIntance()->RenderString("Credit ", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -50.0f, -35.0f, 1.0f, 1.0f);
	SceneManager::GetInstance()->GetButtonID(3)->Draw();
	TextRender::GetIntance()->RenderString("Quit ", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -50.0f, -105.0f, 1.0f, 1.0f);  
	TextRender::GetIntance()->RenderString("Hyper Accel", Vector4(0.219, 0.878, 0.843, 1.0f), -380.0f, 300.0f, 4.0f, 4.0f);
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);

}

StateManager * GS_MAINMENU::handleInput(Game & state, int m_key, Vector2 m_touch)
{
	int k = SceneManager::GetInstance()->GetButtonID(0)->InButton(m_touch);
	if (k == 1)
	{
		PhysicsEngine::GetInstance()->release();
		PhysicsEngine::DestroyInstance();
		PhysicsEngine::CreateInstance();
		PhysicsEngine::GetInstance()->Init();
		TextRender::GetIntance()->SetFont("../Resources/Fonts/digifaw.ttf");

		return new GS_GAMEPLAY();
	}
	k = SceneManager::GetInstance()->GetButtonID(1)->InButton(m_touch);
	if (k == 1)
	{
		TextRender::GetIntance()->SetFont("../Resources/Fonts/digifaw.ttf");
		return new GS_OPTION();
	}
	k = SceneManager::GetInstance()->GetButtonID(2)->InButton(m_touch);
	if (k == 1)
	{
		TextRender::GetIntance()->SetFont("../Resources/Fonts/SaucerBB.ttf");
		return new GS_CREDITS();
	}

	k = SceneManager::GetInstance()->GetButtonID(3)->InButton(m_touch);
	if (k == 1)
		std::exit(0);
}

void GS_MAINMENU::_stateupdate(ESContext * esContext, float deltaTime)
{

}

void GS_MAINMENU::_render(ESContext * esContext)
{

}

void GS_OPTION::enter(Game & state, ESContext * esContext)
{

}

StateManager * GS_OPTION::handleInput(Game & state, int m_key, Vector2 m_touch)
{
	int h = SceneManager::GetInstance()->GetButtonID(7)->InButton(m_touch);
	if (h == 1)
	{
		SoundEngine::GetInstance()->VolumeMusicDow();
	}
	 h = SceneManager::GetInstance()->GetButtonID(8)->InButton(m_touch);
	if (h == 1)
	{
		SoundEngine::GetInstance()->VolumeMusicUp();
	}
	 h = SceneManager::GetInstance()->GetButtonID(9)->InButton(m_touch);
	if (h == 1)
	{
		SoundEngine::GetInstance()->VolumeSoundDow();
	}
      h = SceneManager::GetInstance()->GetButtonID(10)->InButton(m_touch);
	if (h == 1)
	{
		SoundEngine::GetInstance()->VolumeSoundUp();
	}
	int k = SceneManager::GetInstance()->GetButtonID(6)->InButton(m_touch);
	if (k == 1)
	{
		TextRender::GetIntance()->SetFont("../Resources/Fonts/SaucerBB.ttf");
		return new GS_MAINMENU();
	}
}

void GS_OPTION::_stateupdate(ESContext * esContext, float deltaTime)
{
	SoundEngine::GetInstance()->Update();
}

void GS_OPTION::_render(ESContext * esContext)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	SceneManager::GetInstance()->GetObjwID(11)->SetPosition(300, 0);
	SceneManager::GetInstance()->GetObjwID(10)->Draw();
	SceneManager::GetInstance()->GetObjwID(11)->Draw();
	SceneManager::GetInstance()->GetButtonID(6)->Draw();
	SceneManager::GetInstance()->GetButtonID(7)->Draw();
	SceneManager::GetInstance()->GetButtonID(8)->Draw();
	SceneManager::GetInstance()->GetButtonID(9)->Draw();
	SceneManager::GetInstance()->GetButtonID(10)->Draw();
	
	TextRender::GetIntance()->RenderString("OPTIONS", Vector4(1.0f, 1.0f, 0.0f, 1.0f), 200, 150, 2.0f, 2.0f);

	TextRender::GetIntance()->RenderString("Music", Vector4(1.0f, 1.0f, 0.0f, 1.0f), 250, 50, 1.3f, 1.3f);
	char vmusic[15]; char vsound[15];
	itoa(SoundEngine::GetInstance()->GetVolumeMusic(), vmusic, 10);
	TextRender::GetIntance()->RenderString(vmusic, Vector4(1.0f, 1.0f, 0.0f, 1.0f),275, 0, 1.3f, 1.3f);
	TextRender::GetIntance()->RenderString("Sound", Vector4(1.0f, 1.0f, 0.0f, 1.0f), 250, -120, 1.3f, 1.3f);
	itoa(SoundEngine::GetInstance()->GetVolumeSound(), vsound, 10);
	TextRender::GetIntance()->RenderString(vsound, Vector4(1.0f, 1.0f, 0.0f, 1.0f), 275, -170, 1.3f, 1.3f);
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void GS_CREDITS::enter(Game & state, ESContext * esContext)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	SceneManager::GetInstance()->GetObjwID(5)->Draw();
	SceneManager::GetInstance()->GetButtonID(6)->Draw();
	TextRender::GetIntance()->RenderString("CREDITS!", Vector4(1.0f, 1.0f, 0.0f, 1.0f), -100, 200, 2.0f, 2.0f);
	TextRender::GetIntance()->RenderString("This is THE most amazing game ever, made by", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -400, 100, 1.0f, 1.0f);
	TextRender::GetIntance()->RenderString("Team 2's interns : Lan, Nghia, Duc, Long ", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -400, 30, 1.0f, 1.0f);
	TextRender::GetIntance()->RenderString("Lan                    : Lead, Graphics, Sound & Engine", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -400, -60, 1.0f, 1.0f);
	TextRender::GetIntance()->RenderString("Nghia               : UI & Engine", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -400, -110, 1.0f, 1.0f);
	TextRender::GetIntance()->RenderString("Duc&Long    : Physics & Game Logic", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -400, -160, 1.0f, 1.0f);
	TextRender::GetIntance()->RenderString("Have fun!", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -400, -270, 1.5f, 1.5f);
	TextRender::GetIntance()->RenderString("Hanoi, 08/24/19", Vector4(1.0f, 1.0f, 1.0f, 1.0f), -10, -280, 1.0f, 1.0f);
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

StateManager * GS_CREDITS::handleInput(Game & state, int m_key, Vector2 m_touch)
{
	int k = SceneManager::GetInstance()->GetButtonID(6)->InButton(m_touch);
	if (k == 1)
	{
		TextRender::GetIntance()->SetFont("../Resources/Fonts/SaucerBB.ttf");
		return new GS_MAINMENU();
	}
}

void GS_CREDITS::_stateupdate(ESContext * esContext, float deltaTime)
{
}

void GS_CREDITS::_render(ESContext * esContext)
{

}