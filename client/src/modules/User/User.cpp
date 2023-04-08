#include "User.hpp"

User::User() {
  this->sex = Sex::neutral;
}

User::User (QSettings& setting, QString account) {
  Load (setting, account);
}

void User::Save (QSettings& setting)  {
  setting.beginGroup ("UserAccount_" + this->user_account);
  setting.setValue ("user_account", this->user_account);
  setting.setValue ("image_header_path", this->image_header_path);
  setting.setValue ("introduction", this->introduction);
  setting.setValue ("user_name", this->user_name);
  setting.setValue ("password", this->user_password);
  setting.setValue ("user_phone", this->user_phone);
  setting.setValue ("user_email", this->user_email);
  setting.setValue ("birthday", this->birthday);
  setting.setValue ("address", this->address);
  setting.setValue ("sex", ValueSex.at (this->sex));
  setting.endGroup();
}

void User::Load (QSettings& setting, QString account)  {
  this->user_account = account;
  setting.beginGroup ("UserAccount_" + this->user_account);
  user_account = setting.value ("user_account").toString();
  image_header_path = setting.value ("image_header_path").toString();
  introduction = setting.value ("introduction").toString();
  user_name = setting.value ("user_name").toString();
  user_password = setting.value ("password").toString();
  user_phone = setting.value ("user_phone").toString();
  user_email =  setting.value ("user_email").toString();
  birthday  = setting.value ("birthday").toString();
  address = setting.value ("address").toString();
  if (setting.value ("sex").toString().size() > 0) {
    this->sex = SexValue.at (setting.value ("sex").toString());
  }
  setting.endGroup();
}
