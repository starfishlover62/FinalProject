/**
 * @file alien.h
 * @author Josh Gillum
 * @brief Class definitions for the Alien, Squid, Crab, and Jellyfish classes
 * @version 1.0
 * @date 2023-12-05
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
#include "object.h"


/**
 * @brief Alien abstract class. Designed to provide a framework for inherited classes to provide specifications as
 * to the attributes of the alien
 * 
 */
class Alien : public Object{

public:
    class InvalidMove{}; // Used when no direction is specified for moving

    Alien(sf::Vector2f position = sf::Vector2f(0,0));

    // Getters
    bool dead() const { return mDead; } // Returns true if the alien is dead, false if living
    bool readyForDeletion() const { return mAnimation.complete(); } // Returns true if the explosion animation is complete
    int points() const { return mPoints; } // Returns the number of points the alien is worth

    virtual void kill(); // Kills the alien, updates to the explosion animation
    

protected:
    int mPoints;                // Number of points alien is worth
    bool mDead;                 // True if dead, false if alive
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


/**
 * @brief UFO class that has the attributes of the UFO (saucer) type of alien
 * 
 */
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