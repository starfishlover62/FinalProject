/**
 * @file alien.cpp
 * @author Josh Gillum
 * @brief Function implementations for Alien and child classes
 * @version 0.1
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "alien.h"


/**
 * @brief Alien constructor
 * 
 * @param position the starting position of the sprite. Default is (0,0)
 */
Alien::Alien(sf::Vector2f position){
    mTextureFile = "./assets/sprites.png";
    mPosition = position;
    mScale = {0.75,0.75};
    mSprite.setScale(mScale);
    mSprite.setPosition(sf::Vector2f(mPosition));
    mPoints = 0;
    mDead = false;
}


/**
 * @brief Squid constructor
 * 
 * @param position the starting position of the sprite. Default is (0,0)
 */
Squid::Squid(sf::Vector2f position) : Alien(position) { 
    mAnimation.addFrame(0,48,46,94); // Frame one of animation
    mAnimation.addFrame(0,0,46,46); // Frame two
    mAnimation.enableAnimationRepeat(); // Causes the animation to loop
    mPoints = 40;
    setTexture(); 
}

/**
 * @brief Crab constructor
 * 
 * @param position the starting position of the sprite. Default is (0,0)
 */
Crab::Crab(sf::Vector2f position) : Alien(position) { 
    mAnimation.addFrame(0,98,64,144);
    mAnimation.addFrame(0,148,64,194);
    mAnimation.enableAnimationRepeat();
    mPoints = 20;
    setTexture(); 
}


/**
 * @brief Jellyfish constructor
 * 
 * @param position the starting position of the sprite. Default is (0,0)
 */
Jellyfish::Jellyfish(sf::Vector2f position) : Alien(position) { 
    mAnimation.addFrame(0,200,70,247);
    mAnimation.addFrame(0,250,70,297);
    mAnimation.enableAnimationRepeat();
    mPoints = 10;
    setTexture(); 
}


/**
 * @brief UFO constructor
 * 
 * @param position 
 * @param velocity 
 */
UFO::UFO(sf::Vector2f position, sf::Vector2f velocity) : Alien(position){
    std::srand(std::time(0));
    mPoints = 3 + (rand() % 7);
    mPoints *= 100;
    mAnimation.addFrame(100,0,253,67);
    mAnimation.enableAnimationRepeat();
    mScale = {0.50,0.50};
    mSprite.setScale(mScale);
    setTexture();
    mVelocity = velocity;
}


/**
 * @brief Returns the size of the sprite in its current animation frame
 * 
 * @return sf::Vector2f Vector representation of the size
 */
sf::Vector2f Alien::size() const { 
    if(mAnimation.valid()){
        return mAnimation.size(); // Gets the size of sprite's current animation frame
    }
    throw Animation::UnInitializedAnimation(); // Thrown when the animation was not properly initialized
}


/**
 * @brief Returns the width of the sprite in its current animation frame
 * 
 * @return int width of sprite
 */
int Alien::sizeX() const { 
    if(mAnimation.valid()){
        return mAnimation.sizeX() * mScale.x;
    }
    throw Animation::UnInitializedAnimation();
}


/**
 * @brief Returns the height of the sprite in its current animation frame
 * 
 * @return int height of sprite
 */
int Alien::sizeY() const { 
    if(mAnimation.valid()){
        return mAnimation.sizeY() * mScale.y;
    }
    throw Animation::UnInitializedAnimation();
}


/**
 * @brief Moves the alien along the x-axis
 * 
 * @param distance Number of pixels to move
 * @param direction positive value to move right, negative value to move left, a zero value will throw InvalidMove exception
 *  Default direction is right
 */
void Alien::moveX(float distance, int direction){
    if(direction < 0){
        mPosition.x -= distance;
        mSprite.setPosition(mPosition);
    } else if(direction > 0){
        mPosition.x += distance;
        mSprite.setPosition(mPosition);
    } else { // Direction is not specified
        throw InvalidMove();
    }
}


/**
 * @brief Moves the alien along the y-axis
 * 
 * @param distance Number of pixels to move
 * @param direction positive value to move up, negative value to move down, a zero value will throw InvalidMove exception
 *  Default direction is up
 */
void Alien::moveY(float distance, int direction){
    if(direction < 0){
        mPosition.y -= distance;
        mSprite.setPosition(mPosition);
    } else if(direction > 0){
        mPosition.y += distance;
        mSprite.setPosition(mPosition);
    } else {
        throw InvalidMove();
    }
}


/**
 * @brief Sets the position of the alien
 * 
 * @param position, vector of the alien's position
 */
void Alien::setPosition(sf::Vector2f position){
    mPosition = position;
    mSprite.setPosition(mPosition);
}


/**
 * @brief Applies the texture member to the sprite member. Throws loadTextureError if the 
 * path stored in mTextureFile does not exist. Before calling this function, use 
 * setTextureFile(std::string path) to set the path to the texture file
 * 
 */
void Alien::setTexture(){
    if(!mTexture.loadFromFile(mTextureFile)){
        throw(loadTextureError(mTextureFile)); // Thrown when the file does not exist
    }
    mSprite.setTexture(mTexture); // Applies the texture to the sprite
    if(mAnimation.valid()){ // checks if an animation has been set up
        mSprite.setTextureRect(mAnimation.getFrame()); // gets the texture rectangle for the current frame
    }
}


/**
 * @brief Changes the frame of the animation
 * 
 * @return true, the frame was changed
 * @return false, the frame was not changed
 */
bool Alien::cycleFrames(){
    if(mAnimation.valid()){
        if(!mAnimation.updateFrame()){ // Checks if the frame was changed
            return false;
        }
        mSprite.setTextureRect(mAnimation.getFrame());
        return true;
    }
    return false; // The animation was either not valid, or the frame was not changed
}


/**
 * @brief Kills the alien, triggering the explosion animation
 * 
 */
void Alien::kill(){
    mDead = true;
    mTextureFile = "./assets/explosion.png";
    mSprite.setPosition(sf::Vector2f(mPosition.x - sizeX()/6.0, mPosition.y - sizeY()/2.5)); // Moves the explosion to be centered
    mAnimation.clear(); // Resets the animation

    // Adds all of the frames of the explosion animation to mAnimation
    for(int row = 0; row < 6; ++row){
        for(int col = 0; col < 8; ++col){
            if(row != 5 && col != 7){
                mAnimation.addFrame((col*100)+1,(row*100)+1,(col+1)*100,(row+1)*100);
            }
        }
    }

    mAnimation.enableAutoUpdate(); // Frames will change based on time elapsed, not calls to update
    mAnimation.disableAnimationRepeat(); // Animation will not loop
    mAnimation.setAnimationTime(sf::seconds(1.5)); // Time entire animation will last for
    mAnimation.resetClock(); // Resets the clock for tracking time elapsed
    setTexture();
}


void UFO::hide() {
    mDead = true;
}