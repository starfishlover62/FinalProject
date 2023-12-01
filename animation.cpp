#include "animation.h"


Animation::Animation(){
    mNumFrames = -1;
    mCurrentFrame = -1;
    mRepeatAnimation = false;
    mFinished = false;
    mTimePerAnimation = sf::Time::Zero;
    mTimePerFrame = sf::Time::Zero;
    mTimeSinceLastUpdate = sf::Time::Zero;

}


void Animation::addFrame(int startX, int startY, int endX, int endY){
    mFrames.push_back(frame(startX,startY,endX,endY));
    ++mNumFrames;
    updateTimePerFrame();
}

bool Animation::updateFrame(){
    mTimeSinceLastUpdate += mClock.restart();
    bool updated = false;
    while (mTimeSinceLastUpdate > mTimePerFrame){
        mTimeSinceLastUpdate -= mTimePerFrame;
        if(!cycleFrames()){
            return false;
        }
        updated = true;
    }

    return updated;
}


bool Animation::cycleFrames(){
    if(!mFinished){
        ++mCurrentFrame;
        if(!mRepeatAnimation && mCurrentFrame == mNumFrames){ 
            mFinished = true; 
            return false;
        }
        return true;
    }
    return false;
}

sf::IntRect Animation::getFrame() const {
    return(sf::IntRect(mFrames[mCurrentFrame].startX,
                       mFrames[mCurrentFrame].startY,
                       mFrames[mCurrentFrame].endX - mFrames[mCurrentFrame].startX,
                       mFrames[mCurrentFrame].endY - mFrames[mCurrentFrame].startY));
}