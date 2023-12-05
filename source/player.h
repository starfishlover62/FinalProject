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

#include "tank.h"
#include "gameboard.h"
#include "bullet.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Player : public sf::Drawable {
    public:
        Player(int screenWidth = 0,int screenHeight = 0);
        ~Player() { clear(); }
        void clear(); // Does the job of the destructor

        // Draws the tank, gameboard, bullet, and lives graphic
        virtual void draw(sf::RenderTarget& target) const;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

        void update(); // Moves the bullet, and updates invincibility state
        void update(sf::Event& event, sf::RenderWindow& window); // Deals with a movement key being released

        const FriendlyBullet* bulletPtr() const; // Returns a pointer constant to the player bullet
        const Tank* tankPtr() const; // Returns a pointer constant to the player tank

        bool loseLife();

        void moving();
        void noMoving();
        

        void hideBullet() { mBulletVisible = false; }
        void updateScore(int points) { mHud->increaseScore(points); }

        void move(bool right = true);
        int x() const { return mTank->x(); }
        int y() const { return mTank->y(); }

        void freeze();
        void unFreeze();
        void pause() { mHud->pause(); }
        void unPause() { mHud->unPause(); }
        void end() { mHud->end(); }
        void unEnd() { mHud->unEnd(); }

        bool shoot();

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