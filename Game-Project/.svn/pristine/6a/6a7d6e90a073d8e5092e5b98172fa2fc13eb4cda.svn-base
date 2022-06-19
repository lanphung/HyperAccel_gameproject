#include "stdafx.h"
#include "KeyManager.h"

KeyManager * KeyManager::ms_pInstance = NULL;

int KeyManager::GetKey()
{
	return m_key;
}

void KeyManager::Key(unsigned char key, bool bIsPressed)
{
	if (bIsPressed == true)
	{
		if ((key == 'W') || (key == 'w')) m_key = m_key | KeyUpMove;
		if ((key == 'S') || (key == 's'))m_key = m_key | KeyDownMove;
		if ((key == 'A') || (key == 'a'))m_key = m_key | KeyLeftMove;
		if ((key == 'D') || (key == 'd'))m_key = m_key | KeyRightMove;
		if (key == VK_UP)m_key = m_key | KeyUpRota;
		if (key == VK_DOWN) m_key = m_key | KeyDownRota;
		if (key == VK_LEFT) m_key = m_key | KeyLeftRota;
		if (key == VK_RIGHT) m_key = m_key | KeyRightRota;
		if (key == VK_SPACE) m_key = m_key | KeyBom;
		if (key == VK_NUMPAD2)m_key = m_key | KeyTransform;
		m_Isdown = 1;
	}
	else
	{
		if ((key == 'W') || (key == 'w')) m_key = m_key ^ KeyUpMove;
		if ((key == 'S') || (key == 's')) m_key = m_key ^ KeyDownMove;
		if ((key == 'A') || (key == 'a')) m_key = m_key ^ KeyLeftMove;
		if ((key == 'D') || (key == 'd')) m_key = m_key ^ KeyRightMove;
		if (key == VK_UP)m_key = m_key ^ KeyUpRota;
		if (key == VK_DOWN)m_key = m_key ^ KeyDownRota;
		if (key == VK_LEFT)m_key = m_key ^ KeyLeftRota;
		if (key == VK_RIGHT)m_key = m_key ^ KeyRightRota;
		if (key == VK_SPACE)m_key = m_key ^ KeyBom;
		if (key == VK_NUMPAD2)m_key = m_key ^ KeyTransform;
		m_Isdown = 0;
	}
}
