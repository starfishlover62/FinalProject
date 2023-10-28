#include "alien.h"

int Squid::points = 20;
std::string Squid::textureFile = "./assets/sprites.png";
int Squid::textureLocation [4] {160,102,47,47};


Alien::Alien(sf::Vector2f position){
    mPosition = position;
    mScale = {1,1};
}

void Alien::setLocation(sf::Vector2f position){
    mPosition = position;
    mSprite.setPosition(mPosition);
}


void Alien::draw(sf::RenderTarget& target,sf::RenderStates states) const{
    target.draw(mSprite,states);
}


Squid::Squid(sf::Vector2f position) : Alien(position) {
    setTexture();
    mSprite.setScale(mScale);
    mSprite.setPosition(sf::Vector2f(mPosition));
}


void Squid::setTexture(){
    if(!mTexture.loadFromFile(textureFile)){
        exit(1);
    }
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(textureLocation[0],textureLocation[1],textureLocation[2],textureLocation[3]));
}