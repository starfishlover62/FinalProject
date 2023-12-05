#include "enemies.h"


Enemies::Enemies(int screenX, int screenY){
    screenWidth = screenX;
    screenHeight = screenY;

    screenBuffer = .03; // Percentage of screen not used
    speedX = .015;
    speedY = .04;
    movingRight = true;


    int x = screenWidth*(screenBuffer*0.8); // init first column
    int y = screenHeight*0.1; // init first row

    numRows = 5;
    numPerRow = 11;
    int formation[numRows] {squid,crab,crab,jellyfish,jellyfish};
    Alien * ptr = nullptr;
    
    for(int i = 0; i < numRows; ++i){
        for(int j = 0; j < numPerRow; ++j){
            if(formation[i] == squid){
                ptr = new Squid(sf::Vector2f(x+9,y));
            } else if(formation[i] == crab){
                ptr = new Crab(sf::Vector2f(x+2,y));
            }  else if(formation[i] == jellyfish){
                ptr = new Jellyfish(sf::Vector2f(x,y));
            }

            
            aliens.push_back(ptr);
            ptr = nullptr;
            x += 60;

        }

        x = screenWidth*(screenBuffer*0.8); // set new column
        y += 55; // advance to next row

    }

    setLeftAlien();
    setRightAlien();

    mTimePerShift = sf::seconds(0.75);
    mTimeSinceLastUpdate = sf::Time::Zero;

    mTimePerUFOShift = sf::seconds(0.01);
    mTimeSinceLastUFOUpdate = sf::Time::Zero;

    mTimePerShot = sf::seconds(1);
    mTimeSinceLastShot = sf::Time::Zero;

    mClock.restart();
    mUFORespawnClock.restart();
    mShotClock.restart();

    ufo = new UFO(sf::Vector2f(20,30),sf::Vector2f(1,0));

    std::srand(std::time(0));
        
}

Enemies::~Enemies(){
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            delete aliens[i];
        }
    }
    if(ufo != nullptr){
        delete ufo;
    }
    alienBullets.clear();
}

void Enemies::setUFORespawn(){
    mUFORespawnClock.restart();
    std::srand(std::time(0));
    mUFORespawnTime = sf::seconds(5 + (std::rand() % 15));
}


int Enemies::checkCollision(const FriendlyBullet* playerBullet){
    if(playerBullet != nullptr){
        if(playerBullet->checkCollision(ufo)){
            int val = ufo->points();
            ufo->kill();
            setUFORespawn();
            return val;
        } else {
            for(int i = aliens.size() - 1; i >= 0; --i){
                if(aliens[i] != nullptr && !aliens[i]->dead()){
                    if(playerBullet->checkCollision(aliens[i])){
                        int val = aliens[i]->points();
                        aliens[i]->kill();
                        if(aliens[i] == leftMostAlien){
                            if(setLeftAlien() == false){
                               return -2;
                            }
                            
                        } else if(aliens[i] == rightMostAlien){
                            if(setRightAlien() == false){
                                return -2;
                            }
                        }
                        return val;

                    }
                }
            }
        }
    }
    return -1;
}

bool Enemies::checkCollision(const Tank* player){
    for(auto it = alienBullets.begin(); it != alienBullets.end(); ++it){
        if(it->checkCollision(player)){
            it = alienBullets.erase(it);
            return true;
        }
    }
    return false;
}


void Enemies::draw(sf::RenderTarget& target) const {
    // std::cout << "Draw" << std::endl;
    ufo->draw(target);
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            aliens[i]->draw(target);
        }
    }
    std::for_each(alienBullets.begin(),alienBullets.end(),[&target](const EnemyBullet b){b.draw(target);});
}


void Enemies::draw(sf::RenderTarget& target,sf::RenderStates states) const {
    ufo->draw(target, states);
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            aliens[i]->draw(target,states);
        }
    }

    std::for_each(alienBullets.begin(),alienBullets.end(),[&target,&states](const EnemyBullet b){b.draw(target,states);});
}

void Enemies::update() {
    move();
    ufo->cycleFrames();
    if(ufo->dead()){
        mUFORespawnTime -= mUFORespawnClock.restart();
        if(mUFORespawnTime <= sf::seconds(0)){
            // std::cout << "RESPAWN" << std::endl;
            mUFORespawnTime = sf::Time::Zero;
            if((std::rand() % 2) % 2 == 0){
                ufo->spawn(sf::Vector2f(20,30),sf::Vector2f(2,0));
            } else {
                ufo->spawn(sf::Vector2f(screenWidth - 20,30),sf::Vector2f(-2,0));
            }
        }
    }
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr && aliens[i]->dead()){
            aliens[i]->cycleFrames();
            if(aliens[i]->readyForDeletion()){
                delete aliens[i];
                aliens[i] = nullptr;
            }
        }
    }
    shoot();
}

void Enemies::shoot(){
    // std::cout << "Shoot called" << std::flush;
    mTimeSinceLastShot += mShotClock.restart();
    while(mTimeSinceLastShot >= mTimePerShot){
        // std::cout << " ~shoot" << std::endl;
        mTimeSinceLastShot -= mTimePerShot;
        
        int alienShooting;
        do {
            alienShooting = std::rand() % aliens.size();
        } while(aliens[alienShooting] == nullptr);

        sf::Vector2f position(aliens[alienShooting]->x() + (aliens[alienShooting]->sizeX()/2),aliens[alienShooting]->y());
        // For some reason, directly using the constructor causes the bullets to briefly appear in the top-left corner
        // Doing it this way has seemed to fix the issue
        EnemyBullet b;
        b.setPosition(position);
        b.setVelocity(4);
        alienBullets.emplace_back(EnemyBullet(b));
    }
}

int Enemies::update(const FriendlyBullet* playerBullet){
    int val = checkCollision(playerBullet);
    update();
    return val;
}

void Enemies::move() {
    sf::Time elapsed = mClock.restart();
    mTimeSinceLastUpdate += elapsed;
    if(!ufo->dead()){
        mTimeSinceLastUFOUpdate += elapsed;
        int counter = 0;
        while(mTimeSinceLastUFOUpdate > mTimePerUFOShift && !ufo->dead()){
            mTimeSinceLastUFOUpdate -= mTimePerUFOShift;
            // std::cout << "UFO move " << counter << std::flush;
            ++counter;
            ufo->setPosition(sf::Vector2f(ufo->x()+ufo->velocity().x,ufo->y()+ufo->velocity().y));
            // std::cout << "~ " << ufo->position().x << std::endl;
            if(ufo->velocity().x > 0){
                if(ufo->x() >= screenWidth){
                    ufo->hide();
                    setUFORespawn();
                }
            } else if(ufo->velocity().x < 0){
                if(ufo->x() + ufo->sizeX() <= 0){
                    ufo->hide();
                    setUFORespawn();
                }
            }
        }
    }
    while (mTimeSinceLastUpdate > mTimePerShift){
        // std::cout << "Alien move" << std::endl;
        mTimeSinceLastUpdate -= mTimePerShift;

        if(!movingRight && (leftMostAlien->x() <= static_cast<int>(screenWidth*screenBuffer))){
            shiftY(true);
            movingRight = true;
        } else if(movingRight && ((rightMostAlien->x()+rightMostAlien->sizeX()) >= static_cast<int>(screenWidth-(screenWidth*screenBuffer)))){
            shiftY(true);
            movingRight = false;
        } else {
            if(movingRight){
                shiftX(true);
            } else {
                shiftX(false);
            }
        }

        nextFrame();
    }

    for(auto it = alienBullets.begin(); it != alienBullets.end(); ++it){
        it->update();
        // std::cout << it->y() << std::endl;
        if(it->y() >= screenHeight){
            // std::cout << "Bottom" << std::endl;
            it = alienBullets.erase(it);
            --it;
        }
    }
}





void Enemies::shiftX(bool right){
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr && !aliens[i]->dead()){
            if(right){
                aliens[i]->moveX(screenWidth*speedX);
            } else {
                aliens[i]->moveX(-screenWidth*speedX);
            }
        }
    }
}


void Enemies::shiftY(bool down){
    if(mTimePerShift > sf::seconds(0.1)){
        mTimePerShift -= sf::seconds(0.05);
    }
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr && !aliens[i]->dead()){
            if(down){
                aliens[i]->moveY(screenWidth*speedY);
            } else {
                aliens[i]->moveY(-screenWidth*speedY);
            }
        }
    }
}


void Enemies::nextFrame() {
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            if(!aliens[i]->dead()){
                aliens[i]->cycleFrames();
            }
        }
    }
}

bool Enemies::setLeftAlien(){
    leftMostAlien = nullptr;
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            if(!aliens[i]->dead()){
                if(leftMostAlien == nullptr){
                    leftMostAlien = aliens[i];
                } else {
                    if(aliens[i]->x() < leftMostAlien->x()){
                        leftMostAlien = aliens[i];
                        // std::cout << "left: " << leftMostAlien->x() << std::endl;
                    }
                }
            }
        }
    }
    if(leftMostAlien == nullptr){
        return false;
    }

    return true;
}



bool Enemies::setRightAlien(){
    rightMostAlien = nullptr;
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            if(!aliens[i]->dead()){
                if(rightMostAlien == nullptr){
                    rightMostAlien = aliens[i];
                } else {
                    if((aliens[i]->x() + aliens[i]->sizeX()) > (rightMostAlien->x() + rightMostAlien->sizeX())){
                        rightMostAlien = aliens[i];
                        // std::cout << "Right: " << rightMostAlien->x() << std::endl;
                    }
                }
            }
        }
    }
    if(rightMostAlien == nullptr){
        return false;
    }

    return true;
}

sf::Vector2f Enemies::accessPosition(int num)
{
    if (aliens[num] == nullptr)
    {
        return {-200, -200};
    }
    return aliens[num]->position();
}

float Enemies::accessPositionX(int num)
{
    if (aliens[num] == nullptr)
    {
        return -200;
    }
    return aliens[num]->x();
}

float Enemies::accessPositionY(int num)
{
    if (aliens[num] == nullptr)
    {
        return -200;
    }
    return aliens[num]->y();
}


void Enemies::freeze(){
    if(!mFrozen){
        sf::Time elapsed = mClock.restart();
        mTimeSinceLastUpdate += elapsed;
        mTimeSinceLastUFOUpdate += elapsed;
        if(ufo->dead()){
            mUFORespawnTime += mUFORespawnClock.restart();
        }
        mTimeSinceLastShot += mShotClock.restart();
        mFrozen = true;
        for_each(alienBullets.begin(),alienBullets.end(),[](EnemyBullet &b){b.freeze();});
    }
}


void Enemies::unFreeze(){
    if(mFrozen){
        mClock.restart();
        mUFORespawnClock.restart();
        mShotClock.restart();
        mFrozen = false;
        for_each(alienBullets.begin(),alienBullets.end(),[](EnemyBullet &b){b.unFreeze();});
    }
}

