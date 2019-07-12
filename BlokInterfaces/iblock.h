#ifndef IBLOCK_H
#define IBLOCK_H

#include "blokinterfaces_global.h"

#include <QPixmap>

class BLOKINTERFACESSHARED_EXPORT IBlock
{
public:
    virtual ~IBlock();
    virtual QPixmap pixmap() = 0;
};

#endif // IBLOCK_H
