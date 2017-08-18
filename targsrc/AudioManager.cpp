#include "AudioManager.hpp"

AudioManager::AudioManager()
{
    Mix_Chunk *temp = Mix_LoadWAV( "resources/Sounds/high.wav" );
    Mix_Music *muse = Mix_LoadMUS("resources/Sounds/Rob_Gasser_-_Ricochet.wav");
    std::queue<AudioEvent*> empty;
    std::swap( queue, empty );
    Music.push_back(muse);
    SFX.push_back(temp);
}

AudioManager::AudioManager(AudioManager const & src)
{
    *this = src;
}

AudioManager::AudioManager(ConfigEditor &cfg)
{
    Mix_Chunk *temp = Mix_LoadWAV( "resources/Sounds/high.wav" );
    Mix_Music *muse = Mix_LoadMUS("resources/Sounds/Rob_Gasser_-_Ricochet.wav");
    Music.push_back(muse);
    SFX.push_back(temp);
    int vol = std::stoi(cfg["MasterVolume"].to_str());
    SFXVol = vol;
    MasterVol = vol;
    SFXVolume(vol);
    MusicVolume(vol);

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

void    AudioManager::MusicVolume(int vol)
{
    if (vol >= 0 && vol <= 100)
        Mix_VolumeMusic(vol);
}

void    AudioManager::SFXVolume(int vol)
{
    if (vol >= 0 && vol <= 100)
        Mix_Volume(-1, vol);
}

void    AudioManager::MasterVolume(int vol)
{
    if (vol >= 0 && vol <= 100)
    {
        Mix_VolumeMusic(vol);
        Mix_Volume(-1, vol);
    }
}

void    AudioManager::PushEvent(bool sound, int position)
{
    AudioEvent event = {sound, position};
    queue.push(&event);
}

void    AudioManager::execQueue()
{
    AudioEvent *temp;

    while(!queue.empty())
    {
       temp = queue.front();
       queue.pop();
        if (temp->type)
        {
           PlayMusic(temp->pos);
        }
        else
        {
            PlaySFX(temp->pos);
        }
    }
}