#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class Alien : public sf::Drawable{

public:
    Alien();

    int x() const { return mPosition.x; }
    int y() const { return mPosition.y; }
    sf::Vector2f getLocation() const { return mPosition; }
    void setLocation(sf::Vector2f position);


    void update(sf::Event& event, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
    virtual void setTexture() = 0;
    

protected:
    sf::Vector2f mPosition;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Vector2f mScale;


};



class Squid : public Alien {

public:
    Squid();

    virtual void setTexture();

    static int points;
    static std::string textureFile; // path to texture file
    static int textureLocation [4]; // {startx,starty,sizex,sizey}

private:

};


#endif