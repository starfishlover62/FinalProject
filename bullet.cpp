#include "bullet.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief Construct a new Bullet:: Bullet object using a bool parameter to determine if the bullet is from the tank or an alien. 
 * 
 * @param up 
 */
Bullet::Bullet(bool up, sf::Vector2f position) : Object(position){
    setScale({1,1});
    //mTexture.loadFromFile("./assets/siground.png");
    setTextureFile("./assets/siground.png");
    mAnimation.addFrame(0,0,4,12);
    setTexture();
    // mSprite.setTextureRect(sf::IntRect(0, 0, 4, 12));
    // mSprite.setOrigin(2.f, 6.f);
    mIncrement = sf::Vector2i(12, 12);
    if (up == true)
    {
        friendly = true;
    }
    else
        friendly = false;
}



// void Bullet::draw(sf::RenderTarget& target,sf::RenderStates states) const{
//     target.draw(mSprite,states);
// }

// void Bullet::draw(sf::RenderTarget& target) const{
//     target.draw(mSprite);
// }

void Bullet::moveBulletUp()
{
    setPosition({mPosition.x, mPosition.y -= mIncrement.y});
}

void Bullet::moveBulletDown()
{
     setPosition({mPosition.x, mPosition.y += mIncrement.y});
}



bool Bullet::checkCollision(const Alien* enemy){
    if ((y() >= enemy->y() && y() <= (enemy->y() + enemy->sizeY())) && x() >= enemy->x() && x() <= (enemy->x() + enemy->sizeX())){
        setPosition({-200, -200});
        return true;
    } else {
        return false;
    }
}
