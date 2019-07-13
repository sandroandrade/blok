#include "player.h"

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

Player::Player()
{
}

QGraphicsItem *Player::createPlayer()
{
    QGraphicsRectItem *rect = new QGraphicsRectItem(-28, -28, 56, 56);
    QBrush brush(QPixmap(QString(":/resources/images/player%1.png").arg(qrand()%9)));
    brush.setTransform(brush.transform().translate(-28, -28));
    rect->setBrush(brush);
    rect->setPen(QPen(Qt::NoPen));

    return rect;
}
