#!/bin/bash

sudo apt install g++
sudo apt-get install libsfml-dev

touch compile.sh
echo "g++ *.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system" > compile.sh
sudo chmod u+x compile.sh
