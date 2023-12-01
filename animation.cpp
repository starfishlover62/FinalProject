#include "animation.h"




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
        cycleFrames();
        updated = true;
        if(mFinished){
            return updated;
        }
    }

    return updated;
}


void Animation::cycleFrames(){
    if(!mFinished){
        ++mCurrentFrame;
        if(!mRepeatAnimation && mCurrentFrame == mNumFrames){ mFinished = true; }
    }
    
}