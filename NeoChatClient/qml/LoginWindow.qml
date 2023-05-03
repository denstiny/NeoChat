import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "./Communication.js" as Commun

Rectangle {
    id: loginDialog
    signal loginStatus(bool status)
    width: parent.width
    height: parent.height
    color: "black"
    x: parent.width
    z: 2

    property bool landing: true

    // LoginWindow show Animation
    SequentialAnimation {
        id: showLoginWidgetAnimation
        running: true
        NumberAnimation {
            target: loginDialog
            property: "x"
            to: 0
            easing.type: Easing.InOutQuad
            duration: 400
        }
    }

    SequentialAnimation {
        id: del_LoginWidgetAnimation
        NumberAnimation {
            target: loginDialog
            property: "x"
            to: loginDialog.width
            easing.type: Easing.InOutQuad
            duration: 300
        }
        onStopped: {
            loginDialog.destroy()
        }
    }

    Button {
        id: landing_registered
        text: "注册"
        contentItem: Label {
            text: landing_registered.text
            font: landing_registered.font
            color: "white"
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            color: "transparent"
        }
        onClicked: {
            loginDialog.landing = !loginDialog.landing
            if(loginDialog.landing) {
                landing_registered.text = "注册"
            }else{
                landing_registered.text = "登陆"
            }
        }
    }

    Rectangle {
        width: 300
        height: 300
        x: loginDialog.width / 2 - width / 2
        color: "transparent"
        anchors.fill: parent
        Login {
            id: login
            anchors.fill: parent
            visible: loginDialog.landing ? true : false
        }
        Register {
            id: register
            anchors.fill: parent
            visible: loginDialog.landing ? false : true
        }
    }
    Component.onCompleted: {
        login.loginStatus.connect(function(status){
            loginStatus(status)
        })
    }

    function get_account() {
        return login.user_account
    }

    function get_password() {
        return login.user_password
    }

    function close() {
        del_LoginWidgetAnimation.start()
    }
}
