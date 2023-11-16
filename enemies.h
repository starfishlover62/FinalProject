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

    
    Enemies() { throw NoScreenSize(); }
    Enemies(int screenX, int screenY);
    ~Enemies();


    int checkCollision(Bullet* playerBullet);
    virtual void draw(sf::RenderTarget& target) const;
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;


    class NoScreenSize{};

    

protected:
    int screenWidth;
    int screenHeight;

    std::vector<Alien *> aliens;

    int numRows;
    int numPerRow;

    Alien* leftMostAlien;
    Alien* rightMostAlien;
    
    



};

#endif