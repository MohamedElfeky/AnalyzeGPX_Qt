import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    property alias name: myText.text
    width: parent.width
    height: myText.implicitHeight
    color: "white"
    Label {
        id: myText
        color: "red"
        bottomPadding: 10
    }
}

