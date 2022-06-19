#pragma once
#include <stdio.h>
#include "Vertex.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Lights.h"
#include "ResourceManager.h"
#include "Object.h"
#include <iostream>
#include "Sprite.h"
#include "define.h"
#include "ParticleSystem.h"
#include "CButton.h"
#include "../Utilities/utilities.h"

class SceneManager
{
protected:
	SceneManager();
	~SceneManager();
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	SceneManager(const SceneManager &) {}
	SceneManager& operator =(const SceneManager &) {}
public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new SceneManager;
	}
	static SceneManager * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		RELEASE(ms_pInstance);
	}
	void SceneLoading();
	void Init();
	float latestTime = 0;
	Object* GetObjwID(int ID);
	CButton* GetButtonID(int ID);
	void Update(float deltaTime);
	void Draws();
	void CleanUp();
	int ObjectCount;
	int ButtonCount;
	int LightsCount;
	int NrLights;
	bool yesLaser = false;
	std::vector <Object*> Objects;
	std::vector <Lights*> Light;
	std::vector <CButton*> CButtons;
protected:
	static SceneManager * ms_pInstance;
};
