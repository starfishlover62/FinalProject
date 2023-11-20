#include "enemies.h"


Enemies::Enemies(int screenX, int screenY, float frameRate){
    screenWidth = screenX;
    screenHeight = screenY;
    this->frameRate = frameRate;
    screenBuffer = .05; // Percentage of screen not used
    speedX = .03;
    speedY = .04;
    frameTicker = 1;
    movingRight = true;


    int x = 75; // init first column
    int y = 100; // init first row

    numRows = 5;
    numPerRow = 11;
    int formation[numRows] {squid,crab,crab,jellyfish,jellyfish};
    Alien * ptr = nullptr;
    
    for(int i = 0; i < numRows; ++i){
        for(int j = 0; j < numPerRow; ++j){
            if(formation[i] == squid){
                ptr = new Squid(sf::Vector2f(x,y));
            } else if(formation[i] == crab){
                ptr = new Crab(sf::Vector2f(x,y));
            }  else if(formation[i] == jellyfish){
                ptr = new Jellyfish(sf::Vector2f(x,y));
            }

            
            aliens.push_back(ptr);
            ptr = nullptr;
            x += 80;

        }

        x = 75; // set new column
        y += 55; // advance to next row

    }

    setLeftAlien();
    setRightAlien();
        
}

Enemies::~Enemies(){
    for(unsigned i = 0; i < aliens.size(); ++i){
        delete aliens[i];
    }
}


int Enemies::checkCollision(Bullet* playerBullet){
    for(int i = aliens.size() - 1; i >= 0; --i){
        if(aliens[i] != nullptr){
            if(playerBullet->checkCollision(aliens[i])){
                int val = aliens[i]->points();
                if(aliens[i] == leftMostAlien){
                    delete aliens[i];
                    aliens[i] = nullptr;
                    if(setLeftAlien() == false){
                        // means no aliens are left, do something
                    }
                    
                } else if(aliens[i] == rightMostAlien){
                    delete aliens[i];
                    aliens[i] = nullptr;
                    if(setRightAlien() == false){
                        // means no aliens are left, do something
                    }
                } else {
                    delete aliens[i];
                    aliens[i] = nullptr;
                }
                return val;

            }
        }
    }
    return -1;
}


void Enemies::draw(sf::RenderTarget& target) const {
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            aliens[i]->draw(target);
            aliens[i]->cycleFrames();
        }
    }
}


void Enemies::draw(sf::RenderTarget& target,sf::RenderStates states) const {
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            aliens[i]->draw(target,states);
            aliens[i]->cycleFrames();
        }
    }
}


void Enemies::move() {

    //std::cout << frameTicker << std::endl;

    if(frameTicker == 0){
        if(!movingRight && (leftMostAlien->x() <= static_cast<int>(screenWidth*screenBuffer))){
            std::cout << (leftMostAlien->x()) << ": ";
            shiftY(1);
            movingRight = true;
            std::cout << "shift y " << std::endl;
        } else if(movingRight && ((rightMostAlien->x()+rightMostAlien->sizeX()) >= static_cast<int>(screenWidth-(screenWidth*screenBuffer)))){
            std::cout << (rightMostAlien->x()+rightMostAlien->sizeX()) << ": ";
            shiftY(1);
            movingRight = false;
            std::cout << "shift y " << std::endl;
        } else {
            if(movingRight){
                shiftX(1);
            } else {
                shiftX(-1);
            }
            std::cout << "shift x " << std::endl;
        }
    }
  frameTicker = ++frameTicker % static_cast<int>(frameRate);
}





void Enemies::shiftX(int direction){
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            aliens[i]->moveX(direction,screenWidth*speedX);
        }
    }
}


void Enemies::shiftY(int direction){
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            aliens[i]->moveY(direction,screenWidth*speedY);
        }
    }
}


bool Enemies::setLeftAlien(){
    leftMostAlien = nullptr;
    for(unsigned i = 0; i < aliens.size(); ++i){
        if(aliens[i] != nullptr){
            if(leftMostAlien == nullptr){
                leftMostAlien = aliens[i];
            } else {
                if(aliens[i]->x() < leftMostAlien->x()){
                    leftMostAlien = aliens[i];
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
            if(rightMostAlien == nullptr){
                rightMostAlien = aliens[i];
            } else {
                if((aliens[i]->x() + aliens[i]->sizeX()) > (rightMostAlien->x() + rightMostAlien->sizeX())){
                    rightMostAlien = aliens[i];
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
    return aliens[num]->getLocation();
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




