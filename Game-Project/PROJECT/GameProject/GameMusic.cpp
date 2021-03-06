#include "GameMusic.h"



GameMusic::GameMusic()
{
	m_volume = 50;
	isPlaying = false;
}


GameMusic::~GameMusic()
{
}

void GameMusic::Init(char* pathFileMusic)
{
	if (!m_music.openFromFile(pathFileMusic))
	{
		std::cout << "Music file loading failed." << pathFileMusic << std::endl;
	}
	m_music.setVolume(m_volume);
	m_music.setLoop(true);
}


void GameMusic::Play(bool isLoop)
{
	//m_music.setPlayingOffset(sf::seconds(n_sec));
	m_music.play();
	m_music.setLoop(isLoop);
}

void GameMusic::Pause()
{
	//m_curTimePlaying = m_music.getPlayingOffset();
	m_music.pause();
}

void GameMusic::Resume()
{
	//m_music.setPlayingOffset(m_curTimePlaying);
	m_music.play();
}

void GameMusic::Stop()
{
	m_music.stop();
}

void GameMusic::SetVolume(float volume)
{
	m_music.setVolume(m_volume*volume*0.01);
}

void GameMusic::SetLocalVolume(float volume)
{
	m_volume = volume;
}

void GameMusic::SetLoop(bool isLoop = true)
{
	m_music.setLoop(isLoop);
}

void GameMusic::SetPitch(float pitch)
{
	m_music.setPitch(pitch);
}
