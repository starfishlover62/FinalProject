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
}


bool Bullet::update(){
    std::cout << "update" << std::endl;
    bool moved = false;
    mTimeSinceLastUpdate += mClock.restart();
    while(mTimeSinceLastUpdate >= mTimePerUpdate){
        std::cout << "Moved (" << mVelocity << ")" << std::endl;
        mTimeSinceLastUpdate -= mTimePerUpdate;
        moveY(mVelocity);
        moved = true;
    }
    return moved;
}


bool FriendlyBullet::checkCollision(const Alien* enemy){
    if ((y() >= enemy->y() && y() <= (enemy->y() + enemy->sizeY())) && x() >= enemy->x() && x() <= (enemy->x() + enemy->sizeX())){
        setPosition({-200, -200});
        return true;
    } else {
        return false;
    }
}

bool EnemyBullet::checkCollision(const Tank* player){
    if ((y() >= player->y() && y() <= (player->y() + player->sizeY())) && x() >= player->x() && x() <= (player->x() + player->sizeX())){
        return true;
    } else {
        return false;
    }
}
