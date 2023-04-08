#include "UserMenuWidget.hpp"
UserMenuWidget::UserMenuWidget (QWidget* parent):
  QWidget (parent),
  ui (new Ui_UserMenuWidget), is_hide (false) {
  
  ui->setupUi (this);
  installEventFilter (this);
  hide();
  wth = 260;
  start_pos.setX (0 - wth);
  start_pos.setY (0);
  end_pos.setX (0);
  end_pos.setY (0);
  InitMyEventSlot();
}

UserMenuWidget::~UserMenuWidget() {
  delete ui;
}

void UserMenuWidget::paintEvent (QPaintEvent* event)  {
  setFocus();
  resize (wth, parentWidget()->height());
}

bool UserMenuWidget::eventFilter (QObject* object, QEvent* event)  {
  if (QEvent::MouseButtonPress == event->type ()
      or QEvent::MouseButtonRelease == event->type()) {
    return true;
  }
  return QWidget::eventFilter (object, event);
}

void UserMenuWidget::showEvent (QShowEvent* event)  {
  QPropertyAnimation* animation = new QPropertyAnimation (this, "pos",
      this->parent());
  animation->setDuration (200); // 设置动画持续时间
  animation->setStartValue (start_pos);
  animation->setEndValue (end_pos);
  animation->start (QAbstractAnimation::DeleteWhenStopped);
}

void UserMenuWidget::hideEvent (QHideEvent* event)  {
  if (is_hide == true) return;
  show();
  QPropertyAnimation* animation  = new QPropertyAnimation (this, "pos",
      this->parent());
  animation->setDuration (100); // 设置动画持续时间
  animation->setStartValue (end_pos);
  animation->setEndValue (start_pos);
  connect (animation, &QPropertyAnimation::finished, [this]() {
    is_hide = true;
    QWidget::hide();
    is_hide = false;
  });
  animation->start (QAbstractAnimation::DeleteWhenStopped);
}

/**
   @brief 绑定按钮槽函数
*/
void UserMenuWidget::InitMyEventSlot()  {
  connect (ui->callButton, &QPushButton::clicked, this,
           &UserMenuWidget::cellButton_clicked);
  connect (ui->nightButton, &QPushButton::clicked, this,
           &UserMenuWidget::nightButton_clicked);
  connect (ui->createGroupButton, &QPushButton::clicked, this,
           &UserMenuWidget::createGroupButton_clicked);
  connect (ui->createChannelButton, &QPushButton::clicked, this,
           &UserMenuWidget::createChannelButton_clicked);
  connect (ui->settingButton, &QPushButton::clicked, this,
           &UserMenuWidget::settingButton_clicked);
  connect (ui->collectionButton, &QPushButton::clicked, this,
           &UserMenuWidget::cellectionButton_clicked);
  connect (ui->contactButton, &QPushButton::clicked, this,
           &UserMenuWidget::contactButton_clicked);
}

// 通话
void UserMenuWidget::cellButton_clicked()  {
  qDebug() << "UserMenuWidget::cellButton_clicked";
}

// 收藏
void UserMenuWidget::cellectionButton_clicked()  {
  qDebug() << "UserMenuWidget::cellectionButton_clicked";
  
}

// 联系人
void UserMenuWidget::contactButton_clicked()  {
  qDebug() << "UserMenuWidget::contactButton_clicked" ;
}

// 创建群组
void UserMenuWidget::createGroupButton_clicked()  {
  qDebug() << "UserMenuWidget::createGroupButton_clicked";
}

// 创建频道
void UserMenuWidget::createChannelButton_clicked()  {
  qDebug() << "UserMenuWidget::createChannelButton_clicked";
}

// 设置
void UserMenuWidget::settingButton_clicked()  {
  qDebug() << "UserMenuWidget::settingButton_clicked";
}

// 夜间
void UserMenuWidget::nightButton_clicked()  {
  qDebug() << "UserMenuWidget::nightButton_clicked";
}

// TODO: 创建群组窗口
// TODO: 创建设置窗口
// TODO: 创建频道窗口
// TODO: 创建联系人窗口 （已经生成ui文件
// TODO: 创建通话窗口
// TODO: 创建收藏窗口
