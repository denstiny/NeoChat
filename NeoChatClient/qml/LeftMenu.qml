import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Popup {
  id: popup
  property int default_width: 320
  background: Rectangle {
    color: "#17212B"
  }

  onVisibleChanged: {
    if(visible) {
      show_animation.start()
    }else {
      hide_animation.start()
    }
  }

  NumberAnimation {
    id: show_animation
    target: popup
    property: "width"
    from: 0
    to: popup.default_width
    duration: 300
  }
  NumberAnimation {
    id: hide_animation
    target: popup
    property: "width"
    from: popup.default_width
    to: 0
    duration: 300
  }

  modal: true
  ColumnLayout {
    //anchors.fill: parent
    width: parent.width
    height: parent.height
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
          icon: "qrc:/images/createGroup.png"
          onClicked: {
            console.log("新建族群")
          }
        }
        Leftmenubutton {
          width: parent.width
          height: buttonList.button_height
          text: "新建频道"
          icon: "qrc:/images/customerButton.png"
          onClicked: {
            console.log("新建频道")
          }
        }
        Leftmenubutton {
          width: parent.width
          height: buttonList.button_height
          text: "联系人"
          icon: "qrc:/images/contact-book.png"
          onClicked: {
            console.log("联系人")
          }
        }
        Leftmenubutton {
          width: parent.width
          height: buttonList.button_height
          text: "通话"
          icon: "qrc:/images/callButton.png"
          onClicked: {
            console.log("通话")
          }
        }
        Leftmenubutton {
          width: parent.width
          height: buttonList.button_height
          text: "我的收藏"
          icon:  "qrc:/images/collection.png"
          onClicked: {
            console.log("我的收藏")
          }
        }
        Leftmenubutton {
          width: parent.width
          height: buttonList.button_height
          text: "设置"
          icon: "qrc:/images/settings.png"
          onClicked: {
            console.log("设置")
          }
        }
        Leftmenubutton {
          width: parent.width
          height: buttonList.button_height
          text: "夜间模式"
          icon: "qrc:/images/night.png"
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
