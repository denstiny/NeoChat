import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls 2.0
import Qt.labs.settings 1.1
import "./Communication.js" as Commun
import BaseCommun 1.0

Window {
    objectName: "NeoChat"
    id:win
    width: 1367
    height: 812
    minimumWidth: 300
    visible: true
    title: qsTr("NeoChat")
    flags: Qt.Tool
    color: "#17212B"

    signal loginStatus(bool status)
    signal updateLogin
    signal messageListen(string message)

    property var $baseCommun: Comm{}

    Settings {
        id: setting
        property alias width: win.width
        property alias height: win.height
        property string user_account
        property string user_password
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
        z: 3
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
                        source: "qrc:/images/networkok.png"
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
                        source: "qrc:/images/networkloading.png"
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

    function showLoginWidget(status) {
        var cmp = Qt.createComponent("./LoginWindow.qml",win)
        if(cmp.status === Component.Ready) {
            var obj = cmp.createObject(win, {})
            obj.loginStatus.connect(function(status){
                if(status) {
                    setting.user_account = obj.get_account()
                    setting.user_password = obj.get_password()
                    win.updateLogin()
                    obj.close()
                }
            })
        }
    }


    onUpdateLogin: {
        console.log("account: " + setting.user_account + "\n" + "password:" + setting.user_password)
    }

    Component.onCompleted: {
        $baseCommun.InitServer($baseCommun.ip,$baseCommun.port)
        // 消息日志，连接服务器状态
        $baseCommun.is_connected.connect(function(status){
            if(status) {
                console.log("连接服务器成功")
            }
            else{
                console.log("连接服务器失败")
            }
        })

        // 检测登陆状态，登陆成功则发送更新账号数据请求，登陆失败则打开登陆窗口
        win.loginStatus.connect(function(status){
            switch(status) {
            case true:
                console.log("登陆成功")
                updateLogin()
                break;
            case false:
                console.log("登陆失败")
                showLoginWidget(win.login)
                break;
            }
        });

        var message = {
            "message_type":"login",
            "user_account": setting.user_account,
            "user_password": setting.user_password

        }

        // 监听的新的消息
        $baseCommun.newMessage.connect(function(message){
            console.log("RES: " + message)
            var mes = JSON.parse(message)
            // 登陆
            if(mes.message_type === "login") {
                loginStatus(mes.status)
            }
            // 注册
            if(mes.message_type === "registered") {

            }
            // 用户消息
            if(mes.message_type === "text") {

            }
            // 语音消息
            if(mes.message_type === "voice") {

            }
            // 电话
            if(mes.message_type === "call") {

            }
            // 视频电话
            if(mes.message_type === "videocall") {

            }
            // 添加好友
            if(mes.message_type === "addfrend") {

            }
            // 修改个人信息
            if(mes.message_type === "changeinfo") {

            }
            // 获取用户信息
            if(mes.message_type === "userinfo") {

            }
        })

        // 首次打开程序发送登陆请求
        $baseCommun.SendMessage(JSON.stringify(message))
    }
}
