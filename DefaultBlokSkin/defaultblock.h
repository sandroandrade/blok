#ifndef DEFAULTBLOCK_H
#define DEFAULTBLOCK_H

#include "defaultblokskin_global.h"

#include "../BlokInterfaces/iblock.h"

class DEFAULTBLOKSKINSHARED_EXPORT DefaultBlock : public IBlock
{
public:
    DefaultBlock();

    QPixmap pixmap();
};

#endif // DEFAULTBLOCK_H
