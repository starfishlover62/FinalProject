#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "alien.h"
#include "tank.h"

#include <iostream>

class Bullet : public Object {

    public:
        Bullet(sf::Vector2f position = {0,0}, double velocity = 0);

        bool checkCollision(const Alien* enemy);

        virtual void setVelocity(double velocity = 0) { mVelocity = velocity; }

        virtual bool update();

        void reset();
    

    protected:
        sf::Clock mClock;
        sf::Time mTimePerUpdate;
        sf::Time mTimeSinceLastUpdate;
        double mVelocity;
};


class FriendlyBullet : public Bullet {
    public:
        FriendlyBullet(sf::Vector2f position = {0,0}, double velocity = 0) : Bullet(position,velocity) {};
        bool checkCollision(const Alien* enemy) const;
};

class EnemyBullet : public Bullet {
    public:
        EnemyBullet(sf::Vector2f position = {0,0}, double velocity = 0) : Bullet(position,velocity) {};
        bool checkCollision(const Tank* player) const;

};

#endif