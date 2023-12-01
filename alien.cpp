#include "alien.h"

std::string Alien::textureFile = "./assets/sprites.png";


Alien::Alien(sf::Vector2f position, int frameRate){
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
    mFrameRate = frameRate;

    mAnimation.setAnimationTime(sf::seconds(static_cast<double>(2)));
}


Squid::Squid(sf::Vector2f position, int frameRate) : Alien(position,frameRate) { 
    
    mNumFrames = 2;
    mTextureLocation = new int[mNumFrames * 4];

    mAnimation.addFrame(0,48,46,94);
    mAnimation.addFrame(0,0,46,46);
    mAnimation.setAnimationRepeat(true);
    
    /*
    mTextureLocation[0] = 0;
    mTextureLocation[1] = 48;
    mTextureLocation[2] = 46;
    mTextureLocation[3] = 94;
    mTextureLocation[4] = 0;
    mTextureLocation[5] = 0;
    mTextureLocation[6] = 46;
    mTextureLocation[7] = 46;
    */
    mPoints = 40;
    setTexture(); 

}


Crab::Crab(sf::Vector2f position, int frameRate) : Alien(position,frameRate) { 
    mNumFrames = 2;
    mTextureLocation = new int[mNumFrames * 4];

    mAnimation.addFrame(0,98,64,144);
    mAnimation.addFrame(0,148,64,194);
    mAnimation.setAnimationRepeat(true);

    /*
    mTextureLocation[0] = 0;
    mTextureLocation[1] = 98;
    mTextureLocation[2] = 64;
    mTextureLocation[3] = 144;
    mTextureLocation[4] = 0;
    mTextureLocation[5] = 148;
    mTextureLocation[6] = 64;
    mTextureLocation[7] = 194;
    */
    mPoints = 20;
    setTexture(); 
}


Jellyfish::Jellyfish(sf::Vector2f position, int frameRate) : Alien(position,frameRate) { 
    mNumFrames = 2;
    mTextureLocation = new int[mNumFrames * 4];

    mAnimation.addFrame(0,200,70,247);
    mAnimation.addFrame(0,250,70,297);
    mAnimation.setAnimationRepeat(true);

    /*
    mTextureLocation[0] = 0;
    mTextureLocation[1] = 200;
    mTextureLocation[2] = 70;
    mTextureLocation[3] = 247;
    mTextureLocation[4] = 0;
    mTextureLocation[5] = 250;
    mTextureLocation[6] = 70;
    mTextureLocation[7] = 297;
    */
    mPoints = 10;
    setTexture(); 
}

Alien::~Alien(){
    if (mTextureLocation != nullptr){
        delete [] mTextureLocation;
    }
}



sf::Vector2f Alien::size() const { 
    if(mAnimation.valid()){
        return mAnimation.size(); 
    }
    throw NoTextureSize();
}


int Alien::sizeX() const { 
    if(mAnimation.valid()){
        return mAnimation.sizeX();
    }
    throw NoTextureSize();
}


int Alien::sizeY() const { 
    if(mAnimation.valid()){
        return mAnimation.sizeY();
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
    if(mAnimation.valid()){
        mSprite.setTextureRect(mAnimation.getFrame());
    }
}


void Alien::cycleFrames(){
    if(mAnimation.valid()){
        mAnimation.updateFrame();
        mSprite.setTextureRect(mAnimation.getFrame());
    }
}