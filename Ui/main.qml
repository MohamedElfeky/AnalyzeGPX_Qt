import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQuick.Dialogs 1.3


// Qt bug on Mac of the MessageDialog
// Either set the modality to Qt.ApplicationModal or
// wrap the "ApplicationWindow" in an "Item", so
// that a MessageDialog can be shown as a sepeated window.
// In order that the ApplicationWindow is shown,
// "Component.onCompleted: show()" has to be called
// And in order that the MessageDialog can be referenced
// a property alias is needed "property alias aboutMessage: aboutMessage"

ApplicationWindow {
    id: root
    visible: true
    title: qsTr("Analyze GPX file")
    height: 768
    width: 1024
    minimumHeight: openFileButton.height + 200
    minimumWidth: openFileButton.width + 400

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Help")

            MenuItem {
                text: qsTr("About");
                onTriggered: {
                    aboutMessage.detailedText = controller.onShowAboutMessage()
                    aboutMessage.open()
                }
//                onTriggered: aboutMessage.open()
            }

            //            Action {
            //                         onTriggered: aboutMessage.open()
            //            }

        }
    }

    SplitView {
        // On the left a tree view is shown for the directories and gpx files
        // On the right, there are the list views for tracks, routes and waypoints
        anchors.top: parent.top
        anchors.bottom: buttonsRowLayout.top
        anchors.left: parent.left
        anchors.right: parent.right
        orientation: Qt.Horizontal

        Rectangle {
            id: filesList
            SplitView.fillWidth: true
            SplitView.preferredWidth: root.width / 4
            SplitView.minimumWidth: root.width / 5
            SplitView.maximumWidth: root.width / 2

            GpxFilesTreeView {
                id: overview
                model: garminTreeModel
            }

        }

        Rectangle {
            id: tracksRect
            SplitView.preferredWidth: root.width / 4
            SplitView.minimumWidth: root.width / 5
            SplitView.maximumWidth: root.width / 2
            border.color: "black"

            RteTrkWptListView {
                id: tracksView
                listHeaderText: qsTr("Tracks")
                roleDisplay: "Tracks"
                model: garminListModel
            }
        }

        Rectangle {
            id: routesRect
            SplitView.preferredWidth: root.width / 4
            SplitView.minimumWidth: root.width / 5
            SplitView.maximumWidth: root.width / 2
            border.color: "black"

            RteTrkWptListView {
                id: routesView
                listHeaderText: qsTr("Routes")
                roleDisplay: "Routes"
                model: garminListModel
            }
        }

        Rectangle {
            id: waypointsRect
            SplitView.preferredWidth: root.width / 4
            SplitView.minimumWidth: root.width / 5
            SplitView.maximumWidth: root.width / 2
            border.color: "black"

            RteTrkWptListView {
                id: waypointsView
                listHeaderText: qsTr("Waypoints")
                roleDisplay: "Waypoints"
                model: garminListModel
            }
        }
    }

    RowLayout {
        // Represents a row of buttons (actions)
        id: buttonsRowLayout
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        Button {
            id: loadGarminDevicesButton
            Layout.margins: 10
            Layout.fillWidth: true
            // All buttons should have same width including margins
            Layout.preferredWidth: Math.max(implicitWidth + 20,
                                            openFileButton.implicitWidth + 20,
                                            exitButton.implicitWidth +20)
            //Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            text: qsTr("Load Garmin devices")
            onClicked: controller.onLoadGarminDevices()
        }

        Button {
            id: openFileButton
            Layout.margins: 10
            Layout.fillWidth: true
            // All buttons should have same width including margins
            Layout.preferredWidth: Math.max(loadGarminDevicesButton.implicitWidth + 20,
                                            openFileButton.implicitWidth + 20,
                                            exitButton.implicitWidth +20)
            //Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            text: qsTr("Open GPX file")
            //onClicked: qmlButtonClicked()
            onClicked: openFileDialog.open()
        }

        Button {
            id: exitButton
            Layout.margins: 10
            Layout.fillWidth: true
            // All buttons should have same width including margins
            Layout.preferredWidth: Math.max(loadGarminDevicesButton.implicitWidth + 20,
                                            openFileButton.implicitWidth + 20,
                                            exitButton.implicitWidth +20)
            //Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            text: qsTr("Exit")
            onClicked: Qt.quit()
        }
    }

    FileDialog {
        id: openFileDialog
        title: qsTr("Please choose gpx file")
        folder: shortcuts.documents
        nameFilters: [ "GPX files (*.gpx *.GPX)"]
        onAccepted: {
            controller.onOpenFile(openFileDialog.fileUrl)
        }
    }
    MessageDialog {
        // TODO: Problem with dark mode
        id: aboutMessage
        title: "Licences used"
        modality: Qt.ApplicationModal

        text: {
            "Copyright (C) 2020 Manfred Kern. All rights reserved.\n" +
            "Contact: manfred.kern@gmail.com \n" +
            "Under BSD license \n" +
            "Additional used license LGPLv3"
        }
    }
}

