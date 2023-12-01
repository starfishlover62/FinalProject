#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include <SFML/Graphics.hpp>


#include <iostream>

#include "animation.h"


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
    class InvalidMove{};

    // Static variables
    static std::string textureFile;

    // Constructors
    Alien(sf::Vector2f position = sf::Vector2f(0,0), int frameRate = 45);
    ~Alien();

    // Getters
    int x() const { return mPosition.x; }
    int y() const { return mPosition.y; }
    bool dead() const { return mDead; }

    sf::Vector2f size() const; // Need to update with animations
    int sizeX() const; // Need to update with animations
    int sizeY() const; // Need to update with animations
    sf::Vector2f getLocation() const { return mPosition; }

    void moveX(int direction, float distance);
    void moveY(int direction, float distance);
    virtual void kill();


    void setLocation(sf::Vector2f position);
    // void update(sf::Event& event, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target) const;
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
    virtual void setTexture();
    virtual bool cycleFrames();
    int points() const { return mPoints; }
    

protected:
    sf::Vector2f mPosition;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Vector2f mScale;

    int mPoints;
    bool mDead;

    int mFrameRate;
    int mNumFrames;
    int mNumKillFrames;
    int mCurrentFrame;
    int mRunningFrameTotal;

    Animation mAnimation;

    int* mTextureLocation; // {startx,starty,endx,endy}
};



class Squid : public Alien {
public:
    Squid(sf::Vector2f position = sf::Vector2f(0,0), int frameRate = 45);
};

class Crab : public Alien {
public:
    Crab(sf::Vector2f position = sf::Vector2f(0,0), int frameRate = 45);
};

class Jellyfish : public Alien {
public:
    Jellyfish(sf::Vector2f position = sf::Vector2f(0,0), int frameRate = 45);
};



#endif