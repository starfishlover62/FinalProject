/**
 * @file animation.h
 * @author Josh Gillum
 * @brief Class definition for animation class
 * @version 0.1
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>

/**
 * @brief Represents a single frame of an animation. Stores the top-left and bottom-right coordinates of the frame.
 * 
 */
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

        // Exception Class
        class UnInitializedAnimation{}; // Thrown when animation is used before it has been fully initialized (some values were not set)

        // Constructor
        Animation();

        // Getters
        sf::IntRect getFrame() const; // Returns the current frame information

        bool valid() const; // Returns whether the animation has been fully initialized
        
        // Returns the size of the current frame
        sf::Vector2f size() const { return sf::Vector2f(mFrames[mCurrentFrame].endX - mFrames[mCurrentFrame].startX,
                                                 mFrames[mCurrentFrame].endY - mFrames[mCurrentFrame].startY); }

        int sizeX() const { return mFrames[mCurrentFrame].endX - mFrames[mCurrentFrame].startX; } // Returns the width of the current frame
        int sizeY() const { return mFrames[mCurrentFrame].endY - mFrames[mCurrentFrame].startY; } // Returns the height of the current frame

        int numFrames() const { return mNumFrames; }        // Returns the number of frames in the animation
        bool repeated() const { return mRepeatAnimation; }  // Returns true if the animation loops, false if it doesnt
        bool complete() const { return mFinished; }         // Returns whether the end of the animation has been reached

        // Updating
        void addFrame(int startX, int startY, int endX, int endY); // Adds a frame to the end of the animation
        void setAnimationTime(sf::Time time); // Change the total time that the animation will last for
        bool updateFrame(); // Cycles to the next frame of the animation, depends on auto or manual updating
        
        void enableAnimationRepeat() { mRepeatAnimation = true; }   // Turns on looping of the animation
        void disableAnimationRepeat() { mRepeatAnimation = false; } // Disables looping of the animation
        void enableAutoUpdate() { mAutoUpdate = true; }             // Animation will change frames based on time elapsed
        void disableAutoUpdate() { mAutoUpdate = false; }           // Animation will change frames based on calls to updateFrame

        void resetClock() { mClock.restart(); } // Sets the clock back to zero
        void clear(); // Resets all values of the animation. Erases all frames
        void finish() { mFinished = true; } // Ends the animation

    protected:

        void updateTimePerFrame() { mTimePerFrame = sf::seconds(mTimePerAnimation.asSeconds() / mNumFrames); } // Updates mTimePerFrame
        bool cycleFrames(); // Cycles to the next frame of the animation
    
        int mNumFrames;                 // Number of frames in animation
        int mCurrentFrame;              // Current frame number, starts at 0
        bool mRepeatAnimation;          // True if animation loops, false if it doesn't
        bool mFinished;                 // True if the last frame of a non-looping animation has been cycled past
        bool mAutoUpdate;               // True if frame cycles are based on time, false if based on function callse
        sf::Time mTimePerAnimation;     // Time to elapse for total animation
        sf::Time mTimePerFrame;         // Time to elapse for each frame
        sf::Time mTimeSinceLastUpdate;  // Time elapsed since last frame change
        sf::Clock mClock;               // Stores elapsed time
        std::vector<frame> mFrames;     // Stores all of the frames
};

#endif