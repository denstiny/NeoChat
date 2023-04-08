#pragma once

#include "ui_LoginWidget.h"
#include "User/User.hpp"
#include "NetWork/NetWork.hpp"
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QPoint>
#include <QWidget>

class LoginWidget: public QWidget {
    Q_OBJECT
  public:
    LoginWidget (QWidget* parent = nullptr);
    void setNetwork (NetWork* net);
    bool GetIsShow();
    ~LoginWidget();
  signals:
    void LoginStatus (bool status);
    void LoginSendMessage (QString user_account, QString user_password);
  public slots:
    void StartLogin (User& user);
    void showEvent (QShowEvent* e) override;
    void hideEvent (QHideEvent* e) override;
    void paintEvent (QPaintEvent* event) override;
  private:
    void InitWidget();
    void ShowLoginWidget (bool);
  private:
    Ui_LoginWidget* ui;
    QPoint start_point;
    QPoint end_point;
    bool is_show;
    bool is_phone_login;
    NetWork* net;
  protected:
    bool eventFilter (QObject* obj, QEvent* event) override;
};
