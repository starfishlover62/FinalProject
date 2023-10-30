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

void Tank::moveTankRight()
{
    if (mPosition.x < 760)
    {
        mPosition.x += mIncrement.y;
        mSprite.setPosition(mPosition);
    }
}

