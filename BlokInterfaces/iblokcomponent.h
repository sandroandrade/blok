#ifndef IBLOKCOMPONENT_H
#define IBLOKCOMPONENT_H

#include "blokinterfaces_global.h"

class QGraphicsItem;

class BLOKINTERFACESSHARED_EXPORT IBlokComponent
{
public:
    virtual ~IBlokComponent();

    virtual QGraphicsItem *createPlayer() = 0;
};

#endif // IBLOKCOMPONENT_H
