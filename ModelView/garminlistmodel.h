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
#ifndef GARMINLISTMODEL_H
#define GARMINLISTMODEL_H

#include <QAbstractListModel>
#include "garmingpxfile.h"

///
/// \class GarminListModel
/// \brief Represents the "Model Controler" for a Garmin GPX file
///
class GarminListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(GpxRoles)

public:
    explicit GarminListModel(QObject* parent = nullptr);

    enum GpxRoles {
        RouteRole = Qt::UserRole + 1,
        TrackRole,
        WaypointRole
    };

    void parse(QFile& file);

    //----- Functions for Qt's data model ------
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    //----- Manipulate routes, tracks, waypoints lists -----
    void appendRoute(const QString& route);
    void appendTrack(const QString& track);
    void appendWaypoint(const QString& waypoint);

    //----- Access to the model -----
    QStringList routesList() const;
    QStringList tracksList() const;
    QStringList waypointsList() const;

    GarminGpxFile& garminGpxFile();

    //----- Define Roles -----
    QHash<int, QByteArray> roleNames() const override;

signals:
    void modelChanged();

private:
    // Roles for displaying
    QHash<int, QByteArray> m_roles;

    // Model
    GarminGpxFile m_garminGpxFile;
};


#endif // GARMINLISTMODEL_H
