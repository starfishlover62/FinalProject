#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include <SFML/Graphics.hpp>

class Alien : public sf::Drawable{

public:

    // Exception Classes
    class loadTextureError{ // Used for when a texture can not be loaded from file
        public:
            loadTextureError(){ path = "Unspecified"; }
            loadTextureError(std::string path){ this->path = path;}
            std::string path;
    };

    // Static variables
    static int textureLocation [4]; // {startx,starty,endx,endy}
    static std::string textureFile;
    static int points;

    // Constructors
    Alien() : Alien(sf::Vector2f(0,0)) {};
    Alien(sf::Vector2f position);

    // Getters
    int x() const { return mPosition.x; }
    int y() const { return mPosition.y; }
    sf::Vector2f getLocation() const { return mPosition; }


    void setLocation(sf::Vector2f position);
    void update(sf::Event& event, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
    virtual void setTexture();
    

protected:
    sf::Vector2f mPosition;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Vector2f mScale;
};



class Squid : public Alien {
public:
    Squid() : Squid(sf::Vector2f(0,0)) {};
    Squid(sf::Vector2f position);
};

class Crab : public Alien {
public:
    Crab() : Crab(sf::Vector2f(0,0)) {};
    Crab(sf::Vector2f position);
};

class Jellyfish : public Alien {
public:
    Jellyfish() : Jellyfish(sf::Vector2f(0,0)) {};
    Jellyfish(sf::Vector2f position);
};



#endif