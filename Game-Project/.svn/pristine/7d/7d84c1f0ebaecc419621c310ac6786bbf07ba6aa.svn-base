#pragma once
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>

class GameSound
{

public:
	GameSound();
	~GameSound();
	void Init(char* pathFileSound);
	void Play();
	void SetVolume(float volume);
	void Stop();
	void SetLoop(bool isLoop);
	void SetPitch(float pitch);
	float getVolume() { return m_volume; }
	void SetLocalVolume(float volume);
	int ID;
	char loc[50];

private:
	sf::Sound m_sound;
	sf::SoundBuffer m_buffer;
	float m_volume;
};

