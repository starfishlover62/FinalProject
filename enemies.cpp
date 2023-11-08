#include "enemies.h"


Enemies::Enemies(){
    numRows = 5;
    numPerRow = 11;
    formation = new int[numRows] {squid,crab,crab,jellyfish,jellyfish};
    for(int i = 0; i < numRows; ++i){
        for(int j = 0; j < numPerRow; ++j){
            if(formation[i] == squid){
                std::cout << i << ": squid" << std::endl;
            } else if(formation[i] == crab){
                std::cout << i << ": crab" << std::endl;
            }  else if(formation[i] == jellyfish){
                std::cout << i << ": jellyfish" << std::endl;
            }
        }
    }
    delete formation;
}