/**
 * @file animation.cpp
 * @author Josh Gillum
 * @brief Function implementations for animation class
 * @version 0.1
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "animation.h"

/**
 * @brief Default animation constructors
 * 
 */
Animation::Animation(){
    // Values of negative one indicate that that they have not been set
    mFrozen = false;
    mNumFrames = -1;    
    mCurrentFrame = -1;
    mRepeatAnimation = false; // Animation will not loop by default
    mAutoUpdate = false; // Animation will be manually cycled by default
    mFinished = false;

    // Time values of zero indicate that they have not been set
    mTimePerAnimation = sf::Time::Zero; 
    mTimePerFrame = sf::Time::Zero;
    mTimeSinceLastUpdate = sf::Time::Zero;
}


/**
 * @brief Appends a frame to the end of the animation. Currently, there is no way to reorder frames,
 * so they must be added in the intended display order
 * 
 * @param startX, starting x coordinate of the frame
 * @param startY, starting y coordinate of the frame
 * @param endX, ending x coodinate of the frame
 * @param endY, ending y coordinate of the frame
 */
void Animation::addFrame(int startX, int startY, int endX, int endY){
    mFrames.push_back(frame(startX,startY,endX,endY)); // Adds frame to vector
    if(mNumFrames <= 0){ // Initialized numFrames and currentFrame if this is the first frame
        mNumFrames = 1;
        mCurrentFrame = 0;
    } else {
        ++mNumFrames;
    }
    updateTimePerFrame(); // Updates the time per frame, necessary since now more frames must be shown in the same amount of time
}


void Animation::enableAnimationRepeat() { 
    mRepeatAnimation = true; 
    mClock.restart();
} 


/**
 * @brief Sets the amount of time that the animation should last
 * 
 * @param time, the total time to elapse for one complete animation
 */
void Animation::setAnimationTime(sf::Time time){
    mAutoUpdate = true; // Because a time is specified for the animation to elapse, it is implicitly set to auto update
    mTimePerAnimation = time;
    if(mNumFrames > 0){ updateTimePerFrame(); }
}


/**
 * @brief Updates the frame based on mAutoUpdate's value. If mAutoUpdate is true, will change the frame every 
 * mTimePerFrame seconds. If mAutoUpdate is false, will change the frame every time the function is called.
 * 
 * @return true, the frame was changed
 * @return false, the frame was not changed (The end of a non-looping animation was reached)
 */
bool Animation::updateFrame(){
    if(!valid()) { throw UnInitializedAnimation(); } // Throws exception if the animation has not been fully initialized
    if(mAutoUpdate){
        mTimeSinceLastUpdate += mClock.restart(); // Stores the time elapsed since the frame was last changed
        bool updated = false; // Tracks whether the frame was changed
        while (mTimeSinceLastUpdate > mTimePerFrame){ // Loops for the number of frames elapsed since the frame was last changed
            mTimeSinceLastUpdate -= mTimePerFrame;
            if(!cycleFrames()){ // Cycles to the next frame in the animation
                return false;
            }
            updated = true;
        }

        return updated;
    } else { // If mAutoUpdate is false (manual updating is in effect)
        if(!cycleFrames()){
            return false;
        }
        return true;
    }
}


/**
 * @brief Moves the animation to the next frame.
 * 
 * @return true, the frame was successfully changed
 * @return false, the frame was not successfully changed (the end of a non-looping animation has been reached)
 */
bool Animation::cycleFrames(){
    if(!valid()) { throw UnInitializedAnimation(); }
    if(!mFinished){
        ++mCurrentFrame;
         if(!mRepeatAnimation){ // If the animation does not loop
            if (mCurrentFrame == mNumFrames){ // Detects whether the end of the animation has been reached
                mFinished = true; 
                return false;
            }
        } else { // Otherwise loops the frame
            mCurrentFrame %= mNumFrames;
        }
        return true;
    }
    return false;
}


/**
 * @brief Returns a rectangle for the current frame
 * 
 * @return sf::IntRect (top-leftX, top-leftY, width, height)
 */
sf::IntRect Animation::getFrame() const {
    if(!valid()) { throw UnInitializedAnimation(); }
    return(sf::IntRect(mFrames[mCurrentFrame].startX,
                       mFrames[mCurrentFrame].startY,
                       mFrames[mCurrentFrame].endX - mFrames[mCurrentFrame].startX,
                       mFrames[mCurrentFrame].endY - mFrames[mCurrentFrame].startY));
}


/**
 * @brief Checks whether the animation has been fully initialized
 * 
 * @return true, the animation has been fully initialized and can be used
 * @return false, the animation has not been fully initialized. Attempting to use it will cause
 * an UnInitializedAnimation exception
 */
bool Animation::valid() const {
    if(mNumFrames == -1) { return false; }
    if(mCurrentFrame == -1) { return false; }
    if(mAutoUpdate){
        if(mTimePerAnimation == sf::Time::Zero) { return false; }
        if(mTimePerFrame == sf::Time::Zero) { return false; }
    }
    return true;
}


/**
 * @brief Resets the animation. Delets all frames and resets time values
 * 
 */
void Animation::clear() {
    mFrames.clear();
    mNumFrames = -1;
    mCurrentFrame = -1;
    mRepeatAnimation = false;
    mFinished = false;
    mTimePerAnimation = sf::Time::Zero;
    mTimePerFrame = sf::Time::Zero;
    mTimeSinceLastUpdate = sf::Time::Zero;
    mAutoUpdate = false;
    mClock.restart();
}


void Animation::freeze(){
    if(!mFrozen){
        mTimeSinceLastUpdate += mClock.restart();
        mFrozen = true;
    }
}


void Animation::unFreeze(){
    if(mFrozen){
        mClock.restart();
        mFrozen = false;
    }
}

