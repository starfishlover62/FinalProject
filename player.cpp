#include "player.h"

Player::Player(int screenWidth,int screenHeight){
    mScreenWidth = screenWidth;
    mScreenHeight = screenHeight;
    mTank = new Tank(mScreenWidth);
    mLives = 3;

    for(int i = 0; i < mLives; ++i){
        mTankLives.push_back(new Tank(mScreenWidth,{690+(50.f*i), 10}));

        // mTankLives[i]->setOrigin(-380-(100*i), 1485.f);

        float initialTankLifeScale = 0.5f; // Adjust this value as needed
        mTankLives[i]->setScale({initialTankLifeScale, initialTankLifeScale});
    }
    mBullet = new FriendlyBullet({mTank->x(),mTank->y()},-8.0);

    mBulletVisible = false;
    mHud = new Gameboard("p1",0);

    mMoving = false;
    mVelocity = 2;
    mTimeSinceLastUpdate = sf::Time::Zero;
    mTimePerUpdate = sf::seconds(0.01);
    mClock.restart();
    mFrozen = false;

    mInv = false;
    mIClock.restart();
    mTimeI = sf::Time::Zero;
    mTimeIFrames = sf::seconds(2);
}


Player::~Player(){
    if(mTank != nullptr){
        delete mTank;
    }
    if(mHud != nullptr){
        delete mHud;
    }
    for(unsigned i = 0; i < mTankLives.size(); ++i){
        if(mTankLives[i] != nullptr){
            delete mTankLives[i];
        }
    }
    if(mBullet != nullptr){
        delete mBullet;
    }
}

void Player::draw(sf::RenderTarget& target) const {
    mTank->draw(target);
    mHud->draw(target);
    if(mBulletVisible){
        mBullet->draw(target);
    }
    // for(unsigned i = 0; i < mTankLives.size(); ++i){
    //     mTankLives[i]->draw(target);
    // }
    std::for_each(mTankLives.begin(),mTankLives.end(),[&target](const Tank* t){t->draw(target);});
}

void Player::draw(sf::RenderTarget& target,sf::RenderStates states) const {
    mTank->draw(target,states);
    mHud->draw(target,states);
    if(mBulletVisible){
        mBullet->draw(target,states);
    }
    // for(unsigned i = 0; i < mTankLives.size(); ++i){
    //     mTankLives[i]->draw(target,states);
    // }
    std::for_each(mTankLives.begin(),mTankLives.end(),[&target,&states](const Tank* t){t->draw(target,states);});
}

void Player::moving() { 
    if(!mMoving){
        mMoving = true; 
        mClock.restart();
        mTimeSinceLastUpdate = sf::Time::Zero;
    }
}

void Player::noMoving() { 
    if(mMoving){
        mMoving = false; 
        mClock.restart();
        mTimeSinceLastUpdate = sf::Time::Zero;
    }
}

void Player::update(){
    if(!mFrozen){
        if(mInv){
            mTimeI += mIClock.restart();
            if(mTimeI >= mTimeIFrames) {
                mInv = false;
                mTank->noBlink();
            }
        }
        if(mBulletVisible){
            mBullet->update();
            if(mBullet->y() < 5){
                mBulletVisible = false;
            }
        }
    }
}



void Player::update(sf::Event& event, sf::RenderWindow& window){
    if(event.type == sf::Event::KeyReleased){
        if((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) ||
           (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)){
            noMoving();
        }
    }
}


void Player::moveTankLeft(){
    mTank->moveTankLeft();
}


void Player::moveTankRight(){
    mTank->moveTankRight();
}


void Player::move(bool right){
    if(!mFrozen){
        mTimeSinceLastUpdate += mClock.restart();
        while(mTimeSinceLastUpdate > mTimePerUpdate){
            mTimeSinceLastUpdate -= mTimePerUpdate;
            float pos = mTank->x();
            if(right){
                if(pos + mTank->sizeX() + 2 < mScreenWidth){
                    mTank->moveX(mVelocity);
                }
            } else {
                if(pos > 2){
                    mTank->moveX(-mVelocity);
                }
            }
        }
    }
}


bool Player::shoot(){
    if(!mFrozen && !mInv){
        if(!mBulletVisible){
            // std::cout << "shoot" << std::endl;
            mBulletVisible = true;
            mBullet->setPosition({mTank->x() + (mTank->sizeX()/2), mTank->y()});
            mBullet->reset();
            return true;
        }
    }
    return false;
}

const FriendlyBullet* Player::bulletPtr() const{
    if(mBulletVisible){
        return mBullet;
    } else {
        return nullptr;
    }
}

const Tank* Player::tankPtr() const{
    if(!mInv){
        return mTank;
    }
    return nullptr;
}


bool Player::loseLife() {
    if(mLives > 0){
        --mLives;
        if(mTankLives[mTankLives.size()-1] != nullptr){
            delete mTankLives[mTankLives.size()-1];
            mTankLives.pop_back();
        }
            
        mInv = true;
        mIClock.restart();
        mTimeI = sf::Time::Zero;
        mTank->blink();
        return true;
    }
    return false;
}


void Player::freeze(){
    if(!mFrozen){
        mTimeSinceLastUpdate += mClock.restart();
        mFrozen = true;
        mTank->freeze();
        mBullet->freeze();
    }
}


void Player::unFreeze(){
    if(mFrozen){
        mClock.restart();
        mFrozen = false;
        mTank->unFreeze();
        mBullet->unFreeze();
    }
}