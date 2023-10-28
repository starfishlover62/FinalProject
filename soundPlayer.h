#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

class SoundPlayer
{
    public:
        SoundPlayer() {}

        bool loadSound(const std::string& filename);

        void playSynchronously();

        void playAsynchronously()
        {
            std::thread soundThread(&SoundPlayer::playSynchronously, this);
            soundThread.detach();
        }

    private:
        sf::SoundBuffer soundBuffer;
        sf::Sound sound;
};

#endif