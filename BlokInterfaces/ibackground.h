#ifndef IBACKGROUND_H
#define IBACKGROUND_H

#include "blokinterfaces_global.h"

#include <QPixmap>

class BLOKINTERFACESSHARED_EXPORT IBackground
{
public:
    virtual ~IBackground();
    virtual QPixmap pixmap() = 0;
};

#endif // IBACKGROUND_H
