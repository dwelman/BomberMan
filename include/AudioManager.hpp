#pragma once

#include <SDL_mixer.h>
#include <ConfigEditor.hpp>
#include <math.h>
#include <string>
#include <vector>
#include <queue>
#include <map>

enum eSFX
{
	NOSFX = 0,
    EXPLODE,
    WALK,
    CRUMBLING
};

enum eMusic
{
	NOMUSIC = 0,
    START,
    COBBLE
};

struct AudioEvent
{
    bool        isMusic;
    eSFX        sfx;
    eMusic      music;
};

class AudioManager
{
    private:
        std::map<eSFX, Mix_Chunk*>    	SFX;
        std::map<eMusic, Mix_Music*>    Music;
        std::queue<AudioEvent*>         queue;
        double                      SFXVol;
        double                      MusicVol;
        double                      MasterVol;

    public:
        AudioManager();
        AudioManager(AudioManager const & src);
        AudioManager(ConfigEditor &cfg);
        ~AudioManager();

        AudioManager &operator=(AudioManager const & src);
		std::map<eMusic, Mix_Music*> getMusic() const;
		std::map<eSFX,Mix_Chunk*>  getSFX() const;

        void PlayMusic(eMusic track);
        void PauseMusic(eMusic track);
        void PlaySFX(eSFX track);

        void MusicVolume(double vol);
        void SFXVolume(double vol);
		void MasterVolume(double vol);

		void PushEvent(AudioEvent *e);
		void PushMusic(eMusic);
		void PushSFX(eSFX);
		void execQueue();
		
};