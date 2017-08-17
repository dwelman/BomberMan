#pragma once

#include <SDL_mixer.h>
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
        ~AudioManager();

        AudioManager &operator=(AudioManager const & src);
        std::vector<Mix_Music*> getMusic() const;
        std::vector<Mix_Chunk*> getSFX() const;

        void PlayMusic(int i);
        void PauseMusic(int i);
        void PlaySFX(int i);
		/*
			pushEvent() ?
			execQueue() ?
			setVolume() 
		*/
};