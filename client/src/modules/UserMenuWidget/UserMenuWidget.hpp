#pragma once
#include <QWidget>
#include <QDebug>
#include "ui_UserMenuWidget.h"
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QString>
#include <QColor>

class UserMenuWidget: public QWidget {
    Q_OBJECT
  public:
    void setBackground (const QColor& color);
    UserMenuWidget (QWidget* parent = nullptr);
    ~UserMenuWidget();
  protected:
    void showEvent (QShowEvent* event);
    void hideEvent (QHideEvent* event);
    void paintEvent (QPaintEvent* event);
    bool eventFilter (QObject* object, QEvent* event);
    
  public slots:
    void cellButton_clicked (); // 通话
    void cellectionButton_clicked (); // 收藏
    void contactButton_clicked (); // 联系人
    void createGroupButton_clicked (); //创建群组
    void createChannelButton_clicked(); // 创建频道
    void settingButton_clicked(); // 设置
    void nightButton_clicked(); // 夜间
  private:
    void InitMyEventSlot();
  private:
    QPoint start_pos, end_pos;
    bool is_hide; // 互斥HideEvent 锁
    int wth; // 当前窗口宽度
  private:
    Ui_UserMenuWidget* ui;
};
