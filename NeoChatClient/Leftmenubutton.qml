import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0

Rectangle {
    id: root
    property string colorValue: "#242F3D"
    color: "transparent"
    signal clicked
    property alias text: label.text
    property alias icon: logo.source
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            root.color = colorValue
        }
        onExited:  {
            root.color = "transparent"
        }
        onClicked: {
            root.clicked()
        }
    }
    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 20
        Image {
            Layout.fillHeight: true
            fillMode: Image.PreserveAspectFit
            id: logo
        }
        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            verticalAlignment: Text.AlignVCenter
            id: label
            color: "#FFFFFF"
            font.pixelSize: 18
        }
    }
}
