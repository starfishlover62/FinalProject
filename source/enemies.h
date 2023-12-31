/**
 * @file enemies.h
 * @author Josh Gillum
 * @brief Enemies class definition
 * @version 1.0
 * @date 2023-12-5
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include <list>
#include <algorithm>

#include <iostream>
#include <typeinfo>

#include "alien.h"
#include "bullet.h"
#include "player.h"

/**
 * @brief A group of aliens. Allows the group to be moved in sync as well as to be animated in sync.
 * Provides for checking collision and firing
 * 
 */
class Enemies : public sf::Drawable{

    public:

        class NoScreenSize{}; // Thrown when a screen size is not specified (required to be able to move the aliens)

        // Allows for easy reference to different types of aliens
        enum enemyType {squid, crab, jellyfish};

        
        // Constructors
        Enemies() { throw NoScreenSize(); } 
        Enemies(int screenX, int screenY);
        ~Enemies();
        void clear(); // Does the function of the destructor

        sf::Vector2f accessPosition(int num);
        float accessPositionX(int num);
        float accessPositionY(int num);

        virtual void draw(sf::RenderTarget& target) const; // Draws all of the aliens
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const; // Draws all of the aliens

        void update(); // Moves the aliens and animates the explosions
        int update(const FriendlyBullet* playerBullet); // Checks for collision with the player's bullet. Calls update()
        bool checkCollision(const Tank* player);
        bool touchingPlayer(const Tank* player);
        void freeze();   // Freezes the clocks
        void unFreeze(); // Unfreezes the clocks


    protected:
        bool mFrozen;
        int screenWidth;    // Size of the window's width
        int screenHeight;   // Size of the window's height
        float screenBuffer; // Percentage of screen that aliens stop at. I.e if .05, aliens change directions 5% of the screen from the edge
        float speedX;       // Percentage of width that aliens move each second
        float speedY;       // Percentage of height that aliens move each time they advance
        bool movingRight;   // True if aliens are moving right, false if moving left
        int numRows;        // Number of rows of aliens
        int numPerRow;      // Number of aliens per row
        std::vector<Alien *> aliens; // Vector of pointers to all of the aliens
        UFO* ufo; // Pointer to ufo alien
        std::list<EnemyBullet> alienBullets; // List of the alien's shots


        Alien* leftMostAlien;   // Points to the left-most alien (favors aliens higher up vertically)
        Alien* rightMostAlien;  // Points to the right-most alien (favors aliens higher up vertically)
        bool setLeftAlien();    // Sets the leftMostAlien pointer
        bool setRightAlien();   // Sets the rightMostAlien pointer

        sf::Time mTimePerShift;         // Amount of time to elapse between each movement of the aliens
        sf::Time mTimeSinceLastUpdate;  // Time since the aliens were last shifted
        sf::Clock mClock;               // Tracks elapsed time

        sf::Time mTimePerUFOShift;         // Amount of time to elapse between each movement of the ufo
        sf::Time mTimeSinceLastUFOUpdate;  // Time since the ufo was last shifted
        sf::Time mUFORespawnTime;   // Time until UFO respawns
        sf::Clock mUFORespawnClock; // Tracks elapsed time since UFO was destroyed

        sf::Time mTimePerShot;      // Time until aliens shoot again
        sf::Time mTimeSinceLastShot;// Time since last shot was made
        sf::Clock mShotClock;       // Tracks elapsed time since last shot
        

        void shiftX(bool right); // Moves the aliens horizontally
        void shiftY(bool down);  // Moves the aliens vertically
        void move();      // Controls when and in what direction aliens move. Also controls when the alien's change their animation frame
        void nextFrame(); // Cycles to the next frame of animation for every alien

        int checkCollision(const FriendlyBullet* playerBullet); // Checks whether the bullet is colliding with any aliens
        void setUFORespawn(); // Sets the amount of time needed for the ufo to respawn
        void shoot(); // Controls shooting bullets from the aliens.
};

#endif