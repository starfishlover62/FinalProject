#include "alien.h"

std::string Alien::textureFile = "./assets/sprites.png";


Alien::Alien(sf::Vector2f position){
    mTextureLocation = nullptr;
    mPosition = position;
    mScale = {0.75,0.75};
    mSprite.setScale(mScale);
    mSprite.setPosition(sf::Vector2f(mPosition));
    mPoints = 0;
    mDead = false;
    mNumFrames = 1;
    mCurrentFrame = 0;
    mRunningFrameTotal = 0;
}


Squid::Squid(sf::Vector2f position) : Alien(position) { 
    
    mNumFrames = 2;
    mTextureLocation = new int[mNumFrames * 4];
    
    mTextureLocation[0] = 0;
    mTextureLocation[1] = 48;
    mTextureLocation[2] = 46;
    mTextureLocation[3] = 94;
    mTextureLocation[4] = 0;
    mTextureLocation[5] = 0;
    mTextureLocation[6] = 46;
    mTextureLocation[7] = 46;
    mPoints = 40;
    setTexture(); 

}


Crab::Crab(sf::Vector2f position) : Alien(position) { 
    mNumFrames = 2;
    mTextureLocation = new int[mNumFrames * 4];

    mTextureLocation[0] = 0;
    mTextureLocation[1] = 98;
    mTextureLocation[2] = 64;
    mTextureLocation[3] = 144;
    mTextureLocation[4] = 0;
    mTextureLocation[5] = 148;
    mTextureLocation[6] = 64;
    mTextureLocation[7] = 194;
    mPoints = 20;
    setTexture(); 
}


Jellyfish::Jellyfish(sf::Vector2f position) : Alien(position) { 
    mNumFrames = 2;
    mTextureLocation = new int[mNumFrames * 4];

    mTextureLocation[0] = 0;
    mTextureLocation[1] = 200;
    mTextureLocation[2] = 70;
    mTextureLocation[3] = 247;
    mTextureLocation[4] = 0;
    mTextureLocation[5] = 250;
    mTextureLocation[6] = 70;
    mTextureLocation[7] = 297;
    mPoints = 10;
    setTexture(); 
}

Alien::~Alien(){
    if (mTextureLocation != nullptr){
        delete [] mTextureLocation;
    }
}



sf::Vector2f Alien::size() const { 
    if(mTextureLocation != nullptr){
        int offset = (4*(mCurrentFrame));
        return sf::Vector2f(mTextureLocation[offset+2]-mTextureLocation[offset+0], 
                            mTextureLocation[offset+3]-mTextureLocation[offset+1]); 
    }
    throw NoTextureSize();
}


int Alien::sizeX() const { 
    if(mTextureLocation != nullptr){
        int offset = (4*(mCurrentFrame));
        return (mScale.x * (mTextureLocation[offset+2]-mTextureLocation[offset+0])); 
    }
    throw NoTextureSize();
}


int Alien::sizeY() const { 
    if(mTextureLocation != nullptr){
        int offset = (4*(mCurrentFrame));
        return (mScale.y * (mTextureLocation[offset+3]-mTextureLocation[offset+1])); 
    }
    throw NoTextureSize();
}



void Alien::moveX(int direction, float distance){
    if(direction < 0){
        mPosition.x -= distance;
        mSprite.setPosition(mPosition);
    } else if(direction > 0){
        mPosition.x += distance;
        mSprite.setPosition(mPosition);
    } else {
        throw InvalidMove();
    }
}



void Alien::moveY(int direction, float distance){
    if(direction < 0){
        mPosition.y -= distance;
        mSprite.setPosition(mPosition);
    } else if(direction > 0){
        mPosition.y += distance;
        mSprite.setPosition(mPosition);
    } else {
        throw InvalidMove();
    }
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
    if(mTextureLocation != nullptr){
        mSprite.setTextureRect(sf::IntRect(mTextureLocation[0],
                                       mTextureLocation[1],
                                       mTextureLocation[2]-mTextureLocation[0],
                                       mTextureLocation[3]-mTextureLocation[1]));
    }
}


void Alien::cycleFrames(){
    ++mRunningFrameTotal;
    mRunningFrameTotal %= (mNumFrames*60);
    mCurrentFrame = mRunningFrameTotal/60;
    int offset = (4*(mCurrentFrame));
    if(mTextureLocation != nullptr){
        mSprite.setTextureRect(sf::IntRect(mTextureLocation[offset+0],
                                       mTextureLocation[offset+1],
                                       mTextureLocation[offset+2]-mTextureLocation[offset+0],
                                       mTextureLocation[offset+3]-mTextureLocation[offset+1]));
    }
}