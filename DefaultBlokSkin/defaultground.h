#ifndef DEFAULTGROUND_H
#define DEFAULTGROUND_H

#include "defaultblokskin_global.h"

#include "../BlokInterfaces/iground.h"

class DEFAULTBLOKSKINSHARED_EXPORT DefaultGround : public IGround
{
public:
    DefaultGround();

    QPixmap pixmap();
};

#endif // DEFAULTGROUND_H
