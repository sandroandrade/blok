#ifndef BOX2DSIMULATORPLUGIN_H
#define BOX2DSIMULATORPLUGIN_H

#include "box2dsimulatorplugin_global.h"

#include <../BlokInterfaces/iplugin.h>
#include <../BlokInterfaces/isimulator.h>

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class b2World;

class BOX2DSIMULATORPLUGINSHARED_EXPORT Box2DSimulatorPlugin
        : public ISimulator, public IPlugin, public b2ContactListener
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "br.com.stone.blok.box2dsimulatorplugin")
    Q_INTERFACES (ISimulator IPlugin)

public:
    Box2DSimulatorPlugin();
    virtual ~Box2DSimulatorPlugin();

    bool initialize();

public Q_SLOTS:
    void init();
    void start();
    void stop();
    void removeBody(QGraphicsItem *body);

protected:
    void timerEvent(QTimerEvent *event);

private:
    b2Body *createBody(b2World *world, float32 x, float32 y, float32 width,
                       float32 height, bool dynamic = true, float32 density = 1.0f,
                       float32 friction = 0.3f, float32 restitution = 0.5f);
    void updateBody(b2Body *body);
    virtual void BeginContact(b2Contact *contact);

    int _timerId;
    b2World *_world;
    QHash<QGraphicsItem *, b2Body *> m_itemBodyHash;
    QGraphicsItem *_player;
    b2Body *_ground;

    QString _playerString;
};

#endif // BOX2DSIMULATORPLUGIN_H
