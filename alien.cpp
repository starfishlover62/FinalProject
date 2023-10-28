#include "alien.h"

int Squid::points = 20;
std::string Squid::textureFile = "pngegg.png";
int Squid::textureLocation [4] {60,102,47,47};



Alien::Alien(){
    mPosition = {0,0};
    mScale = {1,1};
}


void Squid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

Squid::Squid(){
    setTexture();
    mSprite.setScale(mScale);
    mSprite.setPosition(sf::Vector2f(mPosition));
}


void Squid::setTexture(){
    if(!mTexture.loadFromFile(textureFile)){
        std::cout <<"Error opening file" << std::endl;
        exit(1);
    }
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(textureLocation[0],textureLocation[1],textureLocation[2],textureLocation[3]));
}