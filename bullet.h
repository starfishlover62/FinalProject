#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "alien.h"

class Bullet : public sf::Drawable{

public:
    Bullet(bool up) : Bullet(up,sf::Vector2f(-200,-200)){};
    Bullet(bool up, sf::Vector2f position);

    int x() const { return mPosition.x; }
    int y() const { return mPosition.y; }
    sf::Vector2f getLocation() const { return mPosition; }
    void setLocation(sf::Vector2f position);
    void moveBulletUp();
    void moveBulletDown();
    bool checkCollision(const Alien* enemy);

    void setVelocity(sf::Vector2i velocity = {0,0}) { mIncrement = velocity; }
    


    void update(sf::Event& event, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
    virtual void draw(sf::RenderTarget& target) const;
    //virtual void setTexture() = 0;
    

protected:
    sf::Vector2f mPosition;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Vector2f mScale;
    sf::Vector2i mIncrement;
    bool friendly;

};

#endif