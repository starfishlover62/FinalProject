#ifndef PLAYERNAME_H
#define PLAYERNAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

class PlayerName
{
    public:
        void setPlayerName(sf::RenderWindow& window);
        void displayPlayerName();
        std::string setName();

    private:
        std::string mPlayerName;
        sf::Font mFont;
        bool mFontLoaded;
        std::string mInput;
        sf::Text mPromptForName;
        sf::Text mInputText;
};

#endif