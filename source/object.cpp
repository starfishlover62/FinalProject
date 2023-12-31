/**
 * @file object.cpp
 * @author Josh Gillum
 * @brief Function implementations for object class
 * @version 1.0
 * @date 2023-12-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "object.h"

/**
 * @brief Object constructor, sets position and scale
 * 
 * @param position, the position to place the object at, default is (0,0)
 */
Object::Object(sf::Vector2f position){
    mPosition = position;
    mTextureFile = "";
    setScale({1,1});
}


/**
 * @brief Returns the size of the sprite in its current animation frame
 * 
 * @return sf::Vector2f Vector representation of the size
 */
sf::Vector2f Object::size() const { 
    if(mAnimation.valid()){
        return {mAnimation.sizeX() * mScale.x,mAnimation.sizeY() * mScale.y}; // Gets the size of sprite's current animation frame
    }
    throw Animation::UnInitializedAnimation(); // Thrown when the animation was not properly initialized
}


/**
 * @brief Returns the width of the sprite in its current animation frame
 * 
 * @return int width of sprite
 */
int Object::sizeX() const { 
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
int Object::sizeY() const { 
    if(mAnimation.valid()){
        return mAnimation.sizeY() * mScale.y;
    }
    throw Animation::UnInitializedAnimation();
}


/**
 * @brief Sets the position of the alien
 * 
 * @param position, vector of the alien's position
 */
void Object::setPosition(sf::Vector2f position){
    mPosition = position;
    mSprite.setPosition(mPosition);
}

/**
 * @brief Moves the sprite along both axes
 * 
 * @param distance Number of pixels to move
 *  Positive x values move right, negative values move left
 *  Positive y values move down, negative value move up
 */
void Object::move(sf::Vector2f distance){
    mPosition.x += distance.x;
    mPosition.y += distance.y;
    mSprite.setPosition(mPosition);
}


/**
 * @brief Moves the sprite along the x-axis
 * 
 * @param distance Number of pixels to move
 * Positive values move right, negative values move left
 */
void Object::moveX(float distance){
    mPosition.x += distance;
    mSprite.setPosition(mPosition);
}


/**
 * @brief Moves the sprite along the y-axis
 * 
 * @param distance Number of pixels to move 
 *  Positive values move down, negative values move up
 */
void Object::moveY(float distance){
    mPosition.y += distance;
    mSprite.setPosition(mPosition);
}


/**
 * @brief Sets the position of the alien
 * 
 * @param position, vector of the alien's position
 */
void Object::setScale(sf::Vector2f scale){
    mScale = scale;
    mSprite.setScale(mScale);
}


/**
 * @brief Changes the frame of the animation
 * 
 * @return true, the frame was changed
 * @return false, the frame was not changed
 */
bool Object::cycleFrames(){
    if(mAnimation.valid()){
        if(!mAnimation.updateFrame()){ // Checks if the frame was changed
            return false;
        }
        mSprite.setTextureRect(mAnimation.getFrame());
        return true;
    }
    throw Animation::UnInitializedAnimation(); // The animation was either not valid, or the frame was not changed
}


/**
 * @brief Applies the texture member to the sprite member. Throws loadTextureError if the 
 * path stored in mTextureFile does not exist. Before calling this function, use 
 * setTextureFile(std::string path) to set the path to the texture file
 * 
 */
void Object::setTexture(){
    if(!mTexture.loadFromFile(mTextureFile)){
        throw(loadTextureError(mTextureFile)); // Thrown when the file does not exist
    }
    mSprite.setTexture(mTexture); // Applies the texture to the sprite
    if(mAnimation.valid()){ // checks if an animation has been set up
        mSprite.setTextureRect(mAnimation.getFrame()); // gets the texture rectangle for the current frame
    } else {
        throw Animation::UnInitializedAnimation();
    }
}