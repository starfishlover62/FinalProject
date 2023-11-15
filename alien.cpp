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
}


Squid::Squid(sf::Vector2f position) : Alien(position) { 
    
    mNumFrames = 2;
    mTextureLocation = new int[mNumFrames * 4];
    
    mTextureLocation[0] = 60;
    mTextureLocation[1] = 102;
    mTextureLocation[2] = 106;
    mTextureLocation[3] = 148;
    mTextureLocation[4] = 51;
    mTextureLocation[5] = 198;
    mTextureLocation[6] = 115;
    mTextureLocation[7] = 244;
    mPoints = 40;
    setTexture(); 

}


Crab::Crab(sf::Vector2f position) : Alien(position) { 
    mNumFrames = 2;
    mTextureLocation = new int[mNumFrames * 4];

    mTextureLocation[0] = 51;
    mTextureLocation[1] = 198;
    mTextureLocation[2] = 115;
    mTextureLocation[3] = 244;
    mTextureLocation[4] = 48;
    mTextureLocation[5] = 389;
    mTextureLocation[6] = 118;
    mTextureLocation[7] = 436;
    mPoints = 20;
    setTexture(); 
}


Jellyfish::Jellyfish(sf::Vector2f position) : Alien(position) { 
    mNumFrames = 2;
    mTextureLocation = new int[mNumFrames * 4];

    mTextureLocation[0] = 48;
    mTextureLocation[1] = 389;
    mTextureLocation[2] = 118;
    mTextureLocation[3] = 436;
    mTextureLocation[4] = 60;
    mTextureLocation[5] = 102;
    mTextureLocation[6] = 106;
    mTextureLocation[7] = 148;
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
        return sf::Vector2f(mTextureLocation[2]-mTextureLocation[0], 
                            mTextureLocation[3]-mTextureLocation[1]); 
    }
    throw NoTextureSize();
}


int Alien::sizeX() const { 
    if(mTextureLocation != nullptr){
        return (mScale.x * (mTextureLocation[2]-mTextureLocation[0])); 
    }
    throw NoTextureSize();
}


int Alien::sizeY() const { 
    if(mTextureLocation != nullptr){
        return (mScale.y * (mTextureLocation[3]-mTextureLocation[1])); 
    }
    throw NoTextureSize();
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
    ++mCurrentFrame;
    mCurrentFrame %= (mNumFrames*60);
    int offset = (4*(mCurrentFrame/60));
    if(mTextureLocation != nullptr){
        mSprite.setTextureRect(sf::IntRect(mTextureLocation[offset+0],
                                       mTextureLocation[offset+1],
                                       mTextureLocation[offset+2]-mTextureLocation[offset+0],
                                       mTextureLocation[offset+3]-mTextureLocation[offset+1]));
    }
}