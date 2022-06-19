#pragma once
#include "../Utilities/utilities.h"
#include "define.h"

class KeyManager
{
protected:
	KeyManager() {}
	~KeyManager() {}
	KeyManager(const KeyManager &) {}
	KeyManager& operator =(const KeyManager &) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new KeyManager;
	}
	static KeyManager * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		RELEASE(ms_pInstance);
	}
	int m_key=0;
	int GetKey();
	void Key (unsigned char key, bool bIsPressed);
	int m_Isdown = 0;
protected:
	static KeyManager * ms_pInstance;
};
