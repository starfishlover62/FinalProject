# FinalProject

`Final Project`

Installation:
    Run the installer: `sudo bash ./install.sh`
    Then, to launch, run: `./compile.sh`, If that does not work, try `bash ./compile.sh`
    If neither of the above work, follow the manual installation below:

Install g++ compiler: `sudo apt install g++`

Install SFML library: `sudo apt-get install libsfml-dev`

Compile with: `g++ *.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system`

Launching:
    Simply run the command: `./sfml-app`

Simple c++ implementation of the classic arcade game 'Space Invaders'.

Use the left/right arrow keys to move your tank along the ground.
Use space bar to fire a missile. Your objective is to eliminate all of the aliens
before they either hit you with a missile or eat you.
Press enter to pause the game
Press escape or click the 'x' in the top right corner to exit the game.
