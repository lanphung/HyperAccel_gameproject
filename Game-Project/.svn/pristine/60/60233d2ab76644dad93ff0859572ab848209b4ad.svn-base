#pragma once
#include <stdio.h>
#include "Vertex.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include <iostream>
#include <vector>
#include "define.h"
#include "../Utilities/utilities.h"

class ResourceManager
{
protected:
	ResourceManager();
	~ResourceManager();
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	ResourceManager(const ResourceManager &) {}
	ResourceManager& operator =(const ResourceManager &) {}
public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new ResourceManager;
	}
	static ResourceManager * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		RELEASE(ms_pInstance);
	}
	ResourceManager & ResourceLoading();
	Texture* getTexture(int ID);
	int ModelCount;
	int TwoDTexturesCount;
	int ShadersCount;
	std::vector <Model*> Models;
	std::vector <Texture*> Textures;
	std::vector <Shaders*> ShadersList;
	void CleanUp();
protected:
	static ResourceManager * ms_pInstance;
};

