#include "AudioManager.hpp"

AudioManager::AudioManager()
{
    Mix_Chunk *temp = Mix_LoadWAV( "resources/high.wav" );
    Mix_Music *muse = Mix_LoadMUS("resources/Rob_Gasser_-_Ricochet.wav");
    Music.push_back(muse);
    SFX.push_back(temp);
}

AudioManager::AudioManager(AudioManager const & src)
{
    *this = src;
}

AudioManager::~AudioManager()
{

}

AudioManager &AudioManager::operator=(AudioManager const & src)
{
    SFX = src.getSFX();
    Music = src.getMusic();
    return (*this);
}

/* void    AudioManager::setMusic(std::vector<Mix_Music*> M)
{
    Music = M;
}

void    AudioManager::setSFX(std::vector<Mix_Chunk*> S)
{
    SFX = S;
} */

void    AudioManager::PlayMusic(int i)
{
    //if( Mix_PausedMusic() == 1 )
    //{
    //    Mix_ResumeMusic();
   // }
    //else
    //{
        Mix_PlayMusic( Music[i], -1 );
   // }
}

std::vector<Mix_Chunk*> AudioManager::getSFX() const
{
    return(this->SFX);
}

std::vector<Mix_Music*> AudioManager::getMusic() const
{
    return(this->Music);
}

void    AudioManager::PauseMusic(int i)
{
    if (Mix_PausedMusic() == 0)
    Mix_PauseMusic();
}

void    AudioManager::PlaySFX(int i)
{
    if (i < SFX.size())
        Mix_PlayChannel( -1, SFX[i], 0 );
}