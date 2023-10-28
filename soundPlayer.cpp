#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() {}

bool SoundPlayer::loadSound(const std::string& filename)
{
    if (soundBuffer.loadFromFile(filename)) {
        sound.setBuffer(soundBuffer);
        return true;
    }
    return false;
}

void SoundPlayer::playSynchronously()
{
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing)
    {
        // plays entire sound before continuing
    }
}

void SoundPlayer::playAsynchronously()
{
    std::thread soundThread(&SoundPlayer::playSynchronously, this);
    soundThread.detach();
}

