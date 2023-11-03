#ifndef PLAYERNAME_H
#define PLAYERNAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class PlayerName
{
    public:
        void setPlayerName(sf::RenderWindow& window);
        void displayPlayerName();
        std::string setName() const { return mPlayerName; }

    private:
        std::string mPlayerName;
        sf::Font mFont;
        bool mFontLoaded;
        std::string mInput;
        sf::Text mPromptForName;
        sf::Text mInputText;
};

#endif