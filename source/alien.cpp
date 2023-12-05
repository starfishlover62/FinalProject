/**
 * @file alien.cpp
 * @author Josh Gillum
 * @brief Function implementations for Alien and child classes
 * @version 1.0
 * @date 2023-12-05
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
Alien::Alien(sf::Vector2f position) : Object(position){
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
    spawn(position,velocity);
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

/**
 * @brief Hides the UFO. Simply sets the mDead value, without going through the explosion animation
 * 
 */
void UFO::hide() {
    mDead = true;
}


/**
 * @brief Spawns in a UFO (does the job of the constructor) (Resets all the values)
 * 
 * @param position, the position to spawn the UFO at
 * @param velocity, the velocity of the UFO
 */
void UFO::spawn(sf::Vector2f position, sf::Vector2f velocity){
    mDead = false;
    std::srand(std::time(0));

    // Points can be from 300-1000
    mPoints = 3 + (rand() % 7); 
    mPoints *= 100;

    // Sets the position, scale, and velocity
    mPosition = position;
    mSprite.setPosition(position);
    mScale = {0.50,0.50};
    mSprite.setScale(mScale);
    mVelocity = velocity;

    // Adds the animation frame
    mTextureFile = "./assets/sprites.png";
    mAnimation.clear();
    mAnimation.addFrame(100,0,253,67);
    mAnimation.enableAnimationRepeat();
    setTexture();
}