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
        void setAnimationTime(sf::Time time);
        void setAnimationRepeat(bool repeat) { mRepeatAnimation = repeat; }

        sf::IntRect getFrame() const;

        bool valid() const;
        
        sf::Vector2f size() const { return sf::Vector2f(mFrames[mCurrentFrame].endX - mFrames[mCurrentFrame].startX,
                                                 mFrames[mCurrentFrame].endY - mFrames[mCurrentFrame].startY); }

        int sizeX() const { return mFrames[mCurrentFrame].endX - mFrames[mCurrentFrame].startX; }
        int sizeY() const { return mFrames[mCurrentFrame].endY - mFrames[mCurrentFrame].startY; }

        int numFrames() const { return mNumFrames; }
        bool repeated() const { return mRepeatAnimation; }
        bool complete() const { return mFinished; }

        bool updateFrame();

        class UnInitializedAnimation{};

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