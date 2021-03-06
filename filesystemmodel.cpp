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

//
// includes
//
#include "filesystemmodel.h"
#include "folderview.h"
#include <QDebug>

/**
 * @brief DragDropListModel::supportedDropActions
 * @return
 */
FileSystemModel::FileSystemModel( QObject *parent, const QString &path ) : QFileSystemModel( parent ) {
    // set root path
    this->setRootPath( path );
    this->setFilter( QDir::NoDotAndDotDot | QDir::System | QDir::NoDot | QDir::NoDotDot | QDir::AllEntries );
}

/**
 * @brief FileSystemModel::flags
 * @param index
 * @return
 */
Qt::ItemFlags FileSystemModel::flags( const QModelIndex &index ) const {
    if ( !index.isValid())
        return Qt::NoItemFlags;

    return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled  | Qt::ItemIsDragEnabled );
}

/**
 * @brief FileSystemModel::supportedDropActions
 * @return
 */
Qt::DropActions FileSystemModel::supportedDropActions() const {
    return Qt::CopyAction;
}
