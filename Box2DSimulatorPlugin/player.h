#ifndef PLAYER_H
#define PLAYER_H

#include "../BlokInterfaces/iblokcomponent.h"

class Player : public IBlokComponent
{
public:
    Player();

    QGraphicsItem *createPlayer();
};

#endif // PLAYER_H
