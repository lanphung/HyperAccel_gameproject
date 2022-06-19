#include "stdafx.h"
#include "SoundEngine.h"


SoundEngine * SoundEngine::ms_pInstance = NULL;

void SoundEngine::playMusic(char* name)
{
	for (auto &element : m_aMusic)
	if (strcmp(element->loc, name) == 0 && !element->isPlaying)
	{
		element->Play(true);
		element->isPlaying = true;
	}
	else if (strcmp(element->loc, name) != 0 && element->isPlaying)
	{
		element->Stop();
		element->isPlaying = false;
	}
}

void SoundEngine::playSound(char* name)
{
	for (auto &element : m_aSound)
		if (strcmp(element->loc, name) == 0) element->Play();
}

void SoundEngine::SetVolumeMusic()
{
	for (auto &element : m_aMusic) element->SetVolume(master_volumeMusic);
}

void SoundEngine::SetVolumeSound()
{
	for (auto &element : m_aSound) element->SetVolume(master_volumeSound);
}

void SoundEngine::Init(char* filePath)
{
	FILE* sFile = fopen(filePath, "r");
	if (!sFile)
	{
		LOG("Can't open audio specification file");
	}

	int count;
	float local_volume;
	char path[100];
	fscanf(sFile, "#MUSIC %d\n", &count);
	fscanf(sFile, "%f\n", &master_volumeMusic);
	for (int i = 0; i < count; i++)
	{
		GameMusic* music = new GameMusic;
		fscanf(sFile, "ID %d %s\n", &music->ID, music->loc);
		fscanf(sFile, "FILE %s\n", path);
		fscanf(sFile, "VOLUME %f\n", &local_volume);
		music->Init(path);
		music->SetLocalVolume(local_volume);
		music->SetVolume(master_volumeMusic);
		m_aMusic.push_back(music);
	}

	fscanf(sFile, "\n#SOUND %d\n", &count);
	fscanf(sFile, "%f\n", &master_volumeSound);
	for (int i = 0; i < count; i++)
	{
		GameSound* sound = new GameSound;
		fscanf(sFile, "ID %d %s\n", &sound->ID, sound->loc);
		fscanf(sFile, "FILE %s\n", path);
		fscanf(sFile, "VOLUME %f\n", &local_volume);
		sound->Init(path);
		sound->SetLocalVolume(local_volume);
		sound->SetVolume(master_volumeSound);
		m_aSound.push_back(sound);
	}
	fclose(sFile);
}

void SoundEngine::Update()
{
	for (auto &element : m_aMusic)
	{
		element->SetVolume(master_volumeMusic);
	}

	for (auto &element : m_aSound)
	{
		element->SetVolume(master_volumeSound);
	}
}

void SoundEngine::CleanUp()
{
	for (int i = 0; i < m_aMusic.size(); i++) RELEASE(m_aMusic[i]);
	for (int i = 0; i < m_aSound.size(); i++) RELEASE(m_aSound[i]);
}