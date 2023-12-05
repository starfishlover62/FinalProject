/**
 * @file object.h
 * @author Josh Gillum
 * @brief Abstract object class representing a stationery object
 * @version 0.1
 * @date 2023-12-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include "animation.h"


class Object : public sf::Drawable{
    public:
        // Exception Class
        class loadTextureError{ // Used for when a texture can not be loaded from file
            public:
                loadTextureError(){ path = "Unspecified"; }
                loadTextureError(std::string path){ this->path = path;}
                std::string path;
        }; 

        Object(sf::Vector2f position = sf::Vector2f(0,0));

        // Getters
        virtual sf::Vector2f position() const { return mPosition; } // Returns the position of the sprite as a vector
        virtual float x() const { return mPosition.x; }               // Returns the position of the sprite on the x-axis
        virtual float y() const { return mPosition.y; }               // Returns the position of the sprite on the y-axis
        virtual sf::Vector2f size() const;  // Returns the size of the sprite as a vector
        virtual int sizeX() const;          // Returns the width of the sprite
        virtual int sizeY() const;          // Returns the height of the sprite


        // Drawing
        virtual void draw(sf::RenderTarget& target) const { target.draw(mSprite); } // Draws the object
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const { target.draw(mSprite,states);} // Draws the object

        // Updating
        void setTextureFile(std::string path) { mTextureFile = path; } // Sets the path to the texture file
        void setPosition(sf::Vector2f position); // Sets the position of the sprite    
        void setScale(sf::Vector2f scale); // Sets the scale of the sprite
        virtual bool cycleFrames(); // Advances the frame

        // Moving
        void move(sf::Vector2f distance); // Moves the sprite along both axes
        void moveX(float distance);  // Moves the sprite along the x-axis
        void moveY(float distance);  // Moves the sprite along the y-axis
    
    protected:
        sf::Vector2f mPosition;     // Position of the object
        sf::Sprite mSprite;         // Sprite of the object
        sf::Texture mTexture;       // Texture for the sprite
        sf::Vector2f mScale;        // How much to scale the sprite by

        std::string mTextureFile;   // Path to the texture file
        Animation mAnimation;       // Animation for the object

        virtual void setTexture();  // Sets the texture for the sprite



};


#endif