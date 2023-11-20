#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

#include "alien.h"
#include "bullet.h"




#include <iostream>




class Enemies : public sf::Drawable{

public:
    enum enemyType {squid, crab, jellyfish};

    
    Enemies();
    ~Enemies();

    sf::Vector2f accessPosition(int num);
    float accessPositionX(int num);
    float accessPositionY(int num);
    int checkCollision(Bullet* playerBullet);
    virtual void draw(sf::RenderTarget& target) const;
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

    

protected:

    std::vector<Alien *> aliens;

    int numRows;
    int numPerRow;
    
    



};

#endif