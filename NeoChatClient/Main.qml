import QtQuick
import QtQuick.Window
import QtQuick.Layouts

Window {
    width: 1367
    height: 812
    minimumWidth: 300
    visible: true
    title: qsTr("NeoChat")
    flags: Qt.Tool
    color: "#17212B"
    RowLayout {
      anchors.fill: parent
      anchors.margins: 10
      ChatListMenu {
        id: chatlistmenu
        Layout.alignment: Qt.AlignTop
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.maximumWidth: parent.width * 0.3
        Layout.minimumWidth: 300
        onOpenLeftMenu: {
            leftmenu.visible = true
        }
      }
      ChatWindow{
        Layout.alignment: Qt.AlignTop
        //anchors.left: chatlistmenu.right
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.maximumWidth: parent.width * 0.7
      }
    }
    Rectangle {
        id: window_size
        property double parent_width: parent.width
        property double parent_height: parent.height

        anchors.centerIn: parent
        Text {
            id: size
            text: qsTr(parent.parent_width + " x " + parent.parent_width)
            color: "#FFFFFF"
        }
    }
    Rectangle {
      // 网络状况
      id: network_state
      width: 30
      height: 30
      z: 2
      color: "#17212B"
      border.width: 1
      border.color: "black"
      anchors.bottom: parent.bottom
      anchors.left: parent.left
      anchors.margins: 10
      radius: width/2
      Image {
        anchors.fill: parent
        id: icon
        states: [
          State {
            name: "networkok"
            PropertyChanges {
              target: icon
              source: RES + "networkok.png"
            }
            PropertyChanges {
              target: row
              running: false
            }
          },
          State {
            name: "networkload"
            PropertyChanges {
              target: icon
              source: RES + "networkloading.png"
            }
            PropertyChanges {
              target: row
              running: true
            }
          }
        ]
        RotationAnimation on rotation  {
          id: row
          to: 360
          duration: 1000
          loops: Animation.Infinite
        }
        state: "networkok"
        MouseArea {
          anchors.fill: parent
          onClicked: {
            console.log("代理设置")
          }
        }
      }
    }
    LeftMenu {
        id: leftmenu
        visible: false
        z: 3
        height: parent.height
        width: 320
    }
}
