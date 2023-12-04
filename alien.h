/**
 * @file alien.h
 * @author Josh Gillum
 * @brief Class definitions for the Alien, Squid, Crab, and Jellyfish classes
 * @version 0.1
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ALIEN_H
#define ALIEN_H

#include <string>
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>

#include "animation.h"


/**
 * @brief Alien abstract class. Designed to provide a framework for inherited classes to provide specifications as
 * to the attributes of the alien
 * 
 */
class Alien : public sf::Drawable{

public:

    // Exception Classes
    class loadTextureError{ // Used for when a texture can not be loaded from file
        public:
            loadTextureError(){ path = "Unspecified"; }
            loadTextureError(std::string path){ this->path = path;}
            std::string path;
    }; 
    class InvalidMove{}; // Used when no direction is specified for moving

    // Constructor
    Alien(sf::Vector2f position = sf::Vector2f(0,0));

    // Getters
    sf::Vector2f position() const { return mPosition; } // Returns the position of the sprite as a vector
    int x() const { return mPosition.x; }               // Returns the position of the sprite on the x-axis
    int y() const { return mPosition.y; }               // Returns the position of the sprite on the y-axis
    sf::Vector2f size() const;  // Returns the size of the sprite as a vector
    int sizeX() const;          // Returns the width of the sprite
    int sizeY() const;          // Returns the height of the sprite
    bool dead() const { return mDead; } // Returns true if the alien is dead, false if living
    bool readyForDeletion() const { return mAnimation.complete(); } // Returns true if the explosion animation is complete
    int points() const { return mPoints; } // Returns the number of points the alien is worth

    // Drawing
    virtual void draw(sf::RenderTarget& target) const { target.draw(mSprite); } // Draws the alien
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const { target.draw(mSprite,states); } // Draws the alien

    // Updating
    void setTextureFile(std::string path) { mTextureFile = path; } // Sets the path to the texture file
    void setPosition(sf::Vector2f position); // Sets the position of the sprite    
    void moveX(float distance, int direction = 1);  // Moves the sprite along the x-axis
    void moveY(float distance, int direction = 1);  // Moves the sprite along the y-axis
    virtual void kill(); // Kills the alien, updates to the explosion animation
    virtual bool cycleFrames(); // Advances the frame
    

protected:
    sf::Vector2f mPosition;     // Position of the alien
    sf::Sprite mSprite;         // Sprite of the alien
    sf::Texture mTexture;       // Texture for the sprite
    sf::Vector2f mScale;        // How much to scale the sprite by

    std::string mTextureFile;   // Path to the texture file
    Animation mAnimation;       // Animation for the alien

    int mPoints;                // Number of points alien is worth
    bool mDead;                 // True if dead, false if alive

    virtual void setTexture();  // Sets the texture for the sprite

};



/**
 * @brief Squid class has the attributes of the squid type of alien
 * 
 */
class Squid : public Alien {
    public:
        Squid(sf::Vector2f position = sf::Vector2f(0,0));
};


/**
 * @brief Crab class has the attributes of the crab type of alien
 * 
 */
class Crab : public Alien {
    public:
        Crab(sf::Vector2f position = sf::Vector2f(0,0));
};


/**
 * @brief Jellyfish class has the attributes of the jellyfish type of alien
 * 
 */
class Jellyfish : public Alien {
    public:
        Jellyfish(sf::Vector2f position = sf::Vector2f(0,0));
};


class UFO : public Alien {
    public:
        UFO(sf::Vector2f position = sf::Vector2f(0,0), sf::Vector2f velocity = sf::Vector2f(0,0));
        sf::Vector2f velocity() const { return mVelocity; }
        void hide();
        void spawn(sf::Vector2f position = sf::Vector2f(0,0), sf::Vector2f velocity = sf::Vector2f(0,0));
    protected:
        sf::Vector2f mVelocity;
};


#endif