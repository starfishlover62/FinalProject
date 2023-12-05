#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

#include "playerName.h"
#include "gameboard.h"
#include "alien.h"
#include "tank.h"
#include "bullet.h"
#include "enemies.h"
#include "player.h"

void quit(bool OUTPUT_FEEDBACK, const sf::Text quitText, sf::RenderWindow& window); // Closes the window

int main()
{

    const float FRAME_RATE = 60;

    //granularity used to update the game
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f/ FRAME_RATE);
    sf::Clock clock;
    //start the clock
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // output feedback for closed, paused, unpaused
    const bool OUTPUT_FEEDBACK = false;

    int SCREEN_RES_X = 1000, SCREEN_RES_Y = 800;
    sf::RenderWindow window(sf::VideoMode(1000,800),"Space Invaders");

    // Gets the player name from the player, and sets it
    PlayerName playerName;
    playerName.setPlayerName(window, OUTPUT_FEEDBACK);

    // check if the player's name is empty or contains only whitespace
    if(playerName.getPlayerName().find_first_not_of(" \t\n") == std::string::npos){
        playerName.setPlayerName("No Name");
    }

    Enemies* aliens = new Enemies(SCREEN_RES_X,SCREEN_RES_Y); // The group of enemies

    Player* p1 = new Player(SCREEN_RES_X,SCREEN_RES_Y,playerName); // The player

    
    // Initialize ground
    sf::Texture gTexture;
    gTexture.loadFromFile("./assets/siground.png");
    sf::Sprite gSprite;
    gSprite.setTexture(gTexture);
    gSprite.setTextureRect(sf::IntRect(85, 465, SCREEN_RES_X, 4));
    gSprite.setOrigin(400.f, 2.f);
    gSprite.setPosition(sf::Vector2f(400.f, 777.f));

    bool paused = false; // flag for paused game
    bool gameOver = false;
    bool reset = false;
    bool hardReset = false;

    // Used for quitting the game
    Gameboard gameboard(playerName.getPlayerName(), 0);
    sf::Text gameOverText = gameboard.getGameOverText(); // game over text
    sf::Text quitText = gameboard.getCloseText(); // quit text
    
    while (window.isOpen())
    {
        if(hardReset){ // If a hard reset has occured (reset player)
            if(p1 != nullptr){
                delete p1;
            }
            p1 = new Player(SCREEN_RES_X,SCREEN_RES_Y);
            reset = true; // A hard reset wiull also perform a soft reset afterwards
        }
        if(reset){ // If a soft reset has occured (reset enemies)
            paused = false;
            gameOver = false;
            reset = false;
            hardReset = false;
            if(aliens != nullptr){
                delete aliens;
            }
            aliens = new Enemies(SCREEN_RES_X,SCREEN_RES_Y);
        }

        
        // Booleans as to the state of their respective keys
        bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        bool space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        bool enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
        bool escape = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

        if((left && right) || (!left && !right)){ // If both (left and right) or neither (left or right) are pressed
            p1->noMoving();
        } else if((left || right)){ // If moving either left or right, but not both or neither
            p1->moving();
            if(left){
                p1->move(false);
            } else if(right){
                p1->move(true);
            }
        }

        if(space){ // Shoots a bullet
            p1->shoot();
        }

        if(escape){ // Quits the game
            quit(OUTPUT_FEEDBACK, quitText, window);
        }

        
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) { // X was pressed to close window
                quit(OUTPUT_FEEDBACK, quitText, window);
            } else if(event.type == sf::Event::Resized){ // Window was resized
                SCREEN_RES_X = event.size.width;
                SCREEN_RES_Y = event.size.height;
            } else if(event.type == sf::Event::KeyPressed) { // Used to detect if space bar was pressed
                if(event.key.code == sf::Keyboard::Enter){ // This is because pausing is a toggle, not a constant action
                    if(!gameOver){
                        paused = !paused;
                        if(paused){ // Freezes the aliens and pauses the game
                            aliens->freeze();
                            p1->freeze();
                            p1->pause();
                        } else { // Unfreezes and unpauses
                            aliens->unFreeze();
                            p1->unFreeze();
                            p1->unPause();
                        }
                    } else {
                        hardReset = true;
                        break;
                    }
                }
            }



            
        }
        timeSinceLastUpdate += clock.restart();
        if(!gameOver){
            while (timeSinceLastUpdate > TIME_PER_FRAME){
                timeSinceLastUpdate -= TIME_PER_FRAME;
                if(paused){
                    window.draw(*p1); // Draws player hud
                } else {
                    window.clear();

                    // Points scored by shooting an alien
                    int val = aliens->update(p1->bulletPtr());
                    if(val == -2){ // Indicates that there are no aliens left
                        reset = true;
                    } else if(val != -1){ // The player did hit an alien
                        p1->hideBullet();
                        p1->updateScore(val);
                    }

                    // Checks if the aliens are touching the ground, which will end the game in a loss
                    if(aliens->touchingPlayer(p1->tankPtr())){
                        gameOver = true;
                        p1->end();
                    } else if(aliens->checkCollision(p1->tankPtr())){ // If not, then checks collision between alien shots and the player
                        if(!p1->loseLife()){
                            gameOver = true;
                            p1->end();
                        }
                    }
                    
                    p1->update(); // Updates the player bullet and invincibility state
                    aliens->update(); // Advances the aliens

                    window.draw(gSprite); // Draws ground
                    window.draw(*p1); // Draws hud, tank, and player bullet
                    window.draw(*aliens); // Draws aliens and their bullets
                }
                window.display(); // Updates the display to show changes
            }
        }
    }

    // Frees memory if needed

    if(p1 != nullptr){
        delete p1;
    }
    if(aliens != nullptr){
        delete aliens;
    }
    return 0;

}

/**
 * @brief Closes the window
 * 
 * @param OUTPUT_FEEDBACK, message to be printed to console if desired
 * @param quitText, the closing screen text
 * @param window, the window to close
 */
void quit(bool OUTPUT_FEEDBACK, const sf::Text quitText, sf::RenderWindow& window){
    window.draw(quitText);
    window.display();
    sf::sleep(sf::seconds(0));
    
    window.close();  // Close the window
    
}