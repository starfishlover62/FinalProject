#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>

class Tank : public sf::Drawable{

public:
    Tank();
    Tank(sf::Vector2f position);

    int x() const { return mPosition.x; }
    int y() const { return mPosition.y; }
    sf::Vector2f getLocation() const { return mPosition; }
    void setLocation(sf::Vector2f position);
    void moveTankLeft();
    void moveTankRight();
    
    void setOrigin(float x, float y);
    void setScale(float factorX, float factorY);

    void update(sf::Event& event, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
    //virtual void setTexture() = 0;
    

protected:
    sf::Vector2f mPosition;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Vector2f mScale;
    sf::Vector2i mIncrement;


};


#endif