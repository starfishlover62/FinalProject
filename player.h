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
        ~Player();

        virtual void draw(sf::RenderTarget& target) const;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
        void update();
        void update(sf::Event& event, sf::RenderWindow& window);

        const FriendlyBullet* bulletPtr() const;
        const Tank* tankPtr() const;

        void moveTankLeft();
        void moveTankRight();

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
        bool mInv;
        bool mFrozen;
        int mScreenWidth, mScreenHeight;
        Tank* mTank;
        int mLives;
        double mVelocity;
        Gameboard* mHud;
        std::vector<Tank*> mTankLives;
        FriendlyBullet* mBullet;

        bool mBulletVisible;
        bool mMoving;

        sf::Clock mClock;
        sf::Time mTimeSinceLastUpdate;
        sf::Time mTimePerUpdate;

        sf::Clock mIClock;
        sf::Time mTimeI;
        sf::Time mTimeIFrames;

};

#endif