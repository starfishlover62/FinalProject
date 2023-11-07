#include "gameboard.h"

Gameboard::Gameboard(const std::string& playerName, int initialScore) : mPlayerName(playerName), mScore(initialScore)
{
    mFont.loadFromFile("assets/arial.ttf"); // don't know how to load font from c drive
    mNameText.setFont(mFont);
    mNameText.setCharacterSize(24);
    mNameText.setFillColor(sf::Color::White);
    mNameText.setPosition(20, 20);
    mNameText.setString(playerName);

    updateScoreText();
    mScoreText.setPosition(600, 20);
}

void Gameboard::increaseScore(int increaseBy)
{
    mScore += increaseBy;
    updateScoreText();
}

void Gameboard::draw(sf::RenderWindow& window) const
{
    window.draw(mNameText);
    window.draw(mScoreText);
}

void Gameboard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mNameText, states);
    target.draw(mScoreText, states);
}

void Gameboard::drawAdditionalText(sf::RenderWindow& window, const sf::Text& additionalText)
{
    window.draw(additionalText);
}

void Gameboard::updateScoreText()
{
    mScoreText.setFont(mFont);
    mScoreText.setCharacterSize(24);
    mScoreText.setFillColor(sf::Color::White);
    mScoreText.setString("Score: " + std::to_string(mScore));
}

void Gameboard::displayGameOverScreen()
{
    sf::Text text;
    text.setFont(mFont);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(400, 400);
    text.setString("GAME OVER");
    // confirm quit by 'y' or 'n' or 'ESC' (y)
}

sf::Text Gameboard::pauseScreen()
{
    sf::Text pauseText;
    pauseText.setFont(mFont);
    pauseText.setCharacterSize(36);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(350, 400);
    pauseText.setString("PAUSE");
    return pauseText;
}

void Gameboard::displayQuitOverScreen()
{
    sf::Text text;
    text.setFont(mFont);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(400, 400);
    text.setString("QUIT");
}

void Gameboard::displayLevel()
{
    sf::Text text;
    text.setFont(mFont);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(400, 400);
    text.setString("LEVEL " + mLevel);
}

void Gameboard::increaseLevel()
{
    mLevel++;
}