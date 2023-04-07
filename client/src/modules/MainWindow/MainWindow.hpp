#pragma once
#include <QPushButton>
#include <QDebug>
#include "ui/ui_MainWindow.h"
#include <QPalette>
#include <QMouseEvent>
#include "UserMenuWidget/UserMenuWidget.hpp"
#include "LoginWidget/LoginWidget.hpp"
#include "NetWork/NetWork.hpp"
#include "User/User.hpp"
#include <QSettings>

class MainWindow: public QMainWindow {
    Q_OBJECT
  public:
    void InitNetWork();
    MainWindow (QWidget* widget = nullptr);
    ~MainWindow();
  private:
    void ShowChildWidget (QWidget* widget); // 显示子窗口
    void HideChildWidget (QWidget* widget); // 隐藏子窗口
    void LoadServerAccountInformation(); // 加载账号信息
    void AfterMath(); // 窗口关闭时做善后处理
  protected:
    bool eventFilter (QObject* object, QEvent* event);
    void resizeEvent (QResizeEvent* event);
  public slots:
    // user menu widget click
    void clickSideMenuButton();
    // mainwdows click
    void mousePressEvent (QMouseEvent* event);
    // network connection server status
    void NetWorkConnection (bool status);
    // network new meessage signal
    void NetWorkMessagePressed ();
    // login server status
    void TriggerLoginChanged (bool status);
    void Login (QString user_account, QString user_password);
  signals:
    // exit siganl
    void Quit(); // 退出信号
    // login server status signal
    void LoginStatusChanged (bool); // 登陆之后的登陆状态
  private:
    Ui_MainWindow* ui;
    UserMenuWidget* user_menu;
    LoginWidget* login_widget;
    QWidget* is_show_widget = nullptr;
    NetWork* network; // 网络通信
    QMap<QString, User> user; // 用户map
    QSettings* userSetting; // setting 保存用户信息类
    QString use_user_account;
    QString new_user_account;
};
