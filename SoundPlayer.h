#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <SFML/Audio.hpp>
#include <string>
#include <thread>

class SoundPlayer
{
    public:
        SoundPlayer();
        bool loadSound(const std::string& filename);
        void playSynchronously();
        void playAsynchronously();

    private:
        sf::SoundBuffer soundBuffer;
        sf::Sound sound;
};

#endif