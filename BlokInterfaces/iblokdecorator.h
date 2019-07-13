#ifndef IBLOKDECORATOR_H
#define IBLOKDECORATOR_H

#include "blokinterfaces_global.h"
#include "iblokcomponent.h"
#include <QtPlugin>

class IBlokComponent;

class BLOKINTERFACESSHARED_EXPORT IBlokDecorator : public IBlokComponent
{
public:
    explicit IBlokDecorator(IBlokComponent *decorated);
    virtual ~IBlokDecorator();

    void setDecorated(IBlokComponent *decorated);

protected:
    IBlokComponent *_decorated;
};

Q_DECLARE_INTERFACE (IBlokDecorator, "br.com.stone.blok.iblokdecorator")

#endif // IBLOKDECORATOR_H
