#ifndef ALIEN_H
#define ALIEN_H

class Alien {

public:
    Alien();

    int x() const { return positionX; }
    int y() const { return positionY; }




private:
    int positionX, positionY;


};




#endif