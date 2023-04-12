import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtQuick.Layouts 1.0

Rectangle {
    id: root
    Text {
        anchors.centerIn: parent
        id: text
        text: qsTr(parent.height + " x "+ parent.width)
    }
    signal openLeftMenu()

    ColumnLayout{
        spacing: 2
        anchors.fill: parent
        Rectangle {
            z:2
            id: menu
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            color: "red"
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            Rectangle {
                anchors.fill: parent
                color: "#17212B"
                RowLayout {
                    anchors.fill: parent
                    Button {
                        id: menuButton
                        Layout.alignment: Qt.AlignCenter | Qt.AlignLeft
                        Layout.preferredHeight: parent.height * 0.8
                        Layout.leftMargin: 8
                        icon.source:  RES  + "SideButtonLeave.png"
                        background: Rectangle {
                            border.width: 0
                            color: "#17212B"
                        }
                        onClicked: {
                            root.openLeftMenu()
                        }
                        onHoveredChanged:  {
                            if(hovered) {
                                menuButton.icon.source = RES + "SideButtonEnter.png"
                            }else {
                                menuButton.icon.source = RES + "SideButtonLeave.png"
                            }
                        }
                    }
                    TextField {
                        Layout.alignment: Qt.AlignCenter | Qt.AlignRight
                        Layout.preferredHeight: parent.height * 0.8
                        Layout.fillWidth: true
                        Layout.rightMargin: 9
                        placeholderText: "搜索"
                        placeholderTextColor: "#6D7883"
                        color: "#F5F5F5"
                        background: Rectangle {
                            border.width: 0
                            color: "#242F3D"
                            radius: 8
                        }
                    }
                }
            }
        }
        Rectangle {
            anchors.top: menu.bottom
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#17212B"
            ListView {
              ScrollBar.vertical: ScrollBar{
                active: hovered || pressed
              }
              anchors.fill: parent
              spacing: 1
              model: 100
              delegate: Rectangle{
                width: parent.width
                height: 50
                color: "#17212B"
                MouseArea {
                  anchors.fill: parent
                  hoverEnabled: true
                  onEntered: {
                    color = "#242F3D"
                  }
                  onExited: {
                    color = "#17212B"
                  }
                  onClicked: {
                    console.log("打开聊天")
                  }
                }
              }
            }
        }
    }
}
