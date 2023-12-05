#include "gameboard.h"

Gameboard::Gameboard(const std::string& playerName, int initialScore)
    : mPlayerName(playerName), mScore(initialScore), mLevel(0), mFont(loadFont())
{
    mLevel = 1; // set first level to 1
    initializeText(mLivesText, 620, 5, "Lives", 24, sf::Color::White);
    initializeText(mNameText, 20, 5, playerName, 24, sf::Color::White);
    initializeText(mScoreText, 420, 5, "Score: " + std::to_string(mScore), 24, sf::Color::White);
    initializeText(mLevelText, 240, 5, "Level: " + std::to_string(mLevel), 24, sf::Color::White);
    initializeText(mCloseText, 320, 400, "CLOSING...", 36, sf::Color::White);
    initializeText(mGameOverText, 300, 400, "GAME OVER", 36, sf::Color::Red);
    initializeText(mRetryText, 260, 400, "Retry? (Y or N)", 36, sf::Color::White);
    initializeText(mPauseText, 350, 550, "PAUSE", 36, sf::Color::Blue);

    mPaused = false;
}

sf::Font Gameboard::loadFont()
{
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        throw std::runtime_error("Failed to load font: arial.ttf");
    }
    return font;
}

void Gameboard::initializeText(sf::Text& text, float x, float y, const std::string& content, unsigned int size, sf::Color color)
{
    text.setFont(mFont);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    text.setString(content);
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
    window.draw(mLevelText);
    window.draw(mLivesText);
    if(mPaused){
        window.draw(mPauseText);
    }
}

void Gameboard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mNameText, states);
    target.draw(mScoreText, states);
    target.draw(mLevelText,states);
    target.draw(mLivesText,states);
    if(mPaused){
        target.draw(mPauseText,states);
    }
}

void Gameboard::draw(sf::RenderTarget& target) const
{
    target.draw(mNameText);
    target.draw(mScoreText);
    target.draw(mLevelText);
    target.draw(mLivesText);
    if(mPaused){
        target.draw(mPauseText);
    }
}

void Gameboard::drawAdditionalText(sf::RenderWindow& window, const sf::Text& additionalText)
{
    window.draw(additionalText);
}

sf::Text Gameboard::getLivesText()
{
    return mLivesText;
}

sf::Text& Gameboard::getLevelText()
{
    return mLevelText;
}

sf::Text Gameboard::getPauseText()
{
    sf::Text pauseText;
    initializeText(pauseText, 350, 550, "PAUSE", 36, sf::Color::Blue);
    return pauseText;
}

sf::Text Gameboard::getGameOverText()
{
    return mGameOverText;
}

sf::Text Gameboard::getCloseText()
{
    return mCloseText;
}

void Gameboard::updateScoreText()
{
    initializeText(mScoreText, 420, 5, "Score: " + std::to_string(mScore), 24, sf::Color::White);
}

void Gameboard::updateLevelText()
{
    mLevel++;
    initializeText(mLevelText, 240, 20, "Level: " + std::to_string(mLevel), 24, sf::Color::White);
}

sf::Text Gameboard::getRetryText()
{
    return mRetryText;
}