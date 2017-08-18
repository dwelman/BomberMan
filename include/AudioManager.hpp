#pragma once

#include <SDL_mixer.h>
#include <ConfigEditor.hpp>
#include <string>
#include <vector>
#include <queue>

enum SFXs
{
    EXPLODE = 0,
    WALK,
    CRUMBLING
};

enum Musics
{
    START = 0,
    COBBLE

};

struct AudioEvent
{
    bool    type;
    int     pos; 
};

class AudioManager
{
    private:
        std::vector<Mix_Chunk*> SFX;
        std::vector<Mix_Music*> Music;
        std::queue<AudioEvent*> queue;
        int                     SFXVol;
        int                     MusicVol;
        int                     MasterVol;

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
		void MasterVolume(int vol); 
		
		void PushEvent(bool type, int);
		void execQueue();
		
};