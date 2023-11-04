#include "bullet.h"
#include <string>
#include <SFML/Graphics.hpp>

/**
 * @brief Construct a new Bullet:: Bullet object using a bool parameter to determine if the bullet is from the tank or an alien. 
 * 
 * @param up 
 */
Bullet::Bullet(bool up){
    mScale = {1,1};
    mTexture.loadFromFile("./assets/siground.png");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 4, 12));
    mSprite.setOrigin(2.f, 6.f);
    mIncrement = sf::Vector2i(4, 4);
    if (up == true)
    {
        friendly = true;
    }
    else
        friendly = false;
}

void Bullet::setLocation(sf::Vector2f position){
    mPosition = position;
    mSprite.setPosition(mPosition);
}


void Bullet::draw(sf::RenderTarget& target,sf::RenderStates states) const{
    target.draw(mSprite,states);
}

void Bullet::moveBulletUp()
{
    mPosition.y -= mIncrement.y;
    mSprite.setPosition(mPosition);
}

