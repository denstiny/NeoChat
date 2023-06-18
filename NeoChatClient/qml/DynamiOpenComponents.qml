import QtQuick
Item {
    function openComponent(compent,parent,opts){
        var cmp = Qt.createComponent(compent,parent)
        if(cmp.status === Component.Ready) {
            var obj = cmp.createObject(parent,opts)
            return obj
        }
        return false
    }

    function openAddFriend(parent) {
        return openComponent("./AddFriend.qml",parent,{})
    }

    function openRegister(parent,opts) {
        return openComponent("./LoginWindow.qml",parent,opts)
    }

    function openSetting(parent) {
        return openComponent("./Setting.qml",parent,{})
    }
}
