// Class to handle different animations

#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

struct frame {
    int startX;
    int startY;
    int endX;
    int endY;

    frame(int startX = 0, int startY = 0, int endX = 0, int endY = 0){
        this->startX = startX;
        this->startY = startY;
        this->endX = endX;
        this->endY = endY;
    }
};

class Animation {

    public:

        Animation();

        void addFrame(int startX, int startY, int endX, int endY);

        sf::IntRect getFrame() const;



        int numFrames() const { return mNumFrames; }
        bool repeated() const { return mRepeatAnimation; }
        bool complete() const { return mFinished; }

        bool updateFrame();

    protected:

        void updateTimePerFrame() { mTimePerFrame = sf::seconds(mTimePerAnimation.asSeconds() / mNumFrames); }
        bool cycleFrames();
    
        int mNumFrames;
        int mCurrentFrame; // Current frame, starts at 0
        bool mRepeatAnimation;
        bool mFinished;
        sf::Time mTimePerAnimation;
        sf::Time mTimePerFrame;
        sf::Time mTimeSinceLastUpdate;
        sf::Clock mClock;
        std::vector<frame> mFrames;


    private:



};
#endif