#include "tank.h"
#include <string>
#include <SFML/Graphics.hpp>


Tank::Tank(int screenWidth, sf::Vector2f position){
    setTextureFile("./assets/sprites.png");
    mAnimation.addFrame(512,931,588,977);
    setTexture();
    // mSprite.setOrigin(40.f, 24.f);
    setPosition(position);
    mScreenWidth = screenWidth;
}


void Tank::setOrigin(float x, float y)
{
    mSprite.setOrigin(x, y);
}

void Tank::moveTankLeft()
{
    if (mPosition.x > 40)
    {
        mPosition.x -= mVelocity;
        mSprite.setPosition(mPosition);
    }
}

void Tank::moveTankRight()
{
    if (mPosition.x < mScreenWidth - 40)
    {
        mPosition.x += mVelocity;
        mSprite.setPosition(mPosition);
    }
}


void Tank::move(float distance){
    if(mPosition.x > 40 && mPosition.x < mScreenWidth - 40){
        moveX(distance);
    }
}

