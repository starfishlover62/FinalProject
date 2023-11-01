#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include <SFML/Graphics.hpp>

class Alien : public sf::Drawable{
public:
    Alien() : Alien(sf::Vector2f(0,0)) {};
    Alien(sf::Vector2f position);

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
    Squid() : Squid(sf::Vector2f(0,0)) {};
    Squid(sf::Vector2f position) : Alien(position) { setTexture(); }

    virtual void setTexture();

    static int points;
    static std::string textureFile; // path to texture file
    static int textureLocation [4]; // {startx,starty,sizex,sizey}

private:

};

class Crab : public Alien {
public:
    Crab() : Crab(sf::Vector2f(0,0)) {};
    Crab(sf::Vector2f position) : Alien(position) { setTexture(); }

    virtual void setTexture();

    static int points;
    static std::string textureFile; // path to texture file
    static int textureLocation [4]; // {startx,starty,sizex,sizey}

private:

};

class Jellyfish : public Alien {
public:
    Jellyfish() : Jellyfish(sf::Vector2f(0,0)) {};
    Jellyfish(sf::Vector2f position) : Alien(position) { setTexture(); }

    virtual void setTexture();

    static int points;
    static std::string textureFile; // path to texture file
    static int textureLocation [4]; // {startx,starty,sizex,sizey}

private:

};


#endif