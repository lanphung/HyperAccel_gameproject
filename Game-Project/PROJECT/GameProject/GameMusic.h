#pragma once
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>

class GameMusic
{
public:
	GameMusic ();
	~GameMusic();
	void Init(char* pathFileMusic);
	void Play(bool isLoop);
	void SetVolume(float volume);
	void Pause();
	void Resume();
	void Stop();
	void SetLoop(bool isLoop);
	void SetPitch(float pitch);
	float getVolume() { return m_volume; }
	void SetLocalVolume(float volume);
	int ID;
	char loc[50];
	bool isPlaying;

private:
	sf::Music m_music;
	//sf::Time m_curTimePlaying;
	float m_volume;
};

