#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable{

public:
    Bullet(bool up);
    Bullet(sf::Vector2f position);

    int x() const { return mPosition.x; }
    int y() const { return mPosition.y; }
    sf::Vector2f getLocation() const { return mPosition; }
    void setLocation(sf::Vector2f position);
    void moveBulletUp();
    void moveBulletDown();
    


    void update(sf::Event& event, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
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