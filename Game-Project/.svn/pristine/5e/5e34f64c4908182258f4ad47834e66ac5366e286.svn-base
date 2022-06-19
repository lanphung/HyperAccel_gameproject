#pragma once
#include "Object.h"
class WVP
{
protected:
	WVP() {}
	~WVP() {}
	/*Used to calculate view matrix only*/
	WVP(const WVP &) {}
	WVP& operator =(const WVP &) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new WVP;
	}
	static WVP * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}

	void createViewMat();
	Matrix getViewMat() { return ViewMat; }
	Matrix ViewMat;

protected:
	static WVP * ms_pInstance;
};