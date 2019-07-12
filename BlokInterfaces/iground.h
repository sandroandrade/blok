#ifndef IGROUND_H
#define IGROUND_H

#include "blokinterfaces_global.h"

#include <QPixmap>

class BLOKINTERFACESSHARED_EXPORT IGround
{
public:
    virtual ~IGround();
    virtual QPixmap pixmap() = 0;
};

#endif // IGROUND_H
