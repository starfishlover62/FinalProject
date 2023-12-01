#include "animation.h"


Animation::Animation(){
    mNumFrames = -1;
    mCurrentFrame = -1;
    mRepeatAnimation = false;
    mFinished = false;
    mTimePerAnimation = sf::Time::Zero;
    mTimePerFrame = sf::Time::Zero;
    mTimeSinceLastUpdate = sf::Time::Zero;
    mManualUpdate = true;

}


void Animation::addFrame(int startX, int startY, int endX, int endY){
    mFrames.push_back(frame(startX,startY,endX,endY));
    if(mNumFrames <= 0){
        mNumFrames = 1;
        mCurrentFrame = 0;
    } else {
        ++mNumFrames;
    }
    updateTimePerFrame();
}

void Animation::setAnimationTime(sf::Time time){
    mManualUpdate = false;
    mTimePerAnimation = time;
    if(mNumFrames > 0){ updateTimePerFrame(); }
}

bool Animation::updateFrame(){
    if(!valid()) { throw UnInitializedAnimation(); }
    if(!mManualUpdate){
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
    } else {
        if(!cycleFrames()){
            return false;
        }
        return true;
    }
}


bool Animation::cycleFrames(){
    if(!valid()) { throw UnInitializedAnimation(); }
    if(!mFinished){
        ++mCurrentFrame;
        if(!mRepeatAnimation){
            if (mCurrentFrame == mNumFrames){ 
                mFinished = true; 
                return false;
            }
        } else {
            mCurrentFrame %= mNumFrames;
        }
        return true;
    }
    return false;
}

sf::IntRect Animation::getFrame() const {
    if(!valid()) { throw UnInitializedAnimation(); }
    return(sf::IntRect(mFrames[mCurrentFrame].startX,
                       mFrames[mCurrentFrame].startY,
                       mFrames[mCurrentFrame].endX - mFrames[mCurrentFrame].startX,
                       mFrames[mCurrentFrame].endY - mFrames[mCurrentFrame].startY));
}


bool Animation::valid() const {
    if(mNumFrames == -1) { return false; }
    if(mCurrentFrame == -1) { return false; }
    if(!mManualUpdate){
        if(mTimePerAnimation == sf::Time::Zero) { return false; }
        if(mTimePerFrame == sf::Time::Zero) { return false; }
    }
    return true;
}

void Animation::clear() {
    mFrames.clear();
    mNumFrames = -1;
    mCurrentFrame = -1;
    mRepeatAnimation = false;
    mFinished = false;
    mTimePerAnimation = sf::Time::Zero;
    mTimePerFrame = sf::Time::Zero;
    mTimeSinceLastUpdate = sf::Time::Zero;
}