#pragma once
#include "SceneManager.h"
class TouchManager
{
protected:
	TouchManager() { isTouchedDown = false; }
	~TouchManager() {}
	TouchManager(const TouchManager &) {}
	TouchManager& operator =(const TouchManager &) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new TouchManager;
	}
	static TouchManager * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		RELEASE(ms_pInstance);
	}
	bool isTouchedDown;
	void MainCharDirUpdate(int x, int y);
	Vector2 m_touch;
	void SetPosTouch(float x, float y);
	float AngleCalc(Vector2 pos, Vector2 target);
protected:
	static TouchManager * ms_pInstance;
};
