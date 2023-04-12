import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Popup {
    background: Rectangle {
       color: "#17212B"
    }
    modal: true
    ColumnLayout {
        anchors.fill: parent
      Rectangle {
          color: "transparent"
          Layout.alignment: Qt.AlignTop
          Layout.fillWidth: true
        height: 150
      }
      Rectangle{
        color: "transparent"
        Layout.fillHeight: true
        Layout.fillWidth: true
        width: parent.width
        Column {
           anchors.fill: parent
           id: buttonList
           property int button_height: 40
           property int font_size: 17
           property int icon_height: 25
           property int icon_width: 25
           spacing: 10
           Leftmenubutton {
               width: parent.width
               height: buttonList.button_height
               text: "新建组群"
               icon: RES + "createGroup.png"
               onClicked: {
                   console.log("新建族群")
               }
           }
           Leftmenubutton {
               width: parent.width
               height: buttonList.button_height
               text: "新建频道"
               icon: RES + "customerButton.png"
               onClicked: {
                   console.log("新建频道")
               }
           }
           Leftmenubutton {
               width: parent.width
               height: buttonList.button_height
               text: "联系人"
               icon: RES + "contact-book.png"
               onClicked: {
                   console.log("联系人")
               }
           }
           Leftmenubutton {
               width: parent.width
               height: buttonList.button_height
               text: "通话"
               icon: RES + "callButton.png"
               onClicked: {
                   console.log("通话")
               }
           }
           Leftmenubutton {
               width: parent.width
               height: buttonList.button_height
               text: "我的收藏"
               icon:  RES + "collection.png"
               onClicked: {
                   console.log("我的收藏")
               }
           }
           Leftmenubutton {
               width: parent.width
               height: buttonList.button_height
               text: "设置"
               icon: RES + "settings.png"
               onClicked: {
                   console.log("设置")
               }
           }
           Leftmenubutton {
               width: parent.width
               height: buttonList.button_height
               text: "夜间模式"
               icon: RES + "night.png"
               onClicked: {
                   console.log("夜间模式")
               }
           }
        }
      }
      Rectangle {
          Layout.alignment: Qt.AlignBottom
          height: 100
          Layout.fillWidth: true
          Text {
              id: name
              text: qsTr("NeoChat")
              font.pixelSize: 30
              font.bold: true
              color: "#5D6B87"
          }
          color: "transparent"
      }
    }
}
