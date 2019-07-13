#include "sworddecoratorplugin.h"

#include <QGraphicsRectItem>
#include <QPen>

SwordDecoratorPlugin::SwordDecoratorPlugin() :
    IBlokDecorator(nullptr)
{
}

bool SwordDecoratorPlugin::initialize()
{
    return true;
}

QGraphicsItem *SwordDecoratorPlugin::createPlayer()
{
    QGraphicsItem *parentItem = _decorated->createPlayer();

    QGraphicsRectItem *rect = new QGraphicsRectItem(-28, -28, 56, 56, parentItem);
    QBrush brush(QPixmap(":/resources/images/sword.png"));
    brush.setTransform(brush.transform().translate(-28, -28));
    rect->setBrush(brush);
    rect->setPen(QPen(Qt::NoPen));
    rect->setPos(56, 0);

    return parentItem;
}
