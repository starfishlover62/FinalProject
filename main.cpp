#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <iostream>
// #include <vector>
// #include <time.h>
#include "playerName.h"
#include "gameboard.h"
#include "alien.h"
#include "tank.h"
#include "bullet.h"
#include "enemies.h"
#include "player.h"

void quit(bool OUTPUT_FEEDBACK, const sf::Text quitText, sf::RenderWindow& window);

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

    PlayerName playerName;
    
    // comment out to skip enter name screen
    //playerName.setPlayerName(window, OUTPUT_FEEDBACK);

    // check if the player's name is empty or contains only whitespace
    if(playerName.getPlayerName().find_first_not_of(" \t\n") == std::string::npos)
    {
        playerName.setPlayerName("No Name");
    }

    Gameboard gameboard(playerName.getPlayerName(), 0);

    Enemies* aliens = new Enemies(SCREEN_RES_X,SCREEN_RES_Y);

    Player* p1 = new Player(SCREEN_RES_X,SCREEN_RES_Y);

    
    //initialize ground
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
  
    // sf::Text levelText = gameboard.getLevelText(); // level text
    // levelText = gameboard.getLevelText(); // increment to level 1

    // sf::Text pauseText = gameboard.getPauseText(); // pause text
    sf::Text gameOverText = gameboard.getGameOverText(); // game over text
    sf::Text quitText = gameboard.getCloseText(); // quit text

    // sf::Text retryText = gameboard.getRetryText(); // retry text
    // sf::Text livesText = gameboard.getLivesText(); // lives text

    
    int tankRespawnDelay = 0; // variable for respawning tank
    
    while (window.isOpen())
    {
        if(hardReset){
            std::cout << "hard" << std::endl;
            if(p1 != nullptr){
                delete p1;
            }
            p1 = new Player(SCREEN_RES_X,SCREEN_RES_Y);
            reset = true;
        }
        if(reset){
            std::cout << "soft" << std::endl;
            paused = false;
            gameOver = false;
            reset = false;
            hardReset = false;
            if(aliens != nullptr){
                delete aliens;
            }
            aliens = new Enemies(SCREEN_RES_X,SCREEN_RES_Y);
        }
        timeSinceLastUpdate += clock.restart();
        sf::Event event;

        bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        bool space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        bool enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
        bool escape = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

        if((left && right) || (!left && !right)){ // If both (left and right) or neither (left or right) are pressed
            p1->noMoving();
        } else if((left || right)){
            p1->moving();
            if(left){
                p1->move(false);
            } else if(right){
                p1->move(true);
            }
        }

        if(space){
            p1->shoot();
        }

        if(escape){
            quit(OUTPUT_FEEDBACK, quitText, window);
        }


        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) { // X was pressed to close window
                quit(OUTPUT_FEEDBACK, quitText, window);
            } else if(event.type == sf::Event::Resized){ // Window was resized
                SCREEN_RES_X = event.size.width;
                SCREEN_RES_Y = event.size.height;

                // Need to add call to enemies to update as well as to tank class


            } else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Enter){
                    if(!gameOver){
                        paused = !paused;
                        if(paused){
                            aliens->freeze();
                            p1->freeze();
                            p1->pause();
                        } else {
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
        if(!gameOver){
            while (timeSinceLastUpdate > TIME_PER_FRAME){
                timeSinceLastUpdate -= TIME_PER_FRAME;
                if(paused){
                    window.draw(*p1);
                } else {
                    window.clear();
                // draw name and score
                
                    
                    
                    int val = aliens->update(p1->bulletPtr());
                    if(val == -2){
                        reset = true;
                    } else if(val != -1){
                        p1->hideBullet();
                        p1->updateScore(val);
                    }

                    if(aliens->checkCollision(p1->tankPtr())){
                        if(!p1->loseLife()){
                            gameOver = true;
                            p1->end();
                            std::cout << "out of lives" << std::endl;
                        }
                    }
                    
                    
                    
                    
                    
                    p1->update();
                    aliens->update();

                    window.draw(gSprite); // Draws ground
                    window.draw(*p1); // Draws hud, tank, and player bullet
                    window.draw(*aliens); // Draws aliens and their bullets
                }
                window.display(); // Updates the display to show changes
            }
        }
    }
    if(p1 != nullptr){
        delete p1;
    }
    if(aliens != nullptr){
        delete aliens;
    }
    return 0;

}

void quit(bool OUTPUT_FEEDBACK, const sf::Text quitText, sf::RenderWindow& window){
    // for debugging/feedback
    if (OUTPUT_FEEDBACK) std::cerr << "Game Closed\n";
    
    window.draw(quitText);
    window.display();
    sf::sleep(sf::seconds(0));
    
    window.close();  // Close the window
    
}