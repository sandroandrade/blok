#ifndef ISIMULATOR_H
#define ISIMULATOR_H

#include "blokinterfaces_global.h"

#include <QObject>

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

public Q_SLOTS:
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void removeBody(QGraphicsItem *body) = 0;

protected:
    QGraphicsScene *_scene;
    IBlockBuilder *_blockBuilder;
    ISkinFactory *_skinFactory;
};

Q_DECLARE_INTERFACE(ISimulator, "br.com.stone.blok.isimulator")

#endif // ISIMULATOR_H
