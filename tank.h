#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>
#include "object.h"
#include <iostream>
class Tank : public Object{

public:
    Tank(int screenWidth, sf::Vector2f position = {500,730});

    void moveTankLeft();
    void moveTankRight();

    void blink();
    void noBlink();

    void move(float distance);
    
    void setOrigin(float x, float y);

    void update();
    

protected:
    bool mBlinking;
    int mScreenWidth;
    float mVelocity;


};


#endif