#ifndef DEFAULTBACKGROUND_H
#define DEFAULTBACKGROUND_H

#include "defaultblokskin_global.h"

#include "../BlokInterfaces/ibackground.h"

class DEFAULTBLOKSKINSHARED_EXPORT DefaultBackground : public IBackground
{
public:
    DefaultBackground();

    QPixmap pixmap();
};

#endif // DEFAULTBACKGROUND_H
