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
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QUrl>
#include "garminlistmodel.h"
#include "garmintreemodel.h"

///
/// \class Controller
/// \brief The Controller class
///
class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject* parent = nullptr);

    // ------------- Actions for the UI ------------------

    ///
    /// \brief Look for routes, tracks and waypoints in the given file
    /// and shows them in the list views routes, tracks, waypoints respectively
    /// \param gpx file
    ///
    Q_INVOKABLE void onOpenFile(QUrl fileUrl);

    ///
    /// \brief Looks for all GPX-files which are
    /// loacted in the mounted volumes/devices in folder "Garmin/GPX".
    /// and shows them in the treeview
    ///
    Q_INVOKABLE void onLoadGarminDevices();

    ///
    /// \brief Loads the Garmn GPX file selected in the treeview
    /// and shows them in the list views routes, tracks, waypoints respectively
    /// \param index = QModelIndex returned by click event of the treeview
    ///
    Q_INVOKABLE void onTreeviewClicked(QModelIndex index);

    // -------------  Getters for the model needed by the UI ------------

    GarminListModel& garminListModel(); // Listviews in the splitview
    GarminTreeModel& garminTreeModel(); // Treeview in the splitview

private:
    GarminListModel m_garminListModel;
    GarminTreeModel m_garminTreeModel;
};

#endif // CONTROLLER_H
