#pragma once

#include <SDL_mixer.h>
#include <ConfigEditor.hpp>
#include <string>
#include <vector>
#include <queue>

struct AudioEvent
{
	//IDK ? 
};

class AudioManager
{
    private:
        std::vector<Mix_Chunk*> SFX;
        std::vector<Mix_Music*> Music;
		std::queue<AudioEvent*> queue;

    public:
        AudioManager();
        AudioManager(AudioManager const & src);
        AudioManager(ConfigEditor &cfg);
        ~AudioManager();

        AudioManager &operator=(AudioManager const & src);
        std::vector<Mix_Music*> getMusic() const;
        std::vector<Mix_Chunk*> getSFX() const;

        void PlayMusic(int i);
        void PauseMusic(int i);
        void PlaySFX(int i);

        void MusicVolume(int vol);
        void SFXVolume(int vol);
		/*
			pushEvent() ?
			execQueue() ?
			setVolume() 
		*/
};