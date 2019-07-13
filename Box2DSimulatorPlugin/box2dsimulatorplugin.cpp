#include "box2dsimulatorplugin.h"

#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <QTimerEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>

#include "../BlokInterfaces/iblockbuilder.h"
#include "../BlokInterfaces/iskinfactory.h"
#include "../BlokInterfaces/iblock.h"
#include "../BlokInterfaces/icore.h"
#include "../BlokInterfaces/iplugincontroller.h"
#include "../BlokInterfaces/iblokdecorator.h"

#include "player.h"

static const float32 B2_TIMESTEP = 1.0f / 30.0f;    // krazy:exclude=staticobjects
static const int32 B2_VELOCITY_ITERATIONS = 8;      // krazy:exclude=staticobjects
static const int32 B2_POSITION_ITERATIONS = 4;      // krazy:exclude=staticobjects

Box2DSimulatorPlugin::Box2DSimulatorPlugin()
    : _timerId(0),
      _world (nullptr),
      _player(nullptr),
      _ground(nullptr),
      _playerString("Player")
{
}

Box2DSimulatorPlugin::~Box2DSimulatorPlugin()
{
    delete _world;
}

bool Box2DSimulatorPlugin::initialize()
{
    return true;
}

void Box2DSimulatorPlugin::init()
{
    delete _world;
    _world = new b2World(b2Vec2(0.0f, -10.0f));
    _world->SetContactListener(this);
    m_itemBodyHash.clear();

    // Ground
    _ground = createBody(_world, 0.0f, -260.0f, 900.0f, 20.0f, false);

    QGraphicsRectItem *rect = nullptr;

    // Blocks
    for (auto point : _blockBuilder->buildBlocks()) {
        b2Body *body = createBody(_world, point.x(), point.y(), 28.0f, 28.0f);
        const b2Vec2 &position = body->GetPosition();
        rect = _scene->addRect(-14, -14, 28, 28);
        QBrush brush(_skinFactory->createBlock()->pixmap());
        brush.setTransform(brush.transform().translate(-14, -14));
        rect->setBrush(brush);
        rect->setPos(static_cast<qreal>(position.x), static_cast<qreal>(-position.y));
        rect->setPen(QPen(Qt::NoPen));
        m_itemBodyHash[rect] = body;
    }

    // Player
    IBlokComponent *component = new Player;
    for (auto decorator :
        ICore::instance()->pluginController()->loadedPlugins<IBlokDecorator>())
    {
        decorator->setDecorated(component);
        component = decorator;
    }
    _player = component->createPlayer();
    _scene->addItem(_player);

    b2Body *playerBody = createBody(_world, 0, 100, 56.0f, 56.0f);
    _player->setPos(0, -100);
    playerBody->SetUserData(&_playerString);
    m_itemBodyHash[_player] = playerBody;
}

void Box2DSimulatorPlugin::start()
{
    if (!_timerId)
        _timerId = startTimer(3);
}

void Box2DSimulatorPlugin::stop()
{
    killTimer(_timerId);
    _timerId = 0;
}

void Box2DSimulatorPlugin::removeBody(QGraphicsItem *body)
{
    b2Body *clickedBody = m_itemBodyHash.value(body);
    if (!clickedBody || clickedBody->GetUserData())
        return;

    _world->DestroyBody(clickedBody);
    m_itemBodyHash.remove(body);
    _scene->removeItem(body);
    emit blockRemoved();

    if (m_itemBodyHash.size() == 2)
    {
        stop();
        emit youWon();
    }
}

void Box2DSimulatorPlugin::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == _timerId)
    {
        _world->Step(B2_TIMESTEP, B2_VELOCITY_ITERATIONS, B2_POSITION_ITERATIONS);
        for (QGraphicsItem *item : m_itemBodyHash.keys())
        {
            const b2Vec2 &pos = m_itemBodyHash[item]->GetPosition();
            item->setPos(static_cast<qreal>(pos.x), static_cast<qreal>(-pos.y));
        }
    }
    QObject::timerEvent(event);
}

b2Body *Box2DSimulatorPlugin::createBody(b2World *world, float32 x, float32 y, float32 width, float32 height, bool dynamic, float32 density, float32 friction, float32 restitution)
{
    b2BodyDef bodyDef;
    if (dynamic)
        bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    b2Body *body = world->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(width/2, height/2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    body->CreateFixture(&fixtureDef);
    body->SetSleepingAllowed(true);

    return body;
}

void Box2DSimulatorPlugin::BeginContact(b2Contact *contact)
{
    if ((contact->GetFixtureA()->GetBody() == _ground && contact->GetFixtureB()->GetBody() == m_itemBodyHash[_player]) ||
        (contact->GetFixtureB()->GetBody() == _ground && contact->GetFixtureA()->GetBody() == m_itemBodyHash[_player]))
    {
        stop();
        emit youLost();
    }
}
