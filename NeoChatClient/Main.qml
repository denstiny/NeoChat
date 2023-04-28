import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls 2.0
import com.neochat.network 1.0

Window {
    id:win
    width: 1367
    height: 812
    minimumWidth: 300
    visible: true
    title: qsTr("NeoChat")
    flags: Qt.Tool
    color: "#17212B"
    NeoChatNetoWork {
      id: network

    }


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
        text: qsTr(parent.parent_width + " x " + parent.parent_height)
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
        focus: true
        Keys.onTabPressed: {
          win.width = win.width + 50
          win.height = win.height + 50
          if (win.width > 1800){
            win.width = 1367
            win.height = 812
          }
        }
      }
    }
    LeftMenu {
      id: leftmenu
      visible: false
      height: parent.height
      property int default_width: 320
      width: 0
    }
    Component.onCompleted: {
        request({
                    "message_type":"login",
                    "type": "POST",
                    "user_account": "101",
                    "user_password": "asd"
                },check_login_status)
    }

     // 检测请求请求状态
    function check_login_status(res) {
        console.log(JSON.stringify(res))
    }

    function request(headerArgs,callback) {
      console.log("send login to server")
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
          print('HEADERS_RECEIVED');
        } else if(xhr.readyState === XMLHttpRequest.DONE) {
            let res = {
                status: xhr.status,
                headers: xhr.getAllResponseHeaders(),
                contentType: xhr.responseType,
                content : xhr.response
            }
          callback(res)
        }
      }
      xhr.open("POST", "http://127.0.0.1:6667");
      for(var key in headerArgs) {
          xhr.setRequestHeader(key,headerArgs[key])
      }
      xhr.send();
    }

}

