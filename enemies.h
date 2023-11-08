#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

#include "alien.h"




#include <iostream>




class Enemies{

public:
    enum enemyType {squid, crab, jellyfish};
    Enemies();

    

protected:

    std::vector<Alien *> aliens;

    int numRows;
    int numPerRow;
    int * formation;
    



};

#endif