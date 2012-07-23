/*
    SuperCollider Qt IDE
    Copyright (c) 2012 Jakob Leben & Tim Blechmann
    http://www.audiosynth.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#ifndef SCIDE_SESSION_MANAGER_HPP_INCLUDED
#define SCIDE_SESSION_MANAGER_HPP_INCLUDED

#include <QObject>
#include <QDir>
#include <QStringList>
#include <QSettings>

namespace ScIDE {

class DocumentManager;

struct Session : public QSettings
{
    Session( const QString & file, const QString & name, Format format, QObject * parent = 0 ):
        QSettings(file, format, parent),
        mName(name)
    {}

    const QString & name() { return mName; }

private:
    QString mName;
};

class SessionManager : public QObject
{
    Q_OBJECT

public:
    SessionManager( DocumentManager *, QObject * parent = 0 );

    QDir sessionsDir();
    QStringList availableSessions();
    QString lastSession();

    void newSession();
    void saveSession();
    Session * saveSessionAs( const QString & name );
    Session * openSession( const QString & name );
    void removeSession( const QString & name );
    void renameSession( const QString & oldName, const QString & newName );
    Session *currentSession() { return mSession; }

signals:
    void saveSessionRequest(Session * session);
    void loadSessionRequest(Session * session);
    void currentSessionChanged(Session * session);

private:
    void closeSession();
    bool saveLastSession( const QDir & dir, const QString & file );
    DocumentManager *mDocMng;
    Session *mSession;
};

} // namespace ScIDE

#endif // SCIDE_SESSION_MANAGER_HPP_INCLUDED
