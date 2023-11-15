#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include <SFML/Graphics.hpp>


#include <iostream>


class Alien : public sf::Drawable{

public:

    // Exception Classes
    class loadTextureError{ // Used for when a texture can not be loaded from file
        public:
            loadTextureError(){ path = "Unspecified"; }
            loadTextureError(std::string path){ this->path = path;}
            std::string path;
    };

    class NoTextureSize{};

    // Static variables
    static std::string textureFile;

    // Constructors
    Alien() : Alien(sf::Vector2f(0,0)) {};
    Alien(sf::Vector2f position);
    ~Alien();

    // Getters
    int x() const { return mPosition.x; }
    int y() const { return mPosition.y; }
    bool dead() const { return mDead; }

    sf::Vector2f size() const; // Need to update with animations
    int sizeX() const; // Need to update with animations
    int sizeY() const; // Need to update with animations
    sf::Vector2f getLocation() const { return mPosition; }


    void setLocation(sf::Vector2f position);
    void update(sf::Event& event, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target) const;
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
    virtual void setTexture();
    virtual void cycleFrames();
    int points() const { return mPoints; }
    

protected:
    sf::Vector2f mPosition;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Vector2f mScale;
    int mPoints;
    bool mDead;
    int mNumFrames;
    int mCurrentFrame;
    int mRunningFrameTotal;
    int* mTextureLocation; // {startx,starty,endx,endy}
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