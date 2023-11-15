#ifndef PLAYERNAME_H
#define PLAYERNAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class PlayerName
{
    public:
        PlayerName();
        PlayerName(std::string name);
        void setPlayerName(std::string name);
        void setPlayerName(sf::RenderWindow& window, bool OUTPUT_FEEDBACK);
        std::string getPlayerName() const;

    private:
        std::string mPlayerName;
        sf::Font mFont;
        bool mFontLoaded;
        std::string mInput;
        sf::Text mPromptForName;
        sf::Text mInputText;
};

#endif