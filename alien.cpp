#include "alien.h"

int Alien::points = 0;
std::string Alien::textureFile = "./assets/sprites.png";
int Alien::textureLocation [4] {0,0,0,0};


Alien::Alien(sf::Vector2f position){
    mPosition = position;
    mScale = {0.75,0.75};
    mSprite.setScale(mScale);
    mSprite.setPosition(sf::Vector2f(mPosition));
}


Squid::Squid(sf::Vector2f position) : Alien(position) { 
    textureLocation[0] = 60;
    textureLocation[1] = 102;
    textureLocation[2] = 106;
    textureLocation[3] = 148;
    points = 40;
    setTexture(); 
}


Crab::Crab(sf::Vector2f position) : Alien(position) { 
    textureLocation[0] = 51;
    textureLocation[1] = 198;
    textureLocation[2] = 115;
    textureLocation[3] = 244;
    points = 20;
    setTexture(); 
}


Jellyfish::Jellyfish(sf::Vector2f position) : Alien(position) { 
    textureLocation[0] = 48;
    textureLocation[1] = 389;
    textureLocation[2] = 118;
    textureLocation[3] = 436;
    points = 10;
    setTexture(); 
}


void Alien::setLocation(sf::Vector2f position){
    mPosition = position;
    mSprite.setPosition(mPosition);
}


void Alien::draw(sf::RenderTarget& target) const{
    target.draw(mSprite);
}


void Alien::draw(sf::RenderTarget& target,sf::RenderStates states) const{
    target.draw(mSprite,states);
}


void Alien::setTexture(){
    if(!mTexture.loadFromFile(textureFile)){
        throw(loadTextureError(textureFile));
    }
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(textureLocation[0],
                                       textureLocation[1],
                                       textureLocation[2]-textureLocation[0],
                                       textureLocation[3]-textureLocation[1]));
}