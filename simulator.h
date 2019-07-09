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

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QtCore/QList>
#include <QtCore/QObject>

#include <QtCore/QSharedPointer>

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class b2World;
class b2Body;

class Simulator : public QObject, public b2ContactListener
{
    Q_OBJECT
public:
    explicit Simulator(QObject *parent = 0);
    virtual ~Simulator();

Q_SIGNALS:
    void bodiesUpdated(const QList<b2Body *> &bodies);
    void bodiesCreated(const QList<b2Body *> &bodies);
    void youWon();
    void youLost();
    
public Q_SLOTS:
    void init();
    void start();
    void stop();
    void removeBody(b2Body *body);

protected:
    void timerEvent(QTimerEvent *event);

private:
    b2Body *createBody(float32 x, float32 y, float32 width, float32 height, bool dynamic = true, float32 density = 1.0f, float32 friction = 0.3f, float32 restitution = 0.5f);
    void updateBody(b2Body *body);
    virtual void BeginContact(b2Contact *contact);

    int _timerId;
    b2World *_world;
    QList<b2Body *> m_bodies;
    b2Body *_player;
    b2Body *_ground;

    QString _playerString;
};

#endif // SIMULATOR_H
