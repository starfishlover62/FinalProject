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

sf::Text Gameboard::levelText()
{
    sf::Text pauseText;
    pauseText.setFont(mFont);
    pauseText.setCharacterSize(36);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(350, 400);
    pauseText.setString("LEVEL");
    return pauseText;
}

sf::Text Gameboard::pauseText()
{
    sf::Text pauseText;
    pauseText.setFont(mFont);
    pauseText.setCharacterSize(36);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(350, 400);
    pauseText.setString("PAUSE");
    return pauseText;
}

sf::Text Gameboard::gameOverText()
{
    sf::Text pauseText;
    pauseText.setFont(mFont);
    pauseText.setCharacterSize(36);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(350, 400);
    pauseText.setString("GAME OVER");
    return pauseText;
}

sf::Text Gameboard::quitText()
{
    sf::Text pauseText;
    pauseText.setFont(mFont);
    pauseText.setCharacterSize(36);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(350, 400);
    pauseText.setString("QUIT");
    return pauseText;
}

void Gameboard::increaseLevel()
{
    mLevel++;
}