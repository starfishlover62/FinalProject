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
    Enemies(int screenX, int screenY, float frameRate);
    ~Enemies();

    sf::Vector2f accessPosition(int num);
    float accessPositionX(int num);
    float accessPositionY(int num);
    int checkCollision(Bullet* playerBullet);
    virtual void draw(sf::RenderTarget& target) const;
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

    void move();


    class NoScreenSize{};
    

    

protected:
    int screenWidth; // Size of the window's width
    int screenHeight; // Size of the window's height
    float frameRate;
    float screenBuffer; // Percentage of screen that aliens stop at. I.e if 5, aliens change directions 5% of the screen from the edge
    float speedX; // Percentage of width that aliens move each second
    float speedY; // Percentage of height that aliens move each time they advance
    int frameTicker;
    bool movingRight;


    std::vector<Alien *> aliens;

    int numRows;
    int numPerRow;

    Alien* leftMostAlien;
    Alien* rightMostAlien;


    void shiftX(int direction);
    void shiftY(int direction);

    bool setLeftAlien();
    bool setRightAlien();
    
    



};

#endif