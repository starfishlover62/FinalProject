#include "playerName.h"

PlayerName::PlayerName()
{
    ;
}

PlayerName::PlayerName(std::string name)
{
    mPlayerName = name;
}

void PlayerName::setPlayerName(std::string name)
{
    mPlayerName = name;
}

void PlayerName::setPlayerName(sf::RenderWindow& window, bool OUTPUT_FEEDBACK)
{
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) // don't know how to load font from c drive
    {
        // Handle font loading error
        std::cerr << "Error loading font file." << std::endl;
        exit(1);
    }

    sf::Text promptForName;
    promptForName.setString("Player Name: "); // text
    promptForName.setPosition(200, 300); // position
    promptForName.setFont(font);
    promptForName.setCharacterSize(24);
    promptForName.setFillColor(sf::Color::White);

    sf::Text startTyping;
    startTyping.setString("(Start Typing)"); // text
    startTyping.setPosition(375, 300); // position
    startTyping.setFont(font);
    startTyping.setCharacterSize(24);
    startTyping.setFillColor(sf::Color::White);

    sf::Text input; // user input
    input.setPosition(375, 300); // position
    input.setFont(font);
    input.setCharacterSize(24);
    input.setFillColor(sf::Color::White);

    //std::string mPlayerName;
    bool pressedEnter = false;
    bool enteredCharacter = false;

    while (window.isOpen() && !pressedEnter)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                if(OUTPUT_FEEDBACK) std::cerr << "Game Closed\n";
                exit(0);
                break;
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == 13)
                    {
                        pressedEnter = true;
                    }
                    else if (event.text.unicode == 8 && mPlayerName.size() > 0)
                    {
                        // handle backspace to erase characters
                        mPlayerName.pop_back();
                    }
                    else if(mPlayerName.size() < 10)
                    {
                        // handle regular key presses and add them to the inputText
                        enteredCharacter = true;
                        mPlayerName += static_cast<char>(event.text.unicode);
                    }
                    input.setString(mPlayerName);
                }
            }
        }

        window.clear();

        // show "(Start Typing)" until user types a character
        if(!enteredCharacter)
        {
            window.draw(startTyping);
        }

        window.draw(promptForName);
        window.draw(input);
        window.display();
    }
    // player name becomes "No Name" if player doesn't enter a name
    if(!enteredCharacter)
    {
        mPlayerName = "No Name";
    }
}

std::string PlayerName::getPlayerName() const
{
    return mPlayerName;
}