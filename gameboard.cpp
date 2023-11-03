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

void Gameboard::draw(sf::RenderWindow& window)
{
    window.draw(mNameText);
    window.draw(mScoreText);
}

void Gameboard::updateScoreText()
{
    mScoreText.setFont(mFont);
    mScoreText.setCharacterSize(24);
    mScoreText.setFillColor(sf::Color::White);
    mScoreText.setString("Score: " + std::to_string(mScore));
}
