#pragma once
#include <QString>
#include <unordered_map>
#include <QSettings>
#include <QDebug>

#define SEX_MALE "male"
#define SEX_FEMALE "female"
#define SEX_NEUTRAL "neutral"

enum class Sex {
  male, // 男性
  female, // 女性
  neutral, // 中性
};

const static std::unordered_map<QString, Sex> SexValue {
  {SEX_MALE, Sex::male},
  {SEX_FEMALE, Sex::female},
  {SEX_NEUTRAL, Sex::neutral},
};

const static std::unordered_map<Sex, QString> ValueSex {
  {Sex::male, SEX_MALE},
  {Sex::female, SEX_FEMALE},
  {Sex::neutral, SEX_NEUTRAL},
};

class User {
  public:
    void Save (QSettings& setting);
    void Load (QSettings& setting, QString account);
    User();
    User (QSettings& setting, QString account);
    // 账号
    QString user_account;
    // 头像
    QString image_header_path;
    // 简介
    QString introduction;
    // 密码
    QString user_password;
    // 名字
    QString user_name;
    // 电话
    QString user_phone;
    // 邮箱
    QString user_email;
    // 生日
    QString birthday;
    // 地址
    QString address;
    // 性别
    Sex sex;
};
