#pragma once
#include "Object.h"
#include "p2Log.h"
#include <SFML/Audio.hpp>
#include "GameMusic.h"
#include "GameSound.h"

class SoundEngine
{
protected:
	SoundEngine() {}
	~SoundEngine() {}
	SoundEngine(const SoundEngine &) {}
	SoundEngine& operator =(const SoundEngine &) {}

public:

	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new SoundEngine;
	}
	static SoundEngine * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			RELEASE(ms_pInstance);
		}
	}
	sf::Music musicPlayer;
	void playSound() {}
	void playMusic(char* name);
	void playSound(char* name);
	void Init(char* filePath);
	void Update();
	void CleanUp();
	void SetVolumeMusic();
	float GetVolumeMusic() { return master_volumeMusic; }
	void VolumeMusicUp() { master_volumeMusic = master_volumeMusic + 4 > 100 ? 100 : master_volumeMusic + 4; SetVolumeMusic();}
	void VolumeMusicDow() { master_volumeMusic = master_volumeMusic - 4 < 0 ? 0 : master_volumeMusic - 4; SetVolumeMusic();}
	void SetVolumeSound();
	float GetVolumeSound() { return master_volumeSound; }
	void VolumeSoundUp() { master_volumeSound = master_volumeSound + 4 > 100 ? 100 : master_volumeSound + 4; SetVolumeSound();}
	void VolumeSoundDow() { master_volumeSound = master_volumeSound - 4 < 0 ? 0 : master_volumeSound - 4; SetVolumeSound();}
	std::vector<GameMusic*> m_aMusic;
	std::vector<GameSound*> m_aSound;

private:
	float master_volumeMusic;
	float master_volumeSound;

protected:
	static SoundEngine * ms_pInstance;

};