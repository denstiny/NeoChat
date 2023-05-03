import QtQuick
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls

Rectangle {
  color: "#0E1621"
  ColumnLayout {
      anchors.fill: parent
      Rectangle {
          // 标题栏
          z: 1
          Layout.alignment: Qt.AlignTop
          Layout.fillWidth: true
          color: "#17212B"
          height: 50
          RowLayout {
              anchors.fill: parent
              Rectangle {
                Layout.alignment: Qt.AlignLeft
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.maximumWidth: parent.width * 0.5
                Layout.maximumHeight: parent.height
                color: "transparent"
                Column{
                  anchors.fill: parent
                  Text {
                    width: parent.width
                    height: parent.height/2
                    color: "#E1DEDB"
                    id: name
                    text: qsTr("name")
                  }
                  Text {
                    width: parent.width
                    height: parent.height/2
                    id: status
                    color: "#556B85"
                    text: qsTr("最近上线")
                  }
                }
              }
              Button {
                id: searchButton
                icon.source: "qrc:/images/search_leave.png"
                background: Rectangle{
                    color: "transparent"
                }
                onHoveredChanged: {
                  if(hovered) {
                    icon.source = "qrc:/images/search_enter.png"
                  }else {
                    icon.source = "qrc:/images/search_leave.png"
                  }
                }
              }
              Button {
                id: callButton
                icon.source: "qrc:/images/call_leave.png"
                background: Rectangle{
                    color: "transparent"
                }
                onHoveredChanged: {
                  if(hovered) {
                    icon.source = "qrc:/images/call_enter.png"
                  }else {
                    icon.source = "qrc:/images/call_leave.png"
                  }
                }
              }
              Button {
                  // 打开右侧边栏
                id: rightmenuButton
                icon.source: "qrc:/images/rightbutton_leaver.png"
                background: Rectangle{
                    color: "transparent"
                }
                onHoveredChanged: {
                  if(hovered) {
                    icon.source = "qrc:/images/rightbutton_enter.png"
                  }else {
                    icon.source = "qrc:/images/rightbutton_leaver.png"
                  }
                }
              }
              Button {
                  // 打开右侧边栏
                id: dots_button
                icon.source: "qrc:/images/dots_leave.png"
                background: Rectangle{
                    color: "transparent"
                }
                onHoveredChanged: {
                  if(hovered) {
                    icon.source = "qrc:/images/dots_enter.png"
                  }else {
                    icon.source = "qrc:/images/dots_leave.png"
                  }
                }
              }
          }
      }

      Rectangle {
        id: messageMenu
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: "#0E1621"
        signal showGotoBottom(bool isshow)

        onShowGotoBottom: function(isshow) {
          gotoBottomButtom.visible = !isshow
        }


        ListView {
          // 显示消息
          id: messageList
          anchors.fill: parent
          ScrollBar.vertical: ScrollBar{
            id: scrollbar
            active: hovered || pressed
          }
          function isScrollBarAtBottom() {
            return messageList.contentY + messageList.height >= messageList.contentHeight;
          }
          spacing: 0
          model: 20
          delegate: Rectangle {
            color: "#0E1621"
            width: messageList.width
            height: 50
            MouseArea {
              anchors.fill: parent
              hoverEnabled: true
              onEntered: {
                var isBottom = messageList.isScrollBarAtBottom()
                messageMenu.showGotoBottom(isBottom)
              }
              onExited: {
                var isBottom = messageList.isScrollBarAtBottom()
                messageMenu.showGotoBottom(isBottom)
              }
              onClicked: {
                console.log("点击")
              }
            }
          }
        }
        Rectangle {
          // 跳转到最新消息按钮
          id: gotoBottomButtom
          radius: width/2
          width: 40
          height: 40
          anchors.right: parent.right
          anchors.bottom: parent.bottom
          anchors.margins: 10
          color: "#1D2B3A"
          visible: false
          Image {
            anchors.margins: 9
            anchors.fill: parent
            id: bottomIcon
            source: "qrc:/images/movebottom.png"
          }
            MouseArea {
              anchors.fill: parent
              hoverEnabled: true
              onClicked: {
                console.log("跳转到最下方")
                  scrollbar.position = 1-scrollbar.size;
              }
              onEntered: {
                bottomIcon.source = "qrc:/images/movebottomEnter.png"
              }
              onExited: {
                bottomIcon.source = "qrc:/images/movebottom.png"
              }
            }
        }
      }
      Rectangle {
        // 消息编辑框
        height: 50
        Layout.fillWidth: true
        color: "#17212B"
        RowLayout {
          anchors.fill: parent
          Button {
            // 选择文件按钮
            Layout.margins: 10
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: 40
            Layout.maximumWidth: 40
            background: Rectangle {
              color: "transparent"
            }
            icon.source: "qrc:/images/file_leave.png"
            onHoveredChanged: {
              if(hovered) {
                icon.source = "qrc:/images/file_enter.png"
              }else
                icon.source = "qrc:/images/file_leave.png"
            }
          }
          TextField {
            // 消息编辑框
            Layout.fillWidth: true
            Layout.fillHeight: true
            background: Rectangle {
              color: "transparent"
            }
            placeholderText: "输入消息..."
            placeholderTextColor: "#6D7883"
            color: "#6D7883"
          }
          Button {
            // 表情按钮
            icon.source : "qrc:/images/expression_leave.png"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: 40
            Layout.maximumWidth: 40
            background: Rectangle{
              color: "transparent"
            }

            onHoveredChanged:  {
              if(hovered)
                icon.source = "qrc:/images/expression_enter.png"
              else
                icon.source = "qrc:/images/expression_leave.png"
            }

          }
          Button{
            // 语音按钮
            icon.source : "qrc:/images/voice_leave.png"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: 50
            Layout.maximumWidth: 50
            background: Rectangle{
              color: "transparent"
            }

            onHoveredChanged:  {
              if(hovered)
                icon.source = "qrc:/images/voice_enter.png"
              else
                icon.source = "qrc:/images/voice_leave.png"
            }
          }
          Button {
            // 发送按钮
            icon.source : "qrc:/images/send-message.png"
            visible: false
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: 50
            Layout.maximumWidth: 50
            background: Rectangle{
              color: "transparent"
            }
          }
        }
      }
  }
}
