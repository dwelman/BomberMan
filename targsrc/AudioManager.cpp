#include "AudioManager.hpp"

AudioManager::AudioManager()
{

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

}

void    AudioManager::PlaySFX(int i)
{

}