#include "tank.h"
#include <string>
#include <SFML/Graphics.hpp>


Tank::Tank(){
    mScale = {1,1};
    mTexture.loadFromFile("./assets/sprites.png");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(510, 930, 80, 48));
    mSprite.setOrigin(40.f, 24.f);
    mPosition={400, 750};
    mSprite.setPosition(mPosition);
    mIncrement = sf::Vector2i(4, 4);
}

void Tank::setLocation(sf::Vector2f position){
    mPosition = position;
    mSprite.setPosition(mPosition);
}

void Tank::setOrigin(float x, float y)
{
    mSprite.setOrigin(x, y);
}

void Tank::setScale(float factorX, float factorY) {
    mScale.x = factorX;
    mScale.y = factorY;
    mSprite.setScale(mScale);
}

void Tank::draw(sf::RenderTarget& target,sf::RenderStates states) const{
    target.draw(mSprite,states);
}

void Tank::moveTankLeft()
{
    if (mPosition.x > 40)
    {
        mPosition.x -= mIncrement.x;
        mSprite.setPosition(mPosition);
    }
}

void Tank::moveTankRight(const float SCREEN_RES_X)
{
    if (mPosition.x < SCREEN_RES_X - 40)
    {
        mPosition.x += mIncrement.y;
        mSprite.setPosition(mPosition);
    }
}

