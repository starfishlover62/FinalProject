/**
 * @file player.cpp
 * @author Josh Gillum
 * @brief Function implementations for player class
 * @version 0.1
 * @date 2023-12-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "player.h"

/**
 * @brief Player object constructor
 * 
 * @param screenWidth, the width of the screen, in pixels
 * @param screenHeight, the height of the screen in pixels
 * @param name, the name of the player
 */
Player::Player(int screenWidth,int screenHeight, PlayerName name){
    
    // Screen dimensions
    mScreenWidth = screenWidth;
    mScreenHeight = screenHeight;

    // Initializes lives and lives graphic
    mLives = 3;
    for(int i = 0; i < mLives; ++i){
        mTankLives.push_back(new Tank(mScreenWidth,{690+(50.f*i), 10}));
        float initialTankLifeScale = 0.5f; // Adjust this value as needed
        mTankLives[i]->setScale({initialTankLifeScale, initialTankLifeScale});
    }

    // Creates new objects
    mTank = new Tank(mScreenWidth);
    mBullet = new FriendlyBullet({mTank->x(),mTank->y()},-8.0);
    mHud = new Gameboard(name.getPlayerName(),0);
    mBulletVisible = false;
    
    // Movement related variables
    mMoving = false;
    mVelocity = 2;
    mTimeSinceLastUpdate = sf::Time::Zero;
    mTimePerUpdate = sf::seconds(0.01);
    mClock.restart();
    mFrozen = false;

    // Invincibility related variables
    mInv = false;
    mIClock.restart();
    mTimeI = sf::Time::Zero;
    mTimeIFrames = sf::seconds(2);
}

/**
 * @brief Deallocates all memory. Does the job of the destructor
 * 
 */
void Player::clear(){
    // Deletes the player tank
    if(mTank != nullptr){
        delete mTank;
    }

    // Deletes the hud
    if(mHud != nullptr){
        delete mHud;
    }

    // Deletes the remaining tankLives objects
    for(unsigned i = 0; i < mTankLives.size(); ++i){
        if(mTankLives[i] != nullptr){
            delete mTankLives[i];
        }
    }

    // Deletes the bullet
    if(mBullet != nullptr){
        delete mBullet;
    }
}

/**
 * @brief Draws the tank, hud, tankLives, and bullet (if visible)
 * 
 * @param target, the target window to draw to
 */
void Player::draw(sf::RenderTarget& target) const {
    mTank->draw(target);
    mHud->draw(target);
    if(mBulletVisible){
        mBullet->draw(target);
    }
    std::for_each(mTankLives.begin(),mTankLives.end(),[&target](const Tank* t){t->draw(target);});
}


/**
 * @brief Draws the tank, hud, tankLives, and bullet (if visible)
 * 
 * @param target, the target window to draw to
 * @param states, the renderStates of the window
 */
void Player::draw(sf::RenderTarget& target,sf::RenderStates states) const {
    mTank->draw(target,states);
    mHud->draw(target,states);
    if(mBulletVisible){
        mBullet->draw(target,states);
    }
    std::for_each(mTankLives.begin(),mTankLives.end(),[&target,&states](const Tank* t){t->draw(target,states);});
}

/**
 * @brief Sets the moving boolean true. If the player just started moving, resets the movement clock
 * 
 */
void Player::moving() { 
    if(!mMoving){
        mMoving = true; 
        mClock.restart();
        mTimeSinceLastUpdate = sf::Time::Zero;
    }
}


/**
 * @brief Sets the moving boolean to false. If the player just stopped moving, resets the movement clock
 * 
 */
void Player::noMoving() { 
    if(mMoving){
        mMoving = false; 
        mClock.restart();
        mTimeSinceLastUpdate = sf::Time::Zero;
    }
}


/**
 * @brief Controls the movement of the bullet, as well as the invincibility of the tank
 * 
 */
void Player::update(){
    if(!mFrozen){ // Nothing will update if the player is frozen
        if(mInv){
            mTimeI += mIClock.restart(); // Tracks time invincible for
            if(mTimeI >= mTimeIFrames) { // If the player has been invincible long enough
                mInv = false; // Turn off invincibility
                mTank->noBlink(); // Stop having the tank blink
            } else {
                mTank->cycleFrames(); // Otherwise changes the frame of the tank
            }

        }
        if(mBulletVisible){ // If the bullet is to visible
            mBullet->update(); // Moves the bullet
            if(mBullet->y() < 5){ // Checks if it is off the screen
                mBulletVisible = false;
            }
        }
    }
}


/**
 * @brief Updates the object based on the events that happen. Currently detects if a key is released,
 * if will set the movement boolean to false
 * 
 * @param event, the event that happend
 * @param window, the window the event happened in
 */
void Player::update(sf::Event& event, sf::RenderWindow& window){
    if(event.type == sf::Event::KeyReleased){
        if((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) ||
           (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)){
            noMoving();
        }
    }
}


/**
 * @brief Moves the tank
 * 
 * @param right, true if the tank is to move right, false if it is to move left
 */
void Player::move(bool right){
    if(!mFrozen){ // Nothing will happen if the player is frozen
        mTimeSinceLastUpdate += mClock.restart();
        while(mTimeSinceLastUpdate > mTimePerUpdate){
            mTimeSinceLastUpdate -= mTimePerUpdate;
            float pos = mTank->x(); // Current position of the tank
            if(right){
                if(pos + mTank->sizeX() + 2 < mScreenWidth){
                    mTank->moveX(mVelocity);
                }
            } else {
                if(pos > 2){
                    mTank->moveX(-mVelocity);
                }
            }
        }
    }
}


/**
 * @brief Shoots a bullet from the tank, if allowed to
 * 
 * @return true, a bullet was shot
 * @return false, a bullet was not shot
 */
bool Player::shoot(){
    if(!mFrozen && !mInv){ // Can not shoot bullets if the player is frozen or invincible
        if(!mBulletVisible){
            mBulletVisible = true;
            mBullet->setPosition({mTank->x() + (mTank->sizeX()/2), mTank->y()}); // Moves the bullet to the tank
            mBullet->reset(); // Resets the bullet's movement clock
            return true;
        }
    }
    return false;
}


/**
 * @brief Returns a pointer constant to the player's bullet
 * 
 * @return const FriendlyBullet*, the bullet object of the player. Returns nullptr if the bullet is not visible
 */
const FriendlyBullet* Player::bulletPtr() const{
    if(mBulletVisible){
        return mBullet;
    } else {
        return nullptr;
    }
}


/**
 * @brief Returns a pointer constant to the player tank
 * 
 * @return const Tank*, the tank object of the player. Returns nullptr if the player is currently invincible
 */
const Tank* Player::tankPtr() const{
    if(!mInv){
        return mTank;
    }
    return nullptr;
}


/**
 * @brief Decrements the player's lives
 * 
 * @return true, the player lost a life and is still alive
 * @return false, the player lost a life and is now dead
 */
bool Player::loseLife() {
    if(mLives > 1){
        --mLives;
        // Removes one of the tanks from the lives graphic
        if(mTankLives[mTankLives.size()-1] != nullptr){
            delete mTankLives[mTankLives.size()-1];
            mTankLives.pop_back();
        }

        // Sets invincibility
        mInv = true;
        mIClock.restart();
        mTimeI = sf::Time::Zero;
        mTank->blink(); // Updates the tank's animation 
        return true;
    }
    if(mLives == 1){ // If the last life was lost
        --mLives;
        // Deletes the last tank from the graphic
        if(mTankLives[mTankLives.size()-1] != nullptr){
            delete mTankLives[mTankLives.size()-1];
            mTankLives.pop_back();
        }
        // Does not return true, will return false
    }
    return false;
}


/**
 * @brief Freezes the player clocks
 * 
 */
void Player::freeze(){
    if(!mFrozen){
        mTimeSinceLastUpdate += mClock.restart();
        mFrozen = true;
        mTank->freeze();
        mBullet->freeze();
    }
}


/**
 * @brief Unfreezes the player clocks
 * 
 */
void Player::unFreeze(){
    if(mFrozen){
        mClock.restart();
        mFrozen = false;
        mTank->unFreeze();
        mBullet->unFreeze();
    }
}