#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "alien.h"

class Bullet : public Object{

public:
    Bullet(bool up) : Bullet(up,sf::Vector2f(-200,-200)){};
    Bullet(bool up, sf::Vector2f position);

    void moveBulletUp();
    void moveBulletDown();
    bool checkCollision(const Alien* enemy);

    void setVelocity(sf::Vector2i velocity = {0,0}) { mIncrement = velocity; }
    


    void update(sf::Event& event, sf::RenderWindow& window);
    // virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
    // virtual void draw(sf::RenderTarget& target) const;
    //virtual void setTexture() = 0;
    

protected:
    // sf::Vector2f mScale;
    sf::Vector2i mIncrement;
    bool friendly;

};

#endif