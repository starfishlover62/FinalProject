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

            if(i == 0){
                if(j == 0){
                    leftMostAlien = ptr;
                } else if(j == numPerRow -1){
                    rightMostAlien = ptr;
                }
            }

            
            aliens.push_back(ptr);
            ptr = nullptr;
            x += 80;

        }

        x = 75; // set new column
        y += 55; // advance to next row

    }
        
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
                    for(unsigned i = 0; i < aliens.size(); ++i){
                        leftMostAlien = nullptr;
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
                } else if(aliens[i] == rightMostAlien){
                    for(unsigned i = 0; i < aliens.size(); ++i){
                        rightMostAlien = nullptr;
                        if(aliens[i] != nullptr){
                            if(rightMostAlien == nullptr){
                                rightMostAlien = aliens[i];
                            } else {
                                if(aliens[i]->x() < rightMostAlien->x()){
                                    rightMostAlien = aliens[i];
                                }
                            }
                        }
                    }
                }
                delete aliens[i];
                aliens[i] = nullptr;
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

    if(!movingRight && (leftMostAlien->x() <= static_cast<int>(screenWidth*screenBuffer))){
        shiftY(1);
        movingRight = true;
    } else if(movingRight && ((rightMostAlien->x()+rightMostAlien->sizeX()) >= static_cast<int>(screenWidth-(screenWidth*screenBuffer)))){
        shiftY(1);
        movingRight = false;
    } else if(frameTicker == 0){
        if(movingRight){
            shiftX(1);
        } else {
            shiftX(-1);
        }
    }

    frameTicker = ++frameTicker % static_cast<int>(frameRate);
    std::cout << frameTicker << std::endl;

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

