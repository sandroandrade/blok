/********************************************************************************
 *   Copyright (C) 2012 by Sandro Andrade <sandroandrade@kde.org>               *
 *                                                                              *
 *   This program is free software; you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or          *
 *   (at your option) any later version.                                        *
 *                                                                              *
 *   This program is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 *   GNU General Public License for more details.                               *
 *                                                                              *
 *   You should have received a copy of the GNU General Public License          *
 *   along with this program; if not, write to the                              *
 *   Free Software Foundation, Inc.,                                            *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .             *
 *******************************************************************************/

#include "simulator.h"

#include <QtCore/QDebug>
#include <QtCore/QTimerEvent>

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

static const float32 B2_TIMESTEP = 1.0f / 30.0f;    // krazy:exclude=staticobjects
static const int32 B2_VELOCITY_ITERATIONS = 8;      // krazy:exclude=staticobjects
static const int32 B2_POSITION_ITERATIONS = 4;      // krazy:exclude=staticobjects
static const float PI = 3.14159265359;

Simulator::Simulator(QObject *parent) :
    QObject(parent), _timerId(0), _world (0), _player(0), _ground(0), _playerString("Player")
{
}

Simulator::~Simulator()
{
    delete _world;
}

void Simulator::BeginContact(b2Contact *contact)
{
    if ((contact->GetFixtureA()->GetBody() == _ground && contact->GetFixtureB()->GetBody() == _player) ||
        (contact->GetFixtureB()->GetBody() == _ground && contact->GetFixtureA()->GetBody() == _player))
    {
        stop();
        emit youLost();
    }
}

void Simulator::start()
{
    if (!_timerId)
        _timerId = startTimer(3);
}

void Simulator::stop()
{
    killTimer(_timerId);
    _timerId = 0;
}

void Simulator::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == _timerId)
    {
        _world->Step(B2_TIMESTEP, B2_VELOCITY_ITERATIONS, B2_POSITION_ITERATIONS);
        emit bodiesUpdated(m_bodies);
    }
    QObject::timerEvent(event);
}

void Simulator::init()
{
    delete _world;
    _world = new b2World(b2Vec2(0.0f, -10.0f));
    _world->SetContactListener(this);
    m_bodies.clear();

    // Ground
    _ground = createBody(0.0f, -260.0f, 900.0f, 20.0f, false);

    // Blocks
    int i, j;
    for (i = 0; i < 10; ++i)
        for (j = 0; j < 11 - i; ++j)
           m_bodies.append(createBody(-150.0f+15*i+30*j, -236.0f+30*i, 28.0f, 28.0f));

    // Player
    j-=2;
    m_bodies.append(_player = createBody(-150.0f+15*i+30*j, -236.0f+30*i+14, 56.0f, 56.0f));
    _player->SetUserData(&_playerString);

    emit bodiesCreated(m_bodies);
}

b2Body *Simulator::createBody(float32 x, float32 y, float32 width, float32 height, bool dynamic, float32 density, float32 friction, float32 restitution)
{
    b2BodyDef bodyDef;
    if (dynamic)
        bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    b2Body *body = _world->CreateBody(&bodyDef);
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

void Simulator::removeBody(b2Body *body)
{
    _world->DestroyBody(body);
    m_bodies.removeAll(body);
    if (m_bodies.size() == 2)
    {
        stop();
        emit youWon();
    }
}
