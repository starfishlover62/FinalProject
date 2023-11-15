#include "enemies.h"


Enemies::Enemies(){
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