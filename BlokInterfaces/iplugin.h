#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "blokinterfaces_global.h"

#include <QtPlugin>

class BLOKINTERFACESSHARED_EXPORT IPlugin
{
public:
    virtual ~IPlugin();

    virtual bool initialize() = 0;
};

Q_DECLARE_INTERFACE(IPlugin, "br.com.stone.blok.iplugin")

#endif // IPLUGIN_H
