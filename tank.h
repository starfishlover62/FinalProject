#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>
#include "object.h"

class Tank : public Object{

public:
    Tank(int screenWidth, sf::Vector2f position = {500,730});

    void moveTankLeft();
    void moveTankRight();

    void move(float distance);
    
    void setOrigin(float x, float y);

    void update(sf::Event& event, sf::RenderWindow& window);
    //virtual void setTexture() = 0;
    

protected:
    int mScreenWidth;
    float mVelocity;


};


#endif