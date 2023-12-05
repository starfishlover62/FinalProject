#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>
#include "object.h"

class Tank : public Object{

public:
    Tank();
    Tank(sf::Vector2f position);

    void moveTankLeft();
    void moveTankRight(const float SCREEN_RES_X);
    
    void setOrigin(float x, float y);

    void update(sf::Event& event, sf::RenderWindow& window);
    //virtual void setTexture() = 0;
    

protected:
    sf::Vector2i mIncrement;


};


#endif