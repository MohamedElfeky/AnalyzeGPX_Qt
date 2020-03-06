/****************************************************************************
**
** Copyright (C) 2020 Manfred Kern. All rights reserved.
** Contact: manfred.kern@gmail.com
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** 3. All advertising materials mentioning features or use of this software
**    must display the following acknowledgement:
**    This product includes software developed by the the organization.
**
** 4. Neither the name of the copyright holder nor the names of its
**    contributors may be used to endorse or promote products derived from
**    this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/
#include <algorithm>
#include "garminlistmodel.h"
#include "garmingpxfile.h"

GarminListModel::GarminListModel(QObject* parent)
    : QAbstractListModel(parent)
{
    // Display roles
    m_roles[RouteRole] = "route";
    m_roles[TrackRole] = "track";
    m_roles[WaypointRole] = "waypoint";

}

void GarminListModel::parse(QFile& file)
{
    beginResetModel();
    m_garminGpxFile.parse(file);
    endResetModel();
}

// ----- Functions for Qt's data model -----

QVariant GarminListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)

    switch (role) {
    case RouteRole:
        return QVariant(QString(tr("Routes")));
    case TrackRole:
        return QVariant(QString(tr("Tracks")));
    case WaypointRole:
        return QVariant(QString(tr("Waypoints")));
    default:
        return QVariant();
    }
}

int GarminListModel::rowCount(const QModelIndex& parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return std::max({routesList().size(), tracksList().size(), waypointsList().size()});
}

QVariant GarminListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case RouteRole:
        if (index.row() < routesList().size())
            return QVariant(routesList().at(index.row()));
        else
            return "";
    case TrackRole:
        if (index.row() < tracksList().size())
            return QVariant(tracksList().at(index.row()));
        else
            return "";
    case WaypointRole:
        if (index.row() < waypointsList().size())
            return QVariant(waypointsList().at(index.row()));
        else
            return "";
    }
    return QVariant();
}

// ----- Manipulate routes, tracks, waypoints lists ----

void GarminListModel::appendRoute(const QString& route)
{
    // TODO: inform model
    m_garminGpxFile.appendRoute(route);
}

void GarminListModel::appendTrack(const QString& track)
{
    // TODO: inform model
    m_garminGpxFile.appendTrack(track);
}

void GarminListModel::appendWaypoint(const QString& waypoint)
{
    // TODO: inform model
    m_garminGpxFile.appendWaypoint(waypoint);
}

// ----- Getters & Setters -----

QStringList GarminListModel::routesList() const
{
    return m_garminGpxFile.rteList();
}

QStringList GarminListModel::tracksList() const
{
    return m_garminGpxFile.trkList();
}

QStringList GarminListModel::waypointsList() const
{
    return m_garminGpxFile.wptList();
}

// ----- Roles to display the model -----

QHash<int, QByteArray> GarminListModel::roleNames() const
{
    return m_roles;
}

GarminGpxFile& GarminListModel::garminGpxFile()
{
    return m_garminGpxFile;
}

