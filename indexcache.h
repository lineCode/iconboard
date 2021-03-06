/*
 * Copyright (C) 2017 Zvaigznu Planetarijs
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 *
 */

#pragma once

//
// includes
//
#include <QHash>
#include "singleton.h"
#include "filestream.h"

/**
 * @brief The Entry struct
 */
struct Entry {
    explicit Entry( const QString &a = QString::null, const QString &f = QString::null ) : alias( a ), fileName( f ) {}
    QString alias;
    QString fileName;
};
Q_DECLARE_METATYPE( Entry )

// read/write operators
inline static QDataStream &operator<<( QDataStream &out, const Entry &e ) { out << e.alias << e.fileName; return out; }
inline static QDataStream &operator>>( QDataStream &in, Entry &e ) { in >> e.alias >> e.fileName; return in; }

/**
 * @brief The Match struct
 */
struct Match {
    explicit Match( const QString &f = QString::null, int s = 0 ) : fileName( f ), scale( s ) {}
    QString fileName;
    int scale;
};
Q_DECLARE_METATYPE( Match )

/**
 * @brief MatchList
 */
typedef QList<Match> MatchList;
Q_DECLARE_METATYPE( MatchList )

/**
 * @brief The IndexCacheNamespace namespace
 */
namespace IndexCacheNamespace {
    static const quint8 Version = 1;
    static const QString IndexFilename( "icons.index" );
}

/**
 * @brief The IndexCache class
 */
class IndexCache : public QObject {
    Q_OBJECT
    Q_PROPERTY( QString path READ path WRITE setPath )

public:
    static IndexCache *instance() { return Singleton<IndexCache>::instance( IndexCache::createInstance ); }
    ~IndexCache() {}
    QIcon icon( const QString &iconName, int scale, const QString &theme );
    QString path() const { return this->m_path; }
    int badEntries() const { return this->m_badEntries; }

public slots:
    void shutdown();

private slots:
    void setPath( const QString &path ) { this->m_path = path; }
    void setValid( bool valid ) { this->m_valid = valid; }

private:
    IndexCache( QObject *parent = nullptr );
    static IndexCache *createInstance() { return new IndexCache(); }
    FileStream indexFile;
    QHash<QString, Entry> index;
    QString m_path;
    bool m_valid;
    bool read();
    bool write( const QString &iconName, int iconScale, const QString &theme, const QString &fileName );
    bool isValid() const { return this->m_valid; }
    MatchList matchList( const QString &iconName, const QString &theme ) const;
    Match readIconFile( const QString &fileName, bool &ok, int recursionLevel ) const;
    int parseSVG( const QString &buffer ) const;
    Match bestMatch( const QString &iconName, int scale, const QString &theme ) const;
    bool contains( const QString &alias ) const { return this->index.contains( alias ); }
    Entry indexEntry( const QString &alias ) const { return this->index[alias]; }
    int m_badEntries;
};
