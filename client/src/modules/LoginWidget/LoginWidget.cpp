#include "LoginWidget.hpp"

LoginWidget::LoginWidget ( QWidget* parent):
  QWidget (parent),
  ui (new Ui_LoginWidget),
  is_show (false),
  is_phone_login (true) {
  ui->setupUi (this);
  installEventFilter (this);
  hide();
  InitWidget();
}

LoginWidget::~LoginWidget() {
  delete ui;
}

/**
   @brief 当用户没有的登陆，则触发NoLogin singal ,该信号绑定StartLogin function
   @param user
*/
void LoginWidget::StartLogin (User& user)  {
  emit LoginStatus (false);
}

void LoginWidget::showEvent (QShowEvent* e)  {
  if (is_show) {
    return;
  }
  resize (parentWidget()->width(), parentWidget()->height());
  QPropertyAnimation* animation = new  QPropertyAnimation (this, "pos");
  animation->setDuration (500);
  animation->setStartValue (QPoint (-width(), 0));
  animation->setEndValue (QPoint (parentWidget()->width() / 2 - width() / 2, 0));
  connect (animation, &QAbstractAnimation::finished, this, [this]() {
    ShowLoginWidget (is_phone_login);
  });
  animation->start (QAbstractAnimation::DeleteWhenStopped);
  is_show = true;
}

void LoginWidget::paintEvent (QPaintEvent* event)  {
  resize (parentWidget()->width(), parentWidget()->height());
}

void LoginWidget::hideEvent (QHideEvent* e)  {
  if (not is_show) {
    return;
  }
  show();
  is_show = false;
  QPropertyAnimation* animation = new  QPropertyAnimation (this, "pos");
  animation->setDuration (200);
  animation->setStartValue (QPoint (parentWidget()->width() / 2 - width() / 2,
                                    0));
  animation->setEndValue (QPoint (-width(), 0));
  animation->start (QAbstractAnimation::DeleteWhenStopped);
  is_show = true;
}

bool LoginWidget::eventFilter (QObject* obj, QEvent* event)  {
  if (event->type() == QEvent::MouseButtonPress
      || event->type() == QEvent::MouseButtonRelease) {
    return true;
  } else {
    return QWidget::eventFilter (obj, event);
  }
}

void LoginWidget::InitWidget()  {
  ui->PhoneLoginWdiget->hide();
  ui->QrCodeLoginWidget->hide();
  // 绑定切换登陆模式按钮
  connect (ui->switchQrCodeLoginButton,
  &QPushButton::clicked, [this]() { // 使用二维码登陆
    this->is_phone_login = false;
    ShowLoginWidget (is_phone_login);
  });
  connect (ui->switchPhonLoginButton,
  &QPushButton::clicked, [this]() { // 使用手机号码登陆
    this->is_phone_login = true;
    ShowLoginWidget (is_phone_login);
  });
  // 登陆
  connect (ui->LoginButton, &QPushButton::clicked, this, [this]() {
    QString user_account = ui->AreaNumberLineEdit->text() +
                           ui->PhoneNumberLineEdit->text();
    QString user_password = ui->PhonePasswordLineEdit->text();
    emit LoginSendMessage (user_account, user_password);
  });
  connect (ui->returnButton, &QPushButton::clicked, this, [this]() {
    hide();
    is_show = false;
  });
}

void LoginWidget::ShowLoginWidget (bool is_phone_login)  {
  qDebug() << "-- show login widget --";
  int width = ui->LogiNChildWidget->width();
  int height = ui->LogiNChildWidget->height();
  if (is_phone_login) {
    ui->QrCodeLoginWidget->hide();
    ui->PhoneLoginWdiget->move (width / 2 - ui->PhoneLoginWdiget->width() / 2,
                                height / 2 - ui->PhoneLoginWdiget->height() / 2);
    ui->PhoneLoginWdiget->show();
  } else {
    ui->PhoneLoginWdiget->hide();
    ui->QrCodeLoginWidget->move (width / 2 - ui->QrCodeLoginWidget->width() / 2,
                                 height / 2 - ui->QrCodeLoginWidget->height() / 2);
    ui->QrCodeLoginWidget->show();
  }
}

bool LoginWidget::GetIsShow()  {
  return is_show;
}

void LoginWidget::setNetwork (NetWork* net)  {
  this->net = net;
}
