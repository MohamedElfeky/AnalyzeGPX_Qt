import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


ListView {
    id: root

    property string listHeaderText
    property string roleDisplay

    anchors.fill: parent
    anchors.margins: 10

    clip: true

    header: ListHeader {
        name: listHeaderText
        z: 2
    }
    headerPositioning: ListView.OverlayHeader

    delegate: Rectangle {
        id: delegateRect
        implicitWidth: 100
        implicitHeight: 20
        Text {
//            anchors.fill: parent
//            elide: Text.ElideRight
            text: {
                if (roleDisplay == "Routes") model.route
                else if (roleDisplay == "Tracks") model.track
                else if (roleDisplay == "Waypoints") model.waypoint
                else "Unknwon Role"
            }
        }
    }
}





