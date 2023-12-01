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
    int screenWidth;    // Size of the window's width
    int screenHeight;   // Size of the window's height
    float frameRate;    // The number of frames to wait before moving
    float screenBuffer; // Percentage of screen that aliens stop at. I.e if 5, aliens change directions 5% of the screen from the edge
    float speedX;       // Percentage of width that aliens move each second
    float speedY;       // Percentage of height that aliens move each time they advance
    int frameTicker;    // Tracks the number of frames between movements
    bool movingRight;   // True if aliens are moving right, false if moving left


    sf::Time mTimePerShift;
    sf::Time mTimeSinceLastUpdate;
    sf::Clock mClock;


    std::vector<Alien *> aliens; // Vector of pointers to all of the aliens

    int numRows;    // Number of rows of aliens
    int numPerRow; // Number of aliens per row

    Alien* leftMostAlien;   // Points to the left-most alien (favors aliens higher up vertically)
    Alien* rightMostAlien;  // Points to the right-most alien (favors aliens higher up vertically)


    void shiftX(int direction); // Moves the aliens horizontally
    void shiftY(int direction); // Moves the aliens vertically
    void nextFrame();

    bool setLeftAlien();    // Sets the leftMostAlien pointer
    bool setRightAlien();   // Sets the rightMostAlien pointer

    
    



};

#endif