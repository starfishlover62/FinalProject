/**
 * @file player.h
 * @author Josh Gillum
 * @brief Class definition for Player class, which represents a player
 * @version 1.0
 * @date 2023-12-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "tank.h"
#include "gameboard.h"
#include "bullet.h"
#include "playerName.h"


class Player : public sf::Drawable {
    public:
        Player(int screenWidth = 0,int screenHeight = 0, PlayerName name = PlayerName("p1"));
        ~Player() { clear(); }
        void clear(); // Does the job of the destructor

        // Draws the tank, gameboard, bullet, and lives graphic
        virtual void draw(sf::RenderTarget& target) const;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

        void update(); // Moves the bullet, and updates invincibility state
        void update(sf::Event& event, sf::RenderWindow& window); // Deals with a movement key being released

        const FriendlyBullet* bulletPtr() const; // Returns a pointer constant to the player bullet
        const Tank* tankPtr() const; // Returns a pointer constant to the player tank

        void moving();   // Sets the moving boolean to true
        void noMoving(); // Sets the moving boolean to false
        void move(bool right = true);        // Moves the tank
        int x() const { return mTank->x(); } // Returns the tank's x position
        int y() const { return mTank->y(); } // Returns the tank's y position
        
        bool shoot(); // Shoots a bullet
        void hideBullet() { mBulletVisible = false; } // Makes the bullet act as if it was destroyed
        void updateScore(int points) { mHud->increaseScore(points); } // Increases score by points points
        bool loseLife(); // Decrements life counter and makes player invincible

        void freeze();   // Freezes the clocks
        void unFreeze(); // Unfreezes the clocks
        void pause() { mHud->pause(); }      // Pauses the game
        void unPause() { mHud->unPause(); }  // Unpauses the game
        void end() { mHud->end(); }          // Ends the game
        void unEnd() { mHud->unEnd(); }      // Unends the game


    protected:
        bool mInv;                          // True if the player is invincible, false if not
        bool mFrozen;                       // True if the clock is frozen, false if not
        bool mBulletVisible;                // True if the bullet should be visible (is moving), false if it should not
        bool mMoving;                       // True if the player is currently moving, false if not
        int mScreenWidth, mScreenHeight;    // The width and height of the screen, in pixels
        Tank* mTank;                        // Pointer to the player's tank object
        int mLives;                         // The number of lives the player has
        double mVelocity;                   // The speed that the player tank is moving at
        Gameboard* mHud;                    // The text and graphics that comprise the HUD
        std::vector<Tank*> mTankLives;      // The tank graphics that represent the life count
        FriendlyBullet* mBullet;            // Pointer to the player's missile

        
        // Clock and time storage for movement timing
        sf::Clock mClock;
        sf::Time mTimeSinceLastUpdate;
        sf::Time mTimePerUpdate;

        // Clock and time storage for invincibility timing
        sf::Clock mIClock;
        sf::Time mTimeI;
        sf::Time mTimeIFrames;

};

#endif