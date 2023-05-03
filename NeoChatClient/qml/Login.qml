import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "./Communication.js" as Commun

Item {
    signal loginStatus(bool status)
    property string user_account: usernameField.text
    property string user_password: passwordField.text
    ColumnLayout {
        anchors.centerIn: parent
        Label {
            text: "用户名"
            color: "white"
        }

        TextField {
            id: usernameField
            placeholderText: "Enter username"
        }

        Label {
            text: "密码"
            color: "white"
        }

        TextField {
            id: passwordField
            placeholderText: "Enter password"
            echoMode: TextInput.Password
        }

        Button {
            text: "登陆"
            onClicked: {
                Commun.request({
                                   "message_type":"login",
                                   "type": "POST",
                                   "user_account": usernameField.text,
                                   "user_password": passwordField.text,
                               },Commun.check_login_status, loginStatus)
            }
        }
    }
}
