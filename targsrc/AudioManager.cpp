#include "AudioManager.hpp"

AudioManager::AudioManager()
{
    Mix_Chunk *temp = Mix_LoadWAV( "resources/Sounds/high.wav" );
    Mix_Music *muse = Mix_LoadMUS("resources/Sounds/Rob_Gasser_-_Ricochet.wav");
    std::queue<AudioEvent*> empty;
    std::swap( queue, empty );
    Music[START] = muse;
    SFX[EXPLODE] = temp;
}

AudioManager::AudioManager(AudioManager const & src)
{
    *this = src;
}

AudioManager::AudioManager(ConfigEditor &cfg)
{
    Mix_Chunk *temp = Mix_LoadWAV( "resources/Sounds/high.wav" );
    Mix_Music *muse = Mix_LoadMUS("resources/Sounds/Rob_Gasser_-_Ricochet.wav");
    Music[START] = muse;
    SFX[EXPLODE] = temp;
    MasterVol = std::stod(cfg["MasterVolume"].to_str());
    SFXVol = std::stod(cfg["SFXVolume"].to_str());
    MusicVol = std::stod(cfg["MusicVolume"].to_str());
    SFXVolume(SFXVol);
    MusicVolume(MusicVol);
    MasterVolume(MasterVol);

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
void PlaySFX(eSFX track);

void    AudioManager::PlayMusic(eMusic track)
{
    //if( Mix_PausedMusic() == 1 )
    //{
    //    Mix_ResumeMusic();
   // }
    //else
    //{
        Mix_PlayMusic( Music[track], -1 );
   // }
}

std::map<eSFX,Mix_Chunk*>  AudioManager::getSFX() const
{
    return(this->SFX);
}

std::map<eMusic, Mix_Music*> AudioManager::getMusic() const
{
    return(this->Music);
}

void    AudioManager::PauseMusic(eMusic track)
{
    if (Mix_PausedMusic() == 0)
        Mix_PauseMusic();
}

void    AudioManager::PlaySFX(eSFX track)
{
    if (SFX.find(track) != SFX.end())
        Mix_PlayChannel( -1, SFX[track], 0 );
}

void    AudioManager::MusicVolume(double vol)
{
    if (vol >= 0 && vol <= 128)
    {
        Mix_VolumeMusic(round(vol * (MasterVol/100)));
        MusicVol = vol;
    }
}

void    AudioManager::SFXVolume(double vol)
{
    if (vol > 0 && vol < 128)
    {
        Mix_Volume(-1, vol);
        SFXVol = vol;
    }
}

void    AudioManager::MasterVolume(double vol)
{
    if (vol >= 0 && vol <= 100)
    {
        MasterVol = vol;
        double volume = round((vol / 100) * SFXVol);
        Mix_Volume(-1, volume);
        volume = round(MusicVol * (vol / 100));
        Mix_VolumeMusic(volume);
    }
}

void    AudioManager::PushEvent(AudioEvent *e)
{
    queue.push(e);
}

void AudioManager::PushMusic(eMusic music)
{
    AudioEvent *e = new AudioEvent();

    e->music = music;
    e->isMusic = true;
    e->sfx = NOSFX;
    queue.push(e);
}

void AudioManager::PushSFX(eSFX sfx)
{
    AudioEvent *e = new AudioEvent();

    e->sfx = sfx;
    e->isMusic = false;
    e->music = NOMUSIC;
    queue.push(e);
}

void    AudioManager::execQueue()
{
    AudioEvent *temp;

    while(!queue.empty())
    {
       temp = queue.front();
       queue.pop();
        if (temp->isMusic)
        {
            PlayMusic(temp->music);
        }
        else
        {
            PlaySFX(temp->sfx);
        }
        delete (temp);
    }
}