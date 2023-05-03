import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
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

        Label {
            text: "确认密码"
            color: "white"
        }

        TextField {
            id: confirmPasswordField
            placeholderText: "Confirm password"
            echoMode: TextInput.Password
        }

        Label {
            text: "邮箱"
            color: "white"
        }

        TextField {
            id: emailField
            placeholderText: "Enter email"
        }

        Button {
            text: "注册"
            onClicked: {
                // TODO: Handle registration logic
            }
        }
    }
}
