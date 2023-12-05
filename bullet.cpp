#include "bullet.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief Construct a new Bullet:: Bullet object using a bool parameter to determine if the bullet is from the tank or an alien. 
 * 
 * @param up 
 */
Bullet::Bullet(sf::Vector2f position, double velocity) : Object(position){
    setTextureFile("./assets/siground.png");
    mAnimation.addFrame(0,0,4,12);
    setTexture();
    mClock.restart();
    mTimePerUpdate = sf::seconds(0.01);
    mTimeSinceLastUpdate = sf::Time::Zero;
    mVelocity = velocity;
    mFrozen = false;
}


bool Bullet::update(){
    // std::cout << "update" << std::endl;
    bool moved = false;
    mTimeSinceLastUpdate += mClock.restart();
    while(mTimeSinceLastUpdate >= mTimePerUpdate){
        // std::cout << "Moved (" << mVelocity << ")" << std::endl;
        mTimeSinceLastUpdate -= mTimePerUpdate;
        moveY(mVelocity);
        moved = true;
    }
    return moved;
}

void Bullet::reset(){
    mClock.restart();
    mTimeSinceLastUpdate = sf::Time::Zero;
}


bool FriendlyBullet::checkCollision(const Alien* enemy) const{
    if ((y() >= enemy->y() && y() <= (enemy->y() + enemy->sizeY())) && 
         x() >= enemy->x() && x() + sizeX() <= (enemy->x() + enemy->sizeX())){
        return true;
    } else {
        return false;
    }
}

bool EnemyBullet::checkCollision(const Tank* player) const{
    if ((y() >= player->y() && y() <= (player->y() + player->sizeY())) && 
         x() >= player->x() && x() + sizeX() <= (player->x() + player->sizeX())){
        return true;
    } else {
        return false;
    }
}


void Bullet::freeze(){
    if(!mFrozen){
        mTimeSinceLastUpdate += mClock.restart();
        mFrozen = true;
    }
}


void Bullet::unFreeze(){
    if(mFrozen){
        mClock.restart();
        mFrozen = false;
    }
}


