import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
    id: addfriend
    signal AddFriendStatus
    z: 3
    anchors.fill: parent
    Rectangle {
        anchors.fill: parent
        opacity: 0.5
        color: "black"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                addfriend.destroy()
            }
        }
    }

    Rectangle {
        width: 200
        height: 300
        anchors.centerIn: parent
        ColumnLayout {
            anchors.fill: parent
            Label {
                text: "账号"
            }
            TextField {
                id: accountField
                placeholderText: "Enter account"
            }
            Label {
                text: "电话"
            }
            TextField {
                id: phoneField
                placeholderText: "Enter phone"
            }
            Row {
                Button {
                    text: "确定"
                    onClicked: {
                        var data = {
                            "message_type":"addfrend",
                            "user_account": accountField.text,
                            "user_phone": phoneField.text
                        }
                        $baseCommun.SendMessage(JSON.stringify(data))
                    }
                }
                Button {
                    text: "取消"
                    onClicked: {
                        addfriend.destroy()
                    }
                }
            }

        }
    }
    Component.onCompleted: {
        $baseCommun.newMessage.connect(function(message){
            var obj = JSON.parse(message)
            if (obj.message_type === "addfrend" && obj.status === true) {
                addfriend.destroy()
                addfriend.AddFriendStatus()
            }
        })
    }

}
