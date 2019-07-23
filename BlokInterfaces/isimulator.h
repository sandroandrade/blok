#ifndef ISIMULATOR_H
#define ISIMULATOR_H

#include "blokinterfaces_global.h"

#include <QObject>
#include <QPointF>

class QGraphicsScene;
class IBlockBuilder;
class ISkinFactory;
class QGraphicsItem;

class BLOKINTERFACESSHARED_EXPORT ISimulator : public QObject
{
    Q_OBJECT

public:
    explicit ISimulator(QObject *parent = nullptr);
    void configure(QGraphicsScene *scene,
                   IBlockBuilder *blockBuilder,
                   ISkinFactory *skinFactory);
    virtual ~ISimulator();

Q_SIGNALS:
    void youWon();
    void youLost();
    void blockRemoved(QPointF removedBlockPosition,
                      const QList<QPointF> &blockPositions,
                      const QPointF &playerPosition);

public Q_SLOTS:
    virtual void removeAllBodies(bool notify = true) = 0;
    virtual void recreate(QList<QPointF> allBlocksPosition,
                          QPointF playerPosition) = 0;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void removeBody(QGraphicsItem *body, bool notify = true) = 0;

protected:
    QGraphicsScene *_scene;
    IBlockBuilder *_blockBuilder;
    ISkinFactory *_skinFactory;
};

Q_DECLARE_INTERFACE(ISimulator, "br.com.stone.blok.isimulator")

#endif // ISIMULATOR_H
