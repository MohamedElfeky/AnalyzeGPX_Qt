import QtQuick 2.14
import QtQuick.Controls 1.4

TreeView {
    id: root

    anchors.fill: parent
    anchors.leftMargin: 1
    headerVisible: true
    backgroundVisible: false

     TableViewColumn {
         title: qsTr("Name")
         role: "name"
         width: parent.width
     }

     itemDelegate: Item {
         Text {
             anchors.fill: parent
             elide: styleData.elideMode
//             color: styleColor
             text: styleData.value
         }
     }

     onClicked: {
         controller.onTreeviewClicked(index)
     }
}
