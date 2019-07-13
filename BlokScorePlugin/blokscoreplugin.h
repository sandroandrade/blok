#ifndef BLOKSCOREPLUGIN_H
#define BLOKSCOREPLUGIN_H

#include "blokscoreplugin_global.h"

#include <QObject>
#include "../BlokInterfaces/iplugin.h"

class QGraphicsTextItem;

class BLOKSCOREPLUGINSHARED_EXPORT BlokScorePlugin
        : public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "br.com.stone.blok.blokscoreplugin")
    Q_INTERFACES (IPlugin)

public:
    BlokScorePlugin();
    bool initialize() Q_DECL_OVERRIDE;

private Q_SLOTS:
    void blockRemoved();
    void init();

private:
    QGraphicsTextItem *_textItem;
    int _counter;
};

#endif // BLOKSCOREPLUGIN_H
