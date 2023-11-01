#include "alien.h"

int Squid::points = 40;
int Crab::points = 20;
int Jellyfish::points = 10;

std::string Squid::textureFile = "./assets/sprites.png";
std::string Crab::textureFile = "./assets/sprites.png";
std::string Jellyfish::textureFile = "./assets/sprites.png";

int Squid::textureLocation [4] {60,102,47,47};
int Crab::textureLocation [4] {60,102,47,47};
int Jellyfish::textureLocation [4] {60,102,47,47};


Alien::Alien(sf::Vector2f position){
    mPosition = position;
    mScale = {1,1};
    mSprite.setScale(mScale);
    mSprite.setPosition(sf::Vector2f(mPosition));
}

void Alien::setLocation(sf::Vector2f position){
    mPosition = position;
    mSprite.setPosition(mPosition);
}


void Alien::draw(sf::RenderTarget& target,sf::RenderStates states) const{
    target.draw(mSprite,states);
}


void Squid::setTexture(){
    if(!mTexture.loadFromFile(textureFile)){
        exit(1);
    }
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(textureLocation[0],textureLocation[1],textureLocation[2],textureLocation[3]));
}

void Crab::setTexture(){
    if(!mTexture.loadFromFile(textureFile)){
        exit(1);
    }
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(textureLocation[0],textureLocation[1],textureLocation[2],textureLocation[3]));
}

void Jellyfish::setTexture(){
    if(!mTexture.loadFromFile(textureFile)){
        exit(1);
    }
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(textureLocation[0],textureLocation[1],textureLocation[2],textureLocation[3]));
}