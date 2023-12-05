# Space Invaders
Space invaders is a popular arcade game that was first released in Japan on April 1, 1978. It was then released in North America in November of 1978. The game is simple in design. A grid of aliens are attacking Earth. It is your job, as the pilot of a tank, to fend them off and save the planet. Your tank features missiles, and you have to use them to destroy the alien ships. Be warned though, the aliens do not take kindly to being shot at, and will shoot back. You must dodge these attacks, otherwise the planet will be destroyed. You have three lives before your game is over. Succesfully defeat a wave of aliens, and another one will come. Your score will carry over between these waves, so try to receive the highest score possible.


Jump to section:

1. [Setup](#Setup)
2. [Playing](#playing-the-game)

# Setup

## Installation
A c++ compiler of some sort, as well as the sfml library is required to compile the program. These instructions use the GNU g++ compiler
### Automatic
* Run the install script:  `bash ./install.sh`

Note that the script requires root access to install the dependencies. If it does not work, ensure that you are either the root user, or run with `sudo`. If it still does not work, try the manual installation method below.
### Manual

* Verify that g++ and libsfml-dev are installed on the system
`dpkg -s g++` and `dpkg -s libsfml-dev`

If the output of either commands looks like: 
```
dpkg-query package <package> is not installed and no information is available
use dpkg --info (= dpkg-deb --info) to examine archive files
```

Then the package is not installed. To install the package, run either:

`sudo apt install g++ ` or `sudo apt-get install libsfml-dev `,
depending on which package is missing.

## Compiling

To compile, run the compile script with: `bash ./compile.sh`
Alternatively, copy and paste the following command into the terminal, and press enter:
    `g++ ./source/*.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system`

## Launching
To launch, Simply run the command: `./sfml-app`

Simple c++ implementation of the classic arcade game 'Space Invaders'.

Use the left/right arrow keys to move your tank along the ground.
Use space bar to fire a missile. Your objective is to eliminate all of the aliens
before they either hit you with a missile or eat you.
Press enter to pause the game
Press escape or click the 'x' in the top right corner to exit the game.


# Playing the game

## Controls
* (Right Arrow / D) ~ move right
* (Left Arrow / A) ~ move left
* (Space) ~ Fire shot
* (Enter) ~ Pause the game
* (Escape) ~ Exit the game

## Tips
* You can only have a single missile on the screen at a time, so aim wisely. 
* After getting hit, you will have two seconds of invulnerability to get out of the way of other shots. You will not be able to fire a missile during this time period
* The mysterious UFO floats across the top of the screen. It is infrequent and offers a lot of points when shot.